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

#include "collision_set_bsp.hpp"
#include "../misc/log.hpp"
#include "../math/vector.hpp"
#include "../math/geometry.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>

#define EPSILON 0.001f

Set<Collision_brush *> debug_bsp_collision_brushes;
bool bsp_debug;

//==============================================================================
//  Kd_tree_node::trace()
//==============================================================================
void Kd_tree_node::trace(const Vector3f & start, Vector3f & end, float radius) {
  // walk through the k-D tree to find brushes..
  int num_brushes = m_brushes.size();

  if(num_brushes) {
    for(int i=0; i<num_brushes; ++i) {
      m_brushes[i]->trace(start, end, radius, end);
      if(bsp_debug) {
        debug_bsp_collision_brushes.add(m_brushes[i]);
      }
    }
  }

  if(index >=0 ) { // have childs, find the right child for the brush
    // very fast plane check...
    if( (start[index] >= distance + radius) && (end[index] >= distance + radius) ) {
      child_front->trace( start, end, radius );
    } else if( (start[index] <= distance - radius) && (end[index] <= distance - radius) ) {
      child_back->trace( start, end, radius );
    } else {
      // check the node to trace first ...
      if( start[index] >= distance + radius ) {
        child_front->trace( start, end, radius );
        child_back->trace( start, end, radius );
      } else {
        child_back->trace( start, end, radius );
        child_front->trace( start, end, radius );
      }
    }
  }
}

//==============================================================================
//  Kd_tree_node::insert_brush()
//==============================================================================
void Kd_tree_node::insert_brush(Collision_brush* brush) {
  if(index >=0 ) { // have childs, find the right child for the brush
    // very fast plane check...
    if( (brush->m_min[index] >= distance) && (brush->m_max[index] >= distance) ) {
      child_front->insert_brush( brush );
    } else if( (brush->m_min[index] <= distance) && (brush->m_max[index] <= distance) ) {
      child_back->insert_brush( brush );
    } else {
      // plane interstect brush
      // m_brushes.add( brush ); (insert in both children!!
      child_front->insert_brush( brush );
      child_back->insert_brush( brush );
    }
  } else {
    m_brushes.add( brush );
  }
}

//==============================================================================
//  Collision_set_bsp::trace()
//==============================================================================
void Collision_set_bsp::trace(const Vector3f & start, Vector3f & end, float radius) {
  if(m_kd_tree) {
    m_kd_tree->trace( start, end, radius );
  }
}

//==============================================================================
//  Collision_brush::trace()
//==============================================================================
void Collision_brush::trace(const Vector3f & start, const Vector3f & end, float radius, Vector3f & output) {
  float min_fraction = -99999.0f;
  int min_plane = -1;

  int num_planes = m_planes.size();

  for (int i=0; i<num_planes; ++i) {
    float start_distance, end_distance;

    start_distance = m_planes[i].distance( start ) - radius;
    end_distance   = m_planes[i].distance( end   ) - radius;

    // make sure the trace isn't completely on one side of the brush
    if (start_distance > 0 && end_distance > 0)	{
      // both are in front of the plane, its outside of this brush
      return;
    }
    if (start_distance <= 0 || end_distance >= 0) {
      // start is behind this plane
      continue;
    }

    if( end_distance > min_fraction) {
      min_fraction = end_distance;
      min_plane = i;
    }
  }

  if(min_plane >= 0) {
    if( -10.0f < min_fraction && min_fraction < 0.0f ) {
      output = end - (min_fraction-EPSILON) * m_planes[min_plane].normal;
    } else {
      log_warning << "min_fraction to large! (" << min_fraction << ")" << endl;
    }
  }
}

//==============================================================================
//  Debug functions
//==============================================================================
void render_cube(Vector3f min, Vector3f max) {
  glVertex3f( min.x, max.y, min.z );
  glVertex3f( min.x, min.y, min.z );

  glVertex3f( min.x, max.y, min.z );
  glVertex3f( min.x, max.y, max.z );

  glVertex3f( min.x, max.y, min.z );
  glVertex3f( max.x, max.y, min.z );


  glVertex3f( max.x, min.y, max.z );
  glVertex3f( max.x, min.y, min.z );

  glVertex3f( max.x, min.y, max.z );
  glVertex3f( min.x, min.y, max.z );

  glVertex3f( max.x, min.y, max.z );
  glVertex3f( max.x, max.y, max.z );


  glVertex3f( max.x, max.y, max.z );
  glVertex3f( max.x, max.y, min.z );

  glVertex3f( max.x, max.y, max.z );
  glVertex3f( min.x, max.y, max.z );


  glVertex3f( min.x, max.y, max.z );
  glVertex3f( min.x, min.y, max.z );

  glVertex3f( min.x, min.y, min.z );
  glVertex3f( min.x, min.y, max.z );


  glVertex3f( max.x, min.y, min.z );
  glVertex3f( max.x, max.y, min.z );

  glVertex3f( max.x, min.y, min.z );
  glVertex3f( min.x, min.y, min.z );
}

//==============================================================================
//  Kd_tree_node::render_debug()
//==============================================================================
void Kd_tree_node::render_debug(Vector3f min, Vector3f max) {
  if(index<0) {
    return;
  }

  switch(index) {
    case 0:		// yz plane;
      render_cube( Vector3f(distance, min.y, min.z), Vector3f(distance, max.y, max.z));
      child_front->render_debug( Vector3f(distance, min.y, min.z), max );
      child_back->render_debug( min, Vector3f(distance, max.y, max.z) );
      break;
    case 1:		// xz plane;
      render_cube( Vector3f(min.x, distance, min.z), Vector3f(max.x, distance, max.z));
      child_front->render_debug( Vector3f(min.x, distance, min.z), max );
      child_back->render_debug( min, Vector3f(max.x, distance, max.z) );
      break;
    case 2:		// xy plane;
      render_cube( Vector3f(min.x, min.y, distance), Vector3f(max.x, max.y, distance));
      child_front->render_debug( Vector3f(min.x, min.y, distance), max );
      child_back->render_debug( min, Vector3f(max.x, max.y, distance) );
      break;
  }
}

//==============================================================================
//  Collision_set_bsp::render_tree()
//==============================================================================
void Collision_set_bsp::render_tree() {
  glColor3f(0, 1, 0);
  glBegin(GL_LINES);
  if(m_kd_tree) {
    m_kd_tree->render_debug(Vector3f(-1000,-1000,-1000), Vector3f(1000,1000,1000));
  }
  glEnd();
}

//==============================================================================
//  Collision_set_bsp::render_brushes()
//==============================================================================
void Collision_set_bsp::render_brushes() {
  if(bsp_debug) {
    int num_collision_brushes  = debug_bsp_collision_brushes.size();

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    for(int i=0; i<num_collision_brushes; ++i) {
      render_cube(debug_bsp_collision_brushes[i]->m_min, debug_bsp_collision_brushes[i]->m_max);
    }
    glEnd();

    debug_bsp_collision_brushes.clear();
  }
}


//============================================================================//
//                                                                            //
//	Read from file functions (format: .cm, doom3)  						  //
//                                                                            //
//============================================================================//
inline std::string cm_get_next_value(std::ifstream & file) {
  std::string s;
  while( file >> s) {
    if( s == "/*" ) {
      while( s != "*/") {
        file >> s;
      }
    } else if( s == "{" || s == "}") {
    } else if( s == "(" || s == ")") {
    } else {
      return s;
    }
  }
  return "EOF";
}

inline std::string cm_get_next_string(std::ifstream & file) {
  std::string s = cm_get_next_value(file);

  return s.substr(1, s.size()-2);
}

#define cm_get_next_float(x) atof( cm_get_next_value(x).c_str() )
#define cm_get_next_int(x) atoi( cm_get_next_value(x).c_str() )

//==============================================================================
//  Collision_set_bsp::load_cm()
//==============================================================================
void Collision_set_bsp::load_cm(const std::string & name) {
  log_function << "Load " << name << " in Collision_set_bsp::load_cm()" << endl;

  std::ifstream file(name.c_str());
  std::string s;

  if(!file) {
    log_error << "unable to open " << name << endl;
    return;
  }

  while( file >> s) {
    if(s == "vertices") {
      /*		    int num_vertices = cm_get_next_int(file);

                log_debug << "load " << num_vertices << " vertices" << endl;

                m_vertices.resize(num_vertices);

                for(int i=0; i<num_vertices; ++i) {
                Vector3f vertex;
                vertex.x = cm_get_next_float(file);
                vertex.y = cm_get_next_float(file);
                vertex.z = cm_get_next_float(file);

                m_vertices[i] = vertex;
                }
                */
    } else if( s == "brushes") {
      log_debug << "load brushes" << endl;

      int brush_memory = cm_get_next_int(file);

      Collision_brush *brush = new Collision_brush();
      while(  brush->read_from_file(file) ) {
        m_brushes.add(brush);
        if(m_kd_tree) {
          m_kd_tree->insert_brush(brush);
        }
        brush = new Collision_brush();
      }
      // hack, only load first collision model
      break;
    } else if( s == "nodes") {
      log_debug << "load k-D tree" << endl;

      m_kd_tree = new Kd_tree_node();
      m_kd_tree->read_from_file(file);
    }
  }
  file.close();

  log_success << name << " loaded succesfully " << endl;
}

//==============================================================================
//  Collision_brush::read_from_file()
//==============================================================================
bool Collision_brush::read_from_file(std::ifstream &file) {
  std::string tmp = cm_get_next_value(file);
  if(tmp == "EOF" || tmp == "collisionModel") {
    log_debug << "end of file" << endl;
    return false;
  }
  int num_planes = atoi( tmp.c_str() );

  m_planes.resize(num_planes);
  // planes
  Plane plane;
  for(int i=0; i<num_planes; ++i) {
    plane.normal.x = cm_get_next_float(file);
    plane.normal.y = cm_get_next_float(file);
    plane.normal.z = cm_get_next_float(file);
    plane.d = cm_get_next_float(file);

    m_planes[i] = plane;
  }
  // bounding box
  m_min.x = cm_get_next_float(file);
  m_min.y = cm_get_next_float(file);
  m_min.z = cm_get_next_float(file);

  m_max.x = cm_get_next_float(file);
  m_max.y = cm_get_next_float(file);
  m_max.z = cm_get_next_float(file);

  m_solid = cm_get_next_string(file);

  return true;
}

//==============================================================================
//  Kd_tree_node::read_from_file()
//==============================================================================
void Kd_tree_node::read_from_file(std::ifstream &file) {
  index    = cm_get_next_int(file);
  distance = cm_get_next_float(file);

  if(index >= 0) {  // two childs...
    child_front = new Kd_tree_node();
    child_back = new Kd_tree_node();

    child_front->read_from_file(file);
    child_back->read_from_file(file);
  }
}
