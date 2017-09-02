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

#include "renderer.hpp"
#include "material/texture.hpp"
#include "material/image.hpp"
#include "misc/log.hpp"

//==============================================================================
//  Renderer::get_texture_from_file()
//==============================================================================
Texture* Renderer::get_texture_from_file(const std::string & name) {
  if(m_texture_map.find(name) != m_texture_map.end()) {
    log_debug_multiple << name << " found in m_texture_map in Renderer::get_texture_from_file() " << endl;
    return m_texture_map[name];
  }
  Image* image = new Image();

  // todo, create an 'file not found' default texture;
  if(!image->load_form_file(name)) {
    log_error << "unable to load image: " << name << endl;
    image->create_empty();
  }

  Texture* texture = create_texture(name);
  texture->set_image(image);

  return texture;
}

//==============================================================================
//  Renderer::get_texture()
//==============================================================================
Texture* Renderer::get_texture(const std::string & name) {
  if(m_texture_map.find(name) != m_texture_map.end()) {
    log_debug_multiple << name << " found in m_texture_map in Renderer::get_texture() " << endl;
    return m_texture_map[name];
  }
  return create_texture(name);
}

