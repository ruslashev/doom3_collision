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

#ifndef  _IMAGE_
#define  _IMAGE_ 1

#include <string>

//==============================================================================
//  Image
//==============================================================================
class Image
{
public:
  Image();
  Image(const std::string &filename);
  virtual ~Image();

  enum Image_type {UNDEFINED, RGB, RGBA, GREYSCALE};

  bool load_form_file(const std::string &filename);

  void clear();
  void create_empty();

  unsigned int get_alpha_depth();
  unsigned int get_image_width();
  unsigned int get_image_height();
  unsigned int get_pixel_depth();

  unsigned char* get_pixels();
  Image_type get_image_type();
protected:
  unsigned char *m_pixels;
  unsigned int m_pixel_depth;
  unsigned int m_alpha_depth;
  unsigned int m_height;
  unsigned int m_width;
  Image_type m_type;

  bool m_loaded;
};

#endif /* _IMAGE_ */

