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

#ifndef _RENDERER_OPENGL_
#define _RENDERER_OPENGL_ 1

#include "../renderer.hpp"
#include "../model/batch.hpp"
#include "../material/texture.hpp"

#include <string>

//==============================================================================
//  Texture_opengl
//==============================================================================
class Texture_opengl : public Texture {
public:
  Texture_opengl(const std::string & name) : Texture(name) {};

  bool upload_texture();
private:
};


//==============================================================================
//  Batch_opengl
//==============================================================================
class Batch_opengl : public Batch {
public:
  Batch_opengl();

  void render();
  bool upload_vertexbuffer();
private:
  unsigned int m_vertexbuffer;
  unsigned int m_indexbuffer;
};

//==============================================================================
//  Renderer_opengl
//==============================================================================
class Renderer_opengl : public Renderer {
public:
  Renderer_opengl() {}
  ~Renderer_opengl() {}

  // init
  void init();
  void close();

  // viewport
  void set_viewport(const int left, const int top, const int width, const int height);
  void set_renderport(const int left, const int top, const int width, const int height);
  void set_view(Camera* camera);

  // batch
  Batch* create_batch();

  // texture
  Texture* create_texture(const std::string & name);
  void upload_textures();
  void bind_texture(Texture* texture);

  // render batch
  void render_batch(Batch* batch);
};

#endif /* _RENDERER_OPENGL_ */
