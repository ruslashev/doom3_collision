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

#ifndef _BATCH_
#define _BATCH_ 1

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "../misc/set.hpp"

enum Primitive_type {
  PRIM_TRIANGLES      = 0,
  PRIM_QUADS          = 1,
  PRIM_TRIANGLE_STRIP = 2,
};

enum Attribute_type {
  ATT_VERTEX   = 0,
  ATT_NORMAL   = 1,
  ATT_TEXCOORD = 2,
  ATT_COLOR    = 3,
};

enum Attribute_format {
  ATT_FLOAT         = 0,
  ATT_UNSIGNED_BYTE = 1,
};

float get_value(const char *src, const unsigned int index, const Attribute_format att_format);
unsigned int get_size(const Attribute_format att_format);

struct Format {
  Attribute_type att_type;
  Attribute_format att_format;
  unsigned int size;
  unsigned int offset;
  unsigned int index;
};

//==============================================================================
//  Batch
//==============================================================================
class Batch {
public:
  Batch();
  virtual ~Batch();

  void clean();

  unsigned int get_index(const unsigned int index) const {
    return (m_index_size == 2)? ((unsigned short *) m_indices)[index] : ((unsigned int *) m_indices)[index];
  }

  void set_index(const unsigned int index, const unsigned int value) {
    if (m_index_size == 2) {
      ((unsigned short *) m_indices)[index] = value;
    } else {
      ((unsigned int *) m_indices)[index] = value;
    }
  }

  char *get_vertices() const { return m_vertices; }
  char *get_indices()  const { return m_indices;  }
  const unsigned int get_vertex_count() const { return m_num_vertices;  }
  const unsigned int get_index_count()  const { return m_num_indices;   }
  const unsigned int get_vertex_size()  const { return m_vertex_size; }
  const unsigned int get_index_size()   const { return m_index_size;  }

  const unsigned int get_format_count() const { return m_formats.size(); }
  const Format &get_format(unsigned int index) const { return m_formats[index]; }

  const Primitive_type get_primitive_type() const { return m_primitive_type; }
  void set_primitive_type(const Primitive_type prim_type) { m_primitive_type = prim_type; }

  void set_vertices(void *vertex_array, const unsigned int vertex_count, const unsigned int size) {
    m_vertices = (char *) vertex_array;
    m_num_vertices = vertex_count;
    m_vertex_size = size;
  }
  void set_indices(void *index_array, const unsigned int index_count, const unsigned int size) {
    m_indices = (char *) index_array;
    m_num_indices = index_count;
    m_index_size = size;
  }

  void add_format(const Attribute_type att_type, const Attribute_format att_format, const unsigned int size, const unsigned int offset, const unsigned int index = 0) {
    Format format;

    format.att_type = att_type;
    format.att_format = att_format;
    format.size = size;
    format.offset = offset;
    format.index = index;

    m_formats.add(format);
  }

  bool find_attribute(const Attribute_type att_type, const unsigned int index = 0, unsigned int *where = NULL) const;
  bool insert_attribute(const Attribute_type att_type, const Attribute_format att_format, const unsigned int size, const unsigned int index = 0);
  bool remove_attribute(const Attribute_type att_type, const unsigned int index = 0);

  virtual void render()=0;
  bool add_normals();

  void read_from_file(FILE *file);
  void write_to_file(std::ofstream &file);
  void write_to_file(const char *fileName);
  void write_to_file(FILE *file);
protected:
  char *m_vertices;
  char *m_indices;

  unsigned int m_num_vertices;
  unsigned int m_num_indices;
  unsigned int m_vertex_size;
  unsigned int m_index_size;

  Set<Format> m_formats;
  Primitive_type m_primitive_type;
};

#endif /* _BATCH_ */
