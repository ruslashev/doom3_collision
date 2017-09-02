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

#include "texture.hpp"
#include "image.hpp"
#include "../misc/log.hpp"

//==============================================================================
//  Texture::Texture()
//==============================================================================
Texture::Texture(const std::string& name) {
  log_init_multiple << "Initialize Texture: " << name << endl;
  m_name = name;

  /* default */
  m_tex_id = 0;
  m_type = BYTE;
  m_dimension = TEX_2D;
  m_use_nearest = false;
  m_use_clamp = false;
}

//==============================================================================
//  Texture::~Texture()
//==============================================================================
Texture::~Texture() {
  clear();
}

//==============================================================================
//  Texture::set_image()
//==============================================================================
void Texture::set_image(Image* image) {
  clear();
  m_images.push_back(image);
}

//==============================================================================
//  Texture::set_image()
//==============================================================================
void Texture::set_image(int index, Image* image) {
  if(index >= m_images.size()) {
    log_warning << "Illegal argument to Texture::set_image(): " << index << endl;
    return;
  }
  if(m_images[index] != NULL) delete m_images[index];
  m_images[index] = image;
}

//==============================================================================
//  Texture::set_num_images()
//==============================================================================
void Texture::set_num_images(int count) {
  clear();
  m_images.resize(count);

  for(int i=0; i<count; i++) {
    m_images[i] = NULL;
  }
}

//==============================================================================
//  clear()
//==============================================================================
void Texture::clear() {
  if(m_images.size()) {
    log_init_multiple << "Free all images of texture " << m_name << endl;

    int count = m_images.size();

    for(int i=0; i<count; i++) {
      if(m_images[i] != NULL) delete m_images[i];
    }
    m_images.resize(0);
  }
}

