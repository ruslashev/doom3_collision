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

#include "image.hpp"
#include "../misc/log.hpp"

#include <fstream>
#include <cstring>

static int TGAReadError = 0;

//==============================================================================
//  read_data()
//==============================================================================
void read_data(std::ifstream &file, char* data, unsigned int size) {
  if (!file.is_open()) {
    return;
  }
  unsigned int a = file.tellg();
  a+= size;
  file.read(data, size);
  if (a != file.tellg()) {
    TGAReadError = 1;
  }
}

//==============================================================================
//  Image::Image()
//==============================================================================
Image::Image() {
  m_loaded = false;
  m_width = 0;
  m_height = 0;
  m_pixel_depth = 0;
  m_alpha_depth = 0;
  m_type = UNDEFINED;
  m_pixels = 0;
}

//==============================================================================
//  Image::Image()
//==============================================================================
Image::Image(const std::string &filename) {
  m_loaded = false;
  m_width = 0;
  m_height = 0;
  m_pixel_depth = 0;
  m_alpha_depth = 0;
  m_type = UNDEFINED;
  m_pixels = 0;
  load_form_file(filename);
}

//==============================================================================
//  Image::~Image()
//==============================================================================
Image::~Image() {
  clear();
}

//==============================================================================
//  Image::load_from_file()
//==============================================================================
bool Image::load_form_file(const std::string &filename) {
  log_init_multiple << "Load " << filename << " in Image::load_from_file()" << endl;

  if (m_loaded) {
    clear();
  }
  m_loaded = false;

  std::ifstream file;
  file.open(filename.c_str(), std::ios::binary);
  if (!file.is_open()) {
    return false;
  }

  bool rle = false;
  bool truecolor = false;
  unsigned int Currentpixel = 0;
  unsigned char ch_buf1, ch_buf2;
  unsigned char buf1[1000];

  unsigned char IDLength;
  unsigned char IDColorMapType;
  unsigned char IDImaget_ype;

  read_data(file, (char*)&IDLength, 1);
  read_data(file, (char*)&IDColorMapType, 1);

  if (IDColorMapType == 1) {
    return false;
  }

  read_data(file, (char*)&IDImaget_ype, 1);

  switch (IDImaget_ype) {
    case 2:
      truecolor = true;
      break;
    case 3:
      m_type = GREYSCALE;
      break;
    case 10:
      rle = true;
      truecolor = true;
      break;
    case 11:
      rle = true;
      m_type = GREYSCALE;
      break;
    default:
      return false;
  }

  file.seekg(5, std::ios::cur);

  file.seekg(4, std::ios::cur);
  read_data(file, (char*)&m_width, 2);
  read_data(file, (char*)&m_height, 2);
  read_data(file, (char*)&m_pixel_depth, 1);

  if (! ((m_pixel_depth == 8) || (m_pixel_depth ==  24) ||
        (m_pixel_depth == 16) || (m_pixel_depth == 32))) {
    return false;
  }

  read_data(file, (char*)&ch_buf1, 1);

  ch_buf2 = 15; //00001111;
  m_alpha_depth = ch_buf1 & ch_buf2;

  if (! ((m_alpha_depth == 0) || (m_alpha_depth == 8))) {
    return false;
  }

  if (truecolor) {
    m_type = RGB;
    if (m_pixel_depth == 32) {
      m_type = RGBA;
    }
  }

  if (m_type == UNDEFINED) {
    return false;
  }

  file.seekg(IDLength, std::ios::cur);

  m_pixels = (unsigned char*) malloc(m_width*m_height*(m_pixel_depth/8));

  if (!rle) {
    read_data(file, (char*)m_pixels, m_width*m_height*(m_pixel_depth/8));
  } else {
    while (Currentpixel < m_width*m_height-1) {

      read_data(file, (char*)&ch_buf1, 1);
      if ((ch_buf1 & 128) == 128) {   // this is an rle packet
        ch_buf2 = (unsigned char)((ch_buf1 & 127) + 1);   // how many pixels are encoded using this packet
        read_data(file, (char*)buf1, m_pixel_depth/8);
        for (unsigned int i=Currentpixel; i<Currentpixel+ch_buf2; ++i) {
          for (unsigned int j=0; j<m_pixel_depth/8; ++j) {
            m_pixels[i*m_pixel_depth/8+j] = buf1[j];
          }
        }
        Currentpixel += ch_buf2;
      } else {   // this is a raw packet
        ch_buf2 = (unsigned char)((ch_buf1 & 127) + 1);
        read_data(file, (char*)buf1, m_pixel_depth/8*ch_buf2);
        for (unsigned int i=Currentpixel; i<Currentpixel+ch_buf2; ++i) {
          for (unsigned int j=0; j<m_pixel_depth/8; ++j) {
            m_pixels[i*m_pixel_depth/8+j] =  buf1[(i-Currentpixel)*m_pixel_depth/8+j];
          }
        }
        Currentpixel += ch_buf2;
      }
    }
  }

  if (TGAReadError != 0) {
    clear();
    return false;
  }
  m_loaded = true;

  // swap BGR(A) to RGB(A)

  unsigned char temp;
  if ((m_type == RGB) || (m_type == RGBA)) {
    if ((m_pixel_depth == 24) || (m_pixel_depth == 32)) {
      for (unsigned int i=0; i<m_width*m_height; ++i)
      {
        temp = m_pixels[i*m_pixel_depth/8];
        m_pixels[i*m_pixel_depth/8] = m_pixels[i*m_pixel_depth/8+2];
        m_pixels[i*m_pixel_depth/8+2] = temp;
      }
    }
  }

  return true;
}

//==============================================================================
//  Image::clear()
//==============================================================================
void Image::clear() {
  if (m_pixels) {
    free(m_pixels);
  }

  m_pixels = 0;
  m_loaded = false;
  m_width = 0;
  m_height = 0;
  m_pixel_depth = 0;
  m_alpha_depth = 0;
  m_type = UNDEFINED;
}

//==============================================================================
//  Image::get_alpha_depth()
//==============================================================================
unsigned int Image::get_alpha_depth() {
  return m_alpha_depth;
}

//==============================================================================
//  Image::get_image_width()
//==============================================================================
unsigned int Image::get_image_width() {
  return m_width;
}

//==============================================================================
//  Image::get_image_height()
//==============================================================================
unsigned int Image::get_image_height() {
  return m_height;
}

//==============================================================================
//  Image::get_pixel_depth()
//==============================================================================
unsigned int Image::get_pixel_depth() {
  return m_pixel_depth;
}

//==============================================================================
//  Image::get_pixels()
//==============================================================================
unsigned char* Image::get_pixels() {
  return m_pixels;
}

//==============================================================================
//  Image::get_image_type()
//==============================================================================
Image::Image_type Image::get_image_type() {
  return m_type;
}

//==============================================================================
//  Image::create_empty()
//==============================================================================
void Image::create_empty() {
  clear();

  // create a default texture
  m_width = 64;
  m_height = 64;
  m_type = RGB;
  m_pixel_depth = 24;
  m_alpha_depth = 0;

  m_pixels = new unsigned char[m_width*m_height*m_pixel_depth];
  memset(m_pixels, 255, m_width*m_height*sizeof(char)*m_pixel_depth/8);
  // top line
  memset(m_pixels, 0, m_width*sizeof(char)*m_pixel_depth/8);
  // left line
  for(int i=0; i<m_height; ++i) {
    m_pixels[i*m_width*sizeof(char)*m_pixel_depth/8  ] = 0;
    m_pixels[i*m_width*sizeof(char)*m_pixel_depth/8+1] = 0;
    m_pixels[i*m_width*sizeof(char)*m_pixel_depth/8+2] = 0;
  }
  m_loaded = true;
}
