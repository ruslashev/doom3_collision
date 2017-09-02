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

#ifndef  _TEXTURE_
#define  _TEXTURE_ 1

#include <vector>
#include <string>

class Image;

//==============================================================================
//  Texture
//==============================================================================
class Texture {
public:
  Texture(const std::string& name);
  ~Texture();

  enum Type { BYTE, FLOAT };
  enum Dimension { TEX_1D, TEX_2D, TEX_3D, TEX_CUBE };

  void set_use_nearest( bool n_use_nearest) { m_use_nearest = n_use_nearest; }
  void set_use_clamp( bool n_use_clamp) { m_use_clamp = n_use_clamp; }

  unsigned int get_tex_id() { return m_tex_id; }

  void set_image(Image* image);
  void set_image(int index, Image* image);
  virtual bool upload_texture()=0;

  void clear();
  void set_num_images(int count);
protected:
  std::vector<Image *> m_images;
  std::string m_name;

  Type m_type;
  Dimension m_dimension;

  bool m_use_nearest;
  bool m_use_clamp;

  unsigned int m_tex_id;
};

#endif /* TEXTURE */

