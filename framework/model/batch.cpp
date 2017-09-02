//============================================================================//
// This source file is part of work done by Reinder Nijhoff (reinder@infi.nl) //
// For the latest info, see http://developer.infi.nl                          //
//                                                                            //
// You're free to use the code in any way you like, modified, unmodified or   //
// cut'n'pasted into your own work.                                           //
//                                                                            //
// Part of this source is based on work by:                                   //
//    - Humus (http://esprit.campus.luth.se/~humus/)                          //
//    - Paul Baker (http://www.paulsprojects.net)                             //
//============================================================================//

#include "batch.hpp"
#include "../math/vector.hpp"
#include "../misc/log.hpp"

//==============================================================================
//
//==============================================================================
float get_value(const char *src, const unsigned int index, const Attribute_format att_format) {
  switch (att_format) {
    case ATT_FLOAT:         return *(((float *) src) + index);
    case ATT_UNSIGNED_BYTE: return *(((unsigned char *) src) + index) * (1.0f / 255.0f);
    default:
                            return 0;
  }
}

//==============================================================================
//
//==============================================================================
void set_value(const char *dest, const unsigned int index, const Attribute_format att_format, float value) {
  switch (att_format) {
    case ATT_FLOAT:
      *(((float *) dest) + index) = value;
      break;
    case ATT_UNSIGNED_BYTE:
      *(((unsigned char *) dest) + index) = (unsigned char) (value * 255.0f);
      break;
  }
}

//==============================================================================
//
//==============================================================================
unsigned int get_size(const Attribute_format att_format) {
  switch (att_format) {
    case ATT_FLOAT:         return 4;
    case ATT_UNSIGNED_BYTE: return 1;
    default:
                            return 0;
  }
}

//==============================================================================
//  Batch::Batch()
//==============================================================================
Batch::Batch() {
  m_vertices = NULL;
  m_indices  = NULL;

  m_num_vertices = 0;
  m_num_indices  = 0;
  m_vertex_size = 0;
  m_index_size  = 0;
}

//==============================================================================
//  Batch::~Batch()
//==============================================================================
Batch::~Batch() {
  clean();
}

//==============================================================================
//  Batch::clean()
//==============================================================================
void Batch::clean() {
  if (m_vertices != NULL) delete m_vertices;
  if (m_indices  != NULL) delete m_indices;
  m_vertices = NULL;
  m_indices = NULL;
}

//==============================================================================
//  Batch::find_attribute()
//==============================================================================
bool Batch::find_attribute(const Attribute_type att_type, const unsigned int index, unsigned int *where) const {
  for (unsigned int i = 0; i < m_formats.size(); i++) {
    if (m_formats[i].att_type == att_type && m_formats[i].index == index) {
      if (where != NULL) *where = i;
      return true;
    }
  }
  return false;
}

//==============================================================================
//  Batch::insert_attribute()
//==============================================================================
bool Batch::insert_attribute(const Attribute_type att_type, const Attribute_format att_format, const unsigned int size, const unsigned int index) {
  unsigned int i;

  for (i = 0; i < m_formats.size(); i++) {
    if (m_formats[i].att_type == att_type && m_formats[i].index == index) return false;
  }

  add_format(att_type, att_format, size, m_vertex_size, index);

  unsigned int fSize = size * get_size(att_format);
  unsigned int newm_vertex_size = m_vertex_size + fSize;
  char *newm_vertices = new char[m_num_vertices * newm_vertex_size];

  char *dest = newm_vertices;
  char *src = m_vertices;
  for (i = 0; i < m_num_vertices; i++) {
    memcpy(dest, src, m_vertex_size);
    memset(dest + m_vertex_size, 0, fSize);
    dest += newm_vertex_size;
    src += m_vertex_size;
  }

  delete m_vertices;
  m_vertices = newm_vertices;
  m_vertex_size = newm_vertex_size;

  return true;
}

//==============================================================================
//  Batch::remove_attribute()
//==============================================================================
bool Batch::remove_attribute(const Attribute_type att_type, const unsigned int index) {
  unsigned int i, j;

  for (i = 0; i < m_formats.size(); i++) {
    if (m_formats[i].att_type == att_type && m_formats[i].index == index) {
      Format format = m_formats[i];
      m_formats.remove(i);

      unsigned int fSize = format.size * get_size(format.att_format);
      for (j = i; j < m_formats.size(); j++) m_formats[i].offset -= fSize;

      unsigned int newm_vertex_size = m_vertex_size - fSize;
      char *newm_vertices = new char[m_num_vertices * newm_vertex_size];

      char *dest = newm_vertices;
      char *src = m_vertices;
      memcpy(dest, src, format.offset);
      dest += format.offset;
      src += format.offset + fSize;
      for (j = 0; j < m_num_vertices - 1; j++) {
        memcpy(dest, src, newm_vertex_size);
        dest += newm_vertex_size;
        src += m_vertex_size;
      }
      memcpy(dest, src, m_vertex_size - (format.offset + fSize));

      delete m_vertices;
      m_vertices = newm_vertices;
      m_vertex_size = newm_vertex_size;

      return true;
    }
  }
  return false;
}

//==============================================================================
//  Batch::read_from_file()
//==============================================================================
void Batch::read_from_file(FILE *file) {
  fread(&m_num_vertices,  sizeof(m_num_vertices),  1, file);
  fread(&m_num_indices,   sizeof(m_num_indices),   1, file);
  fread(&m_vertex_size, sizeof(m_vertex_size), 1, file);
  fread(&m_index_size,  sizeof(m_index_size),  1, file);

  fread(&m_primitive_type, sizeof(m_primitive_type), 1, file);

  unsigned int num_of_formats;
  fread(&num_of_formats, sizeof(num_of_formats), 1, file);
  m_formats.resize(num_of_formats);
  fread(m_formats.get_array(), num_of_formats * sizeof(Format), 1, file);

  m_vertices = new char[m_num_vertices * m_vertex_size];
  fread(m_vertices, m_num_vertices * m_vertex_size, 1, file);

  if (m_num_indices > 0) {
    m_indices = new char[m_num_indices  * m_index_size];
    fread(m_indices,  m_num_indices  * m_index_size,  1, file);
  } else m_indices = NULL;
}

//==============================================================================
//  Batch::add_normals()
//==============================================================================
bool Batch::add_normals() {
  if (m_indices == NULL) return false;
  if (!insert_attribute(ATT_NORMAL, ATT_FLOAT, 3)) return false;
  if (m_primitive_type != PRIM_TRIANGLES) return false;

  unsigned int vertexOffset, normalOffset;
  if (!find_attribute(ATT_VERTEX, 0, &vertexOffset) || !find_attribute(ATT_NORMAL, 0, &normalOffset)) return false;

  Attribute_format vertFormat = m_formats[vertexOffset].att_format;
  vertexOffset = m_formats[vertexOffset].offset;
  normalOffset = m_formats[normalOffset].offset;

  unsigned int i, nTris = m_num_indices / 3;
  for (i = 0; i < nTris; i++){
    unsigned int i0, i1, i2;
    if (m_index_size == 2){
      i0 = ((unsigned short *) m_indices)[3 * i];
      i1 = ((unsigned short *) m_indices)[3 * i + 1];
      i2 = ((unsigned short *) m_indices)[3 * i + 2];
    } else {
      i0 = ((unsigned int *) m_indices)[3 * i];
      i1 = ((unsigned int *) m_indices)[3 * i + 1];
      i2 = ((unsigned int *) m_indices)[3 * i + 2];
    }

    char *vert, *norm;
    vert = m_vertices + i0 * m_vertex_size + vertexOffset;
    Vector3f v0(get_value(vert, 0, vertFormat), get_value(vert, 1, vertFormat), get_value(vert, 2, vertFormat));
    vert = m_vertices + i1 * m_vertex_size + vertexOffset;
    Vector3f v1(get_value(vert, 0, vertFormat), get_value(vert, 1, vertFormat), get_value(vert, 2, vertFormat));
    vert = m_vertices + i2 * m_vertex_size + vertexOffset;
    Vector3f v2(get_value(vert, 0, vertFormat), get_value(vert, 1, vertFormat), get_value(vert, 2, vertFormat));

    Vector3f normal = (cross(v1 - v0, v2 - v0));

    norm = m_vertices + i0 * m_vertex_size + normalOffset;
    *(Vector3f *) norm += normal;
    norm = m_vertices + i1 * m_vertex_size + normalOffset;
    *(Vector3f *) norm += normal;
    norm = m_vertices + i2 * m_vertex_size + normalOffset;
    *(Vector3f *) norm += normal;
  }

  for (i = 0; i < m_num_vertices; i++){
    char *norm = m_vertices + i * m_vertex_size + normalOffset;
    *((Vector3f *) norm) = (*(Vector3f *) norm).get_normalized();
  }

  return true;
}

//==============================================================================
//  Batch::write_to_file()
//==============================================================================
void Batch::write_to_file(std::ofstream &file) {
  file << "# Batch " << endl;
  file << "num_of_vertices: " << m_num_vertices << endl;
  file << "num_of_indices:  " << m_num_indices << endl;
  file << "vertex_size:     " << m_vertex_size << endl;
  file << "index_size:      " << m_index_size << endl;
  file << "primitive_type:  " << m_primitive_type << endl;
  file << "# format" << endl;

  unsigned int num_formats = m_formats.size();
  file << "num_formats:    " << num_formats << endl;
  for(int i=0; i<num_formats; ++i) {
    file << "  format:   " << i << endl;
    file << "    type:   " << m_formats[i].att_type << endl;
    file << "    format: " << m_formats[i].att_format << endl;
    file << "    size:   " << m_formats[i].size << endl;
    file << "    index:  " << m_formats[i].index << endl;
    file << "    offset: " << m_formats[i].offset << endl;
  }
  file << "# vertices " << endl;
  for(int j=0; j<m_num_vertices; ++j) {
    file << "( ";
    for(int i=0; i<num_formats; ++i) {
      for(int k=0; k<m_formats[i].size; ++k) {
        switch(m_formats[i].att_format) {
          case ATT_FLOAT:
            file << ((float *)(m_vertices+m_vertex_size*j+m_formats[i].offset))[k];
            break;
          default:
            file << ((unsigned short *)(m_vertices+m_vertex_size*j+m_formats[i].offset))[k];
            break;
        }
        if(k < (m_formats[i].size-1) || i < num_formats-1) {
          file << ", ";
        }
      }
    }
    file << " )" << endl;
  }
  file << "# indices " << endl;
  for(unsigned int i=0; i<m_num_indices; i+=3) {
    switch(m_index_size) {
      case 2:	file << ((unsigned short *)m_indices)[i] << ", ";
              file << ((unsigned short *)m_indices)[i+1] << ", ";
              file << ((unsigned short *)m_indices)[i+2] << endl;
              break;
      default: file << ((unsigned int *)m_indices)[i] << ", ";
               file << ((unsigned int *)m_indices)[i+1] << ", ";
               file << ((unsigned int *)m_indices)[i+2] << endl;
               break;
    }
  }
}


//==============================================================================
//  Batch::write_to_file()
//==============================================================================
void Batch::write_to_file(const char *fileName) {
  FILE *file = fopen(fileName, "wb");
  if (file == NULL) return;

  unsigned int version = 1;
  fwrite(&version, sizeof(version), 1, file);
  unsigned int nBatches = 1;
  fwrite(&nBatches, sizeof(nBatches), 1, file);

  fwrite(&m_num_vertices, sizeof(m_num_vertices),  1, file);
  fwrite(&m_num_indices, sizeof(m_num_indices),   1, file);
  fwrite(&m_vertex_size, sizeof(m_vertex_size), 1, file);
  fwrite(&m_index_size, sizeof(m_index_size),  1, file);

  fwrite(&m_primitive_type, sizeof(m_primitive_type), 1, file);

  unsigned int num_formats = m_formats.size();
  fwrite(&num_formats, sizeof(num_formats), 1, file);
  fwrite(m_formats.get_array(), num_formats * sizeof(Format), 1, file);

  fwrite(m_vertices, m_num_vertices * m_vertex_size, 1, file);
  fwrite(m_indices,  m_num_indices  * m_index_size,  1, file);

  fclose(file);
}

//==============================================================================
//  Batch::write_to_file()
//==============================================================================
void Batch::write_to_file(FILE *file) {
  fwrite(&m_num_vertices, sizeof(m_num_vertices),  1, file);
  fwrite(&m_num_indices, sizeof(m_num_indices),   1, file);
  fwrite(&m_vertex_size, sizeof(m_vertex_size), 1, file);
  fwrite(&m_index_size, sizeof(m_index_size),  1, file);

  fwrite(&m_primitive_type, sizeof(m_primitive_type), 1, file);

  unsigned int num_formats = m_formats.size();
  fwrite(&num_formats, sizeof(num_formats), 1, file);
  fwrite(m_formats.get_array(), num_formats * sizeof(Format), 1, file);

  fwrite(m_vertices, m_num_vertices * m_vertex_size, 1, file);
  fwrite(m_indices,  m_num_indices  * m_index_size,  1, file);
}

