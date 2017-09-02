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

#include "../framework/framework.hpp"
#include "../framework/base_sdl/base_sdl.hpp"
#include "../framework/renderer_opengl/renderer_opengl.hpp"
#include "../framework/misc/log.hpp"
#include "../framework/model/batch.hpp"

#include "../framework/scene/camera.hpp"
#include "../framework/scene/scene_portal.hpp"
#include "../framework/physics/collision_set_bsp.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

void render_debug_lines();

Base* base = (Base *)new Base_SDL();
Renderer* renderer = (Renderer *)new Renderer_opengl();

int main(int argc, char* argv[])
{
  bool use_collision = true;
  bool tree_debug = false;

  Camera* camera = new Camera_fps();
  camera->get_controller()->set_position( Vector3f(100,100,50) );

  base->init();
  base->init_window( 800, 600, false);
  base->set_caption("Portal Engine");

  renderer->init();
  renderer->set_viewport(0, 0, base->get_window_width(), base->get_window_height());

  std::ifstream file("config.cfg");
  std::string s;
  std::string name;
  if(!file) {
    log_error << "unable to open config.cfg" << endl;
    return 0;
  }

  while( file >> s) {
    if(s == "map") {
      file >> name;
    }
  }

  Scene_portal scene;
  std::string tmp = name;
  scene.load_proc(tmp.append(".proc"));

  Collision_set_bsp bsp;
  tmp = name;
  bsp.load_cm(tmp.append(".cm"));

  renderer->upload_textures();

  static GLfloat white_light[]=  {1.0f,1.0f,1.0f,1.0f};
  static GLfloat white_light2[]=  {1.0f,0.8f,0.8f,1.0f};
  static GLfloat ambient_light[]={0.3f,0.3f,0.3f,1.0f};

  static GLfloat light_pos[] = {150.0f, 130.0f, 120.0f, 0.0f};
  static GLfloat light_pos2[] = {-120.0f, +120.0f, -120.0f, 0.0f};

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,white_light);
  glLightfv(GL_LIGHT0, GL_AMBIENT,ambient_light);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,white_light2);
  glEnable(GL_LIGHT1);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_LEQUAL);

  while( base->update() ) {
    if( base->is_key_released(KEY_P) ) {
      portal_debug = !portal_debug;
    }
    if( base->is_key_released(KEY_C) ) {
      use_collision = !use_collision;
    }
    if( base->is_key_released(KEY_B) ) {
      bsp_debug = !bsp_debug;
    }
    if( base->is_key_released(KEY_T) ) {
      tree_debug = !tree_debug;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);

    Vector3f start = camera->get_position();
    camera->update();
    Vector3f end = camera->get_position();

    if(use_collision) {
      Vector3f end_collided = start;
      while(end_collided != end) {
        end_collided = end;
        bsp.trace( start, end, 10.0f);
      }
      camera->get_controller()->set_position(end_collided);
    }

    renderer->set_view(camera);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    scene.render(camera);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    if(portal_debug) {
      render_debug_lines();
    }

    glDisable(GL_DEPTH_TEST);

    if(tree_debug) {
      bsp.render_tree();
    }

    if(bsp_debug) {
      bsp.render_brushes();
    }

    glEnable(GL_DEPTH_TEST);

    glFlush();
    base->swap_buffers();
    renderer->next_frame();
  }

  renderer->close();
  base->close();

  delete camera;
  delete renderer;
  delete base;
}

void render_debug_lines() {
  glColor3f(1,0,0);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho( 0, base->get_window_width(), base->get_window_height(), 0, 1, 10);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0, 0, -5);
  glDisable(GL_DEPTH_TEST);

  glBegin(GL_LINES);
  int num_lines = portal_debug_lines.size();
  for(int i=0; i<num_lines; i++) {
    glVertex2i( portal_debug_lines[i].x, base->get_window_height()-portal_debug_lines[i].y );
  }
  portal_debug_lines.clear();
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
