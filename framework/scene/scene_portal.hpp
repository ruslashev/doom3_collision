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

#ifndef _PORTAL_SCENE_
#define _PORTAL_SCENE_ 1

#include "../misc/set.hpp"
#include "../model/batch.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"
#include "../math/geometry.hpp"
#include "../renderer.hpp"
#include "../material/texture.hpp"

#include <string>

class Portal_portal;
class Scene_portal;
class Camera;

//==============================================================================
//  Doom3_node
//==============================================================================
struct Doom3_node {
  Plane plane;
  int pos_child, neg_child;
};

//==============================================================================
//  Vector2i
//==============================================================================
class Vector2i {
public:
  Vector2i() {}
  Vector2i(int n_x, int n_y) : x(n_x), y(n_y) {}

  int x, y;
};

//==============================================================================
//  Portal_area
//==============================================================================
class Portal_area {
public:
  Portal_area(const std::string & name, int index) : m_name(name), m_index(index) {}
  const std::string & get_name() const { return m_name; }

  void render(Camera* camera, Vector2i min, Vector2i max);

  void add_portal(Portal_portal *portal) { m_portals.add( portal ); }

  void read_from_file(std::ifstream &file);
private:
  std::string m_name;
  int m_index;

  Set<Texture *> m_textures;
  Set<Batch *> m_batches;
  Set<Portal_portal *> m_portals;

  int m_frame_rendered;
};

//==============================================================================
//  Portal_portal
//==============================================================================
class Portal_portal {
public:
  Portal_portal(Scene_portal* scene) : m_frame_rendered(0) { m_scene = scene; }

  void render_from_area(Camera* camera, int index, Vector2i min, Vector2i max);

  void read_from_file(std::ifstream &file);

  int  check_visibility(Camera* camera);
  void transform_points();
private:
  Scene_portal* m_scene;

  Vector2i m_transformed_min;
  Vector2i m_transformed_max;

  Set<Vector3f> m_points;
  Set<Vector2i> m_transformed_points;
  int m_area_pos;
  int m_area_neg;

  int m_frame_rendered;
  int m_visible;
};

//==============================================================================
//  Scene_portal
//==============================================================================
class Scene_portal {
public:
  Scene_portal() {}

  void render(Camera* camera);
  void load_proc(const std::string & name);

  Portal_area * get_area(int i) { return m_areas[i]; }
  int get_area(const Vector3f & position);

  int get_area_index_by_name(const std::string & name);
private:
  Set<Portal_area *> m_areas;
  Set<Portal_portal *> m_portals;
  Set<Doom3_node> m_nodes;
};

//==============================================================================
//  Debug functions
//==============================================================================
extern bool portal_debug;
extern int portal_debug_areas_rendered;
extern Set<Vector2i> portal_debug_lines;

void portal_add_debug_line(Vector2i vec1, Vector2i vec2);

#endif /* _PORTAL_SCENE_ */
