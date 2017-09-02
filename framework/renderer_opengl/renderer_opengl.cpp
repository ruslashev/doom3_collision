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

#include "renderer_opengl.hpp"
#include "../model/batch.hpp"
#include "../misc/log.hpp"
#include "../material/image.hpp"
#include "../scene/camera.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

//==============================================================================
//
//==============================================================================
GLenum getGLType(const Attribute_format attFormat) {
  switch (attFormat){
    case ATT_FLOAT:         return GL_FLOAT;
    case ATT_UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
    default:
                            return 0;
  }
}

GLenum getGLPrimitive(const Primitive_type primType){
  switch (primType){
    case PRIM_TRIANGLES:      return GL_TRIANGLES;
    case PRIM_QUADS:          return GL_QUADS;
    case PRIM_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
    default:
                              return 0;
  }
}

GLenum arrayType[] = { GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY };

//==============================================================================
//  Batch_opengl::Batch_opengl()
//==============================================================================
Batch_opengl::Batch_opengl() {
  m_indexbuffer=0;
  m_vertexbuffer=0;
}

//==============================================================================
//  Batch_opengl::upload_vertexbuffer()
//==============================================================================
bool Batch_opengl::upload_vertexbuffer() {
  glGenBuffersARB(1, &m_vertexbuffer);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vertexbuffer);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_num_vertices * m_vertex_size, m_vertices, GL_STATIC_DRAW_ARB);

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  if (m_indices > 0) {
    glGenBuffersARB(1, &m_indexbuffer);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_indexbuffer);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_num_indices * m_index_size, m_indices, GL_STATIC_DRAW_ARB);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
  }

  return true;
}

//==============================================================================
//  Batch_opengl::render()
//==============================================================================
void Batch_opengl::render() {
  unsigned int i, num_formats = m_formats.size();

  if(!m_vertexbuffer){
    upload_vertexbuffer();
  }

  if (m_vertexbuffer != 0) {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vertexbuffer);
  }

  for (i = 0; i < num_formats; ++i) {
    Format format = m_formats[i];
    GLenum type = getGLType(format.att_format);
    GLenum array = arrayType[format.att_type];

    char *basePointer = (m_vertexbuffer)? NULL : get_vertices();

    switch (format.att_type) {
      case ATT_VERTEX:
        glVertexPointer(format.size, type, get_vertex_size(), basePointer + format.offset);
        break;
      case ATT_NORMAL:
        glNormalPointer(type, get_vertex_size(), basePointer + format.offset);
        break;
      case ATT_TEXCOORD:
        glClientActiveTextureARB(GL_TEXTURE0_ARB + format.index);
        if(!format.index)
          glTexCoordPointer(format.size, type, get_vertex_size(), basePointer + format.offset);
        break;
      case ATT_COLOR:
        glColorPointer(format.size, type, get_vertex_size(), basePointer + format.offset);
        break;
    }
    glEnableClientState(array);
  }

  if (m_indexbuffer) {
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_indexbuffer);
    glDrawElements(getGLPrimitive( get_primitive_type() ), get_index_count(), get_index_size() == 2? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, NULL);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
  } else {
    glDrawElements(getGLPrimitive( get_primitive_type() ), get_index_count(), get_index_size() == 2? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, get_indices());
  }

  for (i = 0; i < num_formats; ++i) {
    if (get_format(i).att_type == ATT_TEXCOORD) {
      glClientActiveTextureARB(GL_TEXTURE0_ARB + get_format(i).index);
    }
    glDisableClientState(arrayType[get_format(i).att_type]);
  }

  if (m_vertexbuffer) {
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
  }
}

//==============================================================================
//  Texture_opengl::upload_texture()
//==============================================================================
bool Texture_opengl::upload_texture() {
  log_function_multiple << "Upload texture " << m_name << endl;
  int count = m_images.size();

  if(!count) {
    log_debug << "No images in texture" << endl;
    log_error << "Texture binded unsuccessful" << endl;
    return false;
  }

  bool created = false;

  if(!m_tex_id) {
    glGenTextures( 1, &m_tex_id );
  }

  if(m_tex_id) {
    created = true;
  }

  GLuint format;
  GLuint type;
  GLuint dimension;

  switch(m_images[0]->get_image_type() ) {
    case Image::RGB:	   format = GL_RGB;
                         break;
    case Image::RGBA:	   format = GL_RGBA;
                         break;
    case Image::GREYSCALE: format = GL_ALPHA;
                           break;
  }

  switch(m_type) {
    case BYTE:  type = GL_UNSIGNED_BYTE;
                break;
    case FLOAT: type = GL_FLOAT;
                log_error << "Float type image not supported!" << endl;
                break;
  }

  switch(m_dimension) {
    case TEX_1D:   dimension = GL_TEXTURE_1D;
                   log_debug_multiple << "type = GL_TEXTURE_1D" << endl;
                   break;
    case TEX_2D:   dimension = GL_TEXTURE_2D;
                   log_debug_multiple << "type = GL_TEXTURE_2D" << endl;
                   break;
    // case TEX_3D:   dimension = GL_TEXTURE_3D;
    //                log_debug_multiple << "type = GL_TEXTURE_3D" << endl;
    //                break;
    // case TEX_CUBE: if(!GL_ARB_texture_cube_map_supported) {
    //   log_warning << "GL_TEXTURE_CUBE_MAP is not supported!" << endl;
    //   dimension = GL_TEXTURE_2D;
    // } else {
    //   dimension = GL_TEXTURE_CUBE_MAP_ARB;
    //   log_debug_multiple << "type = GL_TEXTURE_CUBE_MAP_ARB" << endl;
    // }
    //                break;
  }

  glBindTexture( dimension, m_tex_id);

  if(m_dimension != TEX_CUBE) {
    gluBuild2DMipmaps( dimension, /*format*/GL_COMPRESSED_RGB_ARB, m_images[0]->get_image_width(), m_images[0]->get_image_height(),
        format, type, m_images[0]->get_pixels());
  } else {
    if(m_images.size()<6) {
      log_error << "Trying to upload Cube Map with " << m_images.size() << " images" << endl;
      return false;
    }

    GLuint cube_map_faces[] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
    };

    for( int i=0; i<6; i++ ) {
      switch(m_images[i]->get_image_type() ) {
        case Image::RGB:	   format = GL_RGB;
                             break;
        case Image::RGBA:	   format = GL_RGBA;
                             break;
        case Image::GREYSCALE: format = GL_ALPHA;
                               break;
      }
      gluBuild2DMipmaps( cube_map_faces[i], format, m_images[i]->get_image_width(), m_images[i]->get_image_height(),
          format, type, m_images[i]->get_pixels() );
    }
  }

  //		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  //Set Parameters
  if(!m_use_nearest) {
    glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
    glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  if(!m_use_clamp) {
    glTexParameteri(dimension, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(dimension, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if(dimension == TEX_CUBE) {
      glTexParameteri(dimension, GL_TEXTURE_WRAP_R, GL_REPEAT);
    }
  } else {
    glTexParameteri(dimension, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(dimension, GL_TEXTURE_WRAP_T, GL_CLAMP);
    if(dimension == TEX_CUBE) {
      glTexParameteri(dimension, GL_TEXTURE_WRAP_R, GL_CLAMP);
    }
  }

  // if (GL_EXT_texture_filter_anisotropic_supported){
  //   int max_anisotrophy = 1;
  //   glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotrophy);
  //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotrophy);
  // }

  if(created) {
    log_debug_multiple << "width " << m_images[0]->get_image_width() << ", height " << m_images[0]->get_image_height() << " bind to " << m_tex_id << endl;
    log_debug_multiple << "mipmap = " << (m_use_nearest?"GL_NEAREST":"GL_LINEAR_MIPMAP_LINEAR") << endl;
    log_success_multiple << "Texture binded successful" << endl;
  } else {
    log_debug_multiple << "glGenTextures == NULL" << endl;
    log_error << "Texture uploaded unsuccessful" << endl;
  }

  return created;
}

//==============================================================================
//  Renderer_opengl::init()
//==============================================================================
void Renderer_opengl::init() {
  GLenum err = glewInit();
  if (err != GLEW_OK)
    printf("failed to initialze glew: %s", glewGetErrorString(err));

  glClearColor( 0, 0, 0, 1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_SCISSOR_TEST);
}

//==============================================================================
//  Renderer_opengl::close()
//==============================================================================
void Renderer_opengl::close() {
}

//==============================================================================
//  Renderer_opengl::set_viewport()
//==============================================================================
void Renderer_opengl::set_viewport(const int left, const int top, const int width, const int height) {
  glViewport(left, top, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (float)width/(float)height, 0.15f ,50000.0f);
  set_renderport(left, top, width, height);
}

//==============================================================================
//  Renderer_opengl::create_batch()
//==============================================================================
Batch* Renderer_opengl::create_batch() {
  Batch_opengl* batch = new Batch_opengl();

  return (Batch *)batch;
}

//==============================================================================
//  Renderer_opengl::create_texture()
//==============================================================================
Texture* Renderer_opengl::create_texture(const std::string & name) {
  Texture_opengl* texture = new Texture_opengl(name);
  m_texture_map[name] = texture;
  return (Texture *)texture;
}

//==============================================================================
//  Renderer_opengl::set_renderport()
//==============================================================================
void Renderer_opengl::set_renderport(const int left, const int top, const int width, const int height) {
  glScissor(left, top, width, height);
}

//==============================================================================
//  Renderer_opengl::set_view()
//==============================================================================
void Renderer_opengl::set_view(Camera* camera) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();                                   // Reset The matrix

  static Matrix4x4f mat;
  const Vector3f eye = camera->get_position();
  mat = Matrix4x4f( camera->get_orientation() );

  glMultMatrixf(mat);
  glTranslated(-eye.x,-eye.y,-eye.z );

  // setup matrixes
  glGetFloatv(GL_MODELVIEW_MATRIX, m_modelview_matrix);
  glGetFloatv(GL_PROJECTION_MATRIX, m_projection_matrix);
  glGetIntegerv(GL_VIEWPORT, m_viewport);

  // update frustum of camera
  camera->update_frustum();
}

//==============================================================================
//  Renderer_opengl::upload_textures()
//==============================================================================
void Renderer_opengl::upload_textures() {
  std::map<std::string, Texture*>::const_iterator it;

  for ( it = m_texture_map.begin(); it != m_texture_map.end(); ++it ) {
    it->second->upload_texture();
  }
}

//==============================================================================
//  Renderer_opengl::bind_texture()
//==============================================================================
void Renderer_opengl::bind_texture(Texture* texture) {
  glBindTexture(GL_TEXTURE_2D, texture->get_tex_id() );
}
