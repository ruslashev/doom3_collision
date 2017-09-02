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

#include "scene_portal.hpp"
#include "../misc/log.hpp"
#include "../math/vector.hpp"
#include "../base.hpp"
#include "camera.hpp"

#include <string>
#include <sstream>
#include <iostream>

//==============================================================================
//  Vertex_doom3
//==============================================================================
struct Vertex_doom3 {
    Vector3f vertex;
    Vector2f texcoord;
    Vector3f normal;
};


//==============================================================================
//  Debug functions
//==============================================================================
bool portal_debug = false;
Set<Vector2i> portal_debug_lines;
int portal_debug_areas_rendered = 0;

void portal_add_debug_line(Vector2i vec1, Vector2i vec2) {
     portal_debug_lines.add(vec1);
     portal_debug_lines.add(vec2);
}
    
//==============================================================================
//  Scene_portal::render()
//==============================================================================
void Scene_portal::render(Camera* camera) {     
//  find start area..
	int start_area = get_area( camera->get_position() );
	
    std::stringstream caption;    
    caption << "Portal Engine, sector: " << (-1-start_area);
    caption << ", fps: " << base->get_fps();
    caption << ", sectors rendered: " << portal_debug_areas_rendered; 
    caption << " c toggles collisions, p:portals, b:brushes and t:kd-tree)";
	base->set_caption( (caption.str()).c_str() );

	portal_debug_areas_rendered = 0;

	if(start_area >= 0) {
	    // you're in the void!!
	    int num_areas = m_areas.size();
	    for(int i=0; i<num_areas; ++i) {
            m_areas[i]->render( camera, Vector2i(0, 0), Vector2i(base->get_window_width(), base->get_window_height()) );
        }   
	} else {
	    // rename start_area: -1 -> 0, -2 -> 1
	    start_area = -1-start_area;
	    m_areas[start_area]->render( camera, Vector2i(0, 0), Vector2i(base->get_window_width(), base->get_window_height()) );
    }       
     
    renderer->set_renderport(0,0, base->get_window_width(), base->get_window_height());    
}

//==============================================================================
//  Portal_area::render()
//==============================================================================
void Portal_area::render(Camera* camera, Vector2i min, Vector2i max) {
	//  hack!!?! only render area once each frame
    if(m_frame_rendered == renderer->get_frame()) {
        return;
    }
    m_frame_rendered = renderer->get_frame();
    portal_debug_areas_rendered++;
    
    //  set renderport, prevent visible 'rounding-error' caps
	renderer->set_renderport( min.x, min.y, max.x-min.x+1, max.y-min.y+1 );
	
	//  render batches in area..    
    int num_batches = m_batches.size();
    for (int j = 0; j < num_batches; ++j) {
        renderer->bind_texture(m_textures[j]);
        m_batches[j]->render();
    }
    
    //  render portals
	int num_portals = m_portals.size();	
	
    for (int j = 0; j < num_portals; ++j) {
        m_portals[j]->render_from_area( camera, m_index, min, max );
    }
}

//==============================================================================
//  Portal_portal::render_from_area()
//==============================================================================
void Portal_portal::render_from_area(Camera* camera, int index, Vector2i min, Vector2i max) {
    // check if vertices are projected for visibility check    
    if(m_frame_rendered != renderer->get_frame()) {
        m_frame_rendered = renderer->get_frame();
        
        if( !(m_visible = check_visibility(camera)) ) {
            // portal is outside frustrum            
            return;
        }
        transform_points();
    }

    // check visibility
    if(!m_visible) {
        return;
    } else if(m_visible<0) {
    // intersection of portal and front plane of frustum
    // set min and max to renderport
        m_transformed_min = Vector2i(0,0);
        m_transformed_max = Vector2i(base->get_window_width(), base->get_window_height());    
    
    }
    
    // clip min and max
    if(min.x < m_transformed_min.x) min.x = m_transformed_min.x;
    if(max.x > m_transformed_max.x) max.x = m_transformed_max.x;
    
    if(min.y < m_transformed_min.y) min.y = m_transformed_min.y;
    if(max.y > m_transformed_max.y) max.y = m_transformed_max.y;
            
    // render area if visible
    if( (max.x > min.x) && (max.y > min.y) ) {
        if(index == m_area_pos) {
          m_scene->get_area( m_area_neg )->render( camera, min, max );
        } else {
          m_scene->get_area( m_area_pos )->render( camera, min, max );
        }    

        if(portal_debug) {
            portal_add_debug_line( min, Vector2i(min.x, max.y) );
            portal_add_debug_line( min, Vector2i(max.x, min.y) );
            portal_add_debug_line( Vector2i(min.x, max.y), max );
            portal_add_debug_line( Vector2i(max.x, min.y), max );
        }    
    }    
}

//==============================================================================
//  Portal_portal::check_visibility()
//	0 = invisible (outside frustrum), 1 = visible, -1 = intersects frontplane
//==============================================================================
int Portal_portal::check_visibility(Camera* camera) {
    int num_points = m_points.size();
    int i;    
    
    // check front plane.
	bool all_front = true;
	bool all_back  = true;
 	
	for(i=0; i<num_points; ++i) {
	    if(!camera->get_frustum_plane(FRUSTUM_FRONT).is_in_front(m_points[i])) {
	        all_front = false;
	    } else {
	        all_back = false;
	    }    
	}
	if(all_back) {
       return 0;
    }
    
    // check the other planes..    
	for(int j=FRUSTUM_FRONT+1; j<FRUSTUM_BACK; ++j) {
	    bool all_back = true;
    	for(i=0; i<num_points; ++i) {
    		if(camera->get_frustum_plane(j).is_in_front(m_points[i])) {
	        	all_back = false;
	        	break;
	        }  
    	}
    	if(all_back) {    
    	    return 0;
    	}    
    }
    
    // return 1 if portal is in frustum and -1 if portal intersects frontplane
    return (all_front?1:-1);
}    

//==============================================================================
//  Portal_portal::transform_points()
//==============================================================================
void Portal_portal::transform_points() {
    int num_points = m_points.size();
    
    m_transformed_min = Vector2i( 99999, 99999);
    m_transformed_max = Vector2i(-99999,-99999);
    
    for(int i=0; i<num_points; ++i) {
        if(renderer->project( m_points[i], m_transformed_points[i].x, m_transformed_points[i].y)) {
            // find maximum and minimum x, y and z values of transformed points to construct renderports.
            if(m_transformed_points[i].x > m_transformed_max.x) {
                m_transformed_max.x = m_transformed_points[i].x;
            } 
            if(m_transformed_points[i].x < m_transformed_min.x) {
                m_transformed_min.x = m_transformed_points[i].x;
            }
        
            if(m_transformed_points[i].y > m_transformed_max.y) {
                m_transformed_max.y = m_transformed_points[i].y;
            } 
            if(m_transformed_points[i].y < m_transformed_min.y) {
                m_transformed_min.y = m_transformed_points[i].y;
            }
        }    
    }
}

//==============================================================================
//  Scene_portal::get_area()
//==============================================================================
int Scene_portal::get_area(const Vector3f & position) {
	if(!m_nodes.size()) {
     	return 0;
    }
    
    // walk through nodes...
	Doom3_node *node = &m_nodes[0];
	
	while(true) {
	    if( node->plane.is_in_front( position ) ) { // in front
	    	if( node->pos_child > 0 ) {
	    	    node = &m_nodes[ node->pos_child ];
	    	} else {
	    	    return node->pos_child;
      		}        
     	} else { // backside
	    	if( node->neg_child > 0 ) {
	    	    node = &m_nodes[ node->neg_child ];	    	    
	    	} else {
	    	    return node->neg_child;
      		}        
     	}
	}
}

//==============================================================================
//  Scene_portal::get_area_index_by_name()
//==============================================================================
int Scene_portal::get_area_index_by_name(const std::string & name) {
    int num_areas = m_areas.size();
    
    for(int i=0; i<num_areas; ++i) {
        if(m_areas[i]->get_name() == name) {
       		return i;
  		}  		
    }
    return -1;
}

//============================================================================//
//                                                                            //
//	Read from file functions (format: .proc, doom3)  						  //
//                                                                            //
//============================================================================//

inline std::string proc_get_next_value(std::ifstream & file) {
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
    return false;
}  

inline std::string proc_get_next_string(std::ifstream & file) {
    std::string s = proc_get_next_value(file);
    
    return s.substr(1, s.size()-2);
}

#define proc_get_next_float(x) atof( proc_get_next_value(x).c_str() )
#define proc_get_next_int(x) atoi( proc_get_next_value(x).c_str() ) 

//==============================================================================
//  Scene_portal::load_proc()
//==============================================================================
void Scene_portal::load_proc(const std::string & name) {
   	log_function << "Load " << name << " in Scene_portal::load_proc()" << endl;
	
 	std::ifstream file(name.c_str());
 	std::string s;
  	
	if(!file) {
		log_error << "unable to open " << name << endl;
		return;
	}
	
	while( file >> s) {
	    if(s == "model") {
// areas
	        std::string name = proc_get_next_string(file);
       		Portal_area* portal_area = new Portal_area(name, m_areas.size());
       		portal_area->read_from_file(file);
       		m_areas.add(portal_area);
        } else if (s == "interAreaPortals") {
// portals
			int num_areas   = proc_get_next_int(file);
			int num_portals = proc_get_next_int(file);

			log_debug << "load " << num_portals << " portals" << endl;

			m_portals.resize(num_portals);

			for(int i=0; i<num_portals; ++i) {
			    Portal_portal* portal_portal = new Portal_portal(this);
			    portal_portal->read_from_file(file);
			    m_portals[i] = portal_portal;
			}    
        } else if (s == "nodes") {
// nodes
		    int num_nodes = proc_get_next_int(file);
      
			log_debug << "load " << num_nodes << " nodes" << endl;
			
            m_nodes.resize(num_nodes);
            
            for(int i=0; i<num_nodes; ++i) {
                Doom3_node node;
                node.plane.normal.x = proc_get_next_float(file);
                node.plane.normal.y = proc_get_next_float(file);
                node.plane.normal.z = proc_get_next_float(file);
                node.plane.d = proc_get_next_float(file);
                
                node.pos_child = proc_get_next_int(file);
                node.neg_child = proc_get_next_int(file);

                if(node.pos_child<0) {
                	std::stringstream name;
                	name << "_area" << (-1-node.pos_child);
                	node.pos_child = -1-get_area_index_by_name(name.str());
               	}

                if(node.neg_child<0) {
                	std::stringstream name;
                	name << "_area" << (-1-node.neg_child);
                	node.neg_child = -1-get_area_index_by_name(name.str());
               	}
               	
                m_nodes[i] = node;
            }
	    }    
	}
	file.close();
	
	log_success << name << " loaded succesfully " << endl;
}
    
//==============================================================================
//  Portal_portal::read_from_file()
//==============================================================================
void Portal_portal::read_from_file(std::ifstream &file) {
    int num_points = proc_get_next_int( file );
    int pos_area   = proc_get_next_int( file );
    int neg_area   = proc_get_next_int( file );    
    
    m_points.resize(num_points);
    m_transformed_points.resize(num_points);
    
    for(int i=0; i<num_points; ++i) {
        Vector3f tmp;
        tmp.x = proc_get_next_float( file );
        tmp.y = proc_get_next_float( file );
        tmp.z = proc_get_next_float( file );                
        
        m_points[i] = tmp;
    }
    
    std::stringstream name_pos;
    name_pos << "_area" << pos_area;
    m_area_pos = m_scene->get_area_index_by_name(name_pos.str());
    std::stringstream name_neg;    
    name_neg << "_area" << neg_area;
    m_area_neg = m_scene->get_area_index_by_name(name_neg.str());    
    
    if(m_area_pos>=0) {
        m_scene->get_area(m_area_pos)->add_portal(this);
    }    
    if(m_area_neg>=0) {
        m_scene->get_area(m_area_neg)->add_portal(this);
    }    
}

//==============================================================================
//  Portal_area::read_from_file()
//==============================================================================
void Portal_area::read_from_file(std::ifstream &file) {
    log_function << "Load area (model) " << m_name << " in Portal_area::read_from_file()" << endl;
   	// read num surfaces;       		
    int num_surfaces = proc_get_next_int(file);
    log_debug << num_surfaces << " surface(s)" << endl;
    
    for(int i=0; i<num_surfaces; i++) {
    	// create new batch...
        Batch* batch = renderer->create_batch();
        batch->add_format( ATT_VERTEX,   ATT_FLOAT, 3, 0, 0);
        batch->add_format( ATT_TEXCOORD, ATT_FLOAT, 2,12, 0);
        batch->add_format( ATT_NORMAL,   ATT_FLOAT, 3,20, 0);                     
        batch->set_primitive_type(PRIM_TRIANGLES);
        Set<Vertex_doom3> *vertices = new Set<Vertex_doom3>();                
        Set<unsigned int> *indices = new Set<unsigned int>();
                     
        // read surface...
        std::string name = proc_get_next_string(file);
        name.append(".tga");
        
       	Texture* texture = renderer->get_texture_from_file(name.c_str());
        m_textures.add( texture );
        
        int num_verts = proc_get_next_int(file);
        int num_ind = proc_get_next_int(file);             
            
        vertices->resize( num_verts );
        indices->resize( num_ind );
            
        for(int j=0; j<num_verts; j++) {
            Vertex_doom3 tmp_vertex;
            tmp_vertex.vertex.x = atof( proc_get_next_value(file).c_str() );
            tmp_vertex.vertex.y = atof( proc_get_next_value(file).c_str() );
            tmp_vertex.vertex.z = atof( proc_get_next_value(file).c_str() );

            tmp_vertex.texcoord.x = atof( proc_get_next_value(file).c_str() );
            tmp_vertex.texcoord.y = atof( proc_get_next_value(file).c_str() );

            tmp_vertex.normal.x = atof( proc_get_next_value(file).c_str() );
            tmp_vertex.normal.y = atof( proc_get_next_value(file).c_str() );
            tmp_vertex.normal.z = atof( proc_get_next_value(file).c_str() );
                    
            vertices->get_index(j) = (tmp_vertex);
        }
        for(int j=0; j<num_ind; j++) {
            indices->get_index(j) = ( atoi( proc_get_next_value(file).c_str() ) );
		}    
        // save batch..
        log_debug << "  - surface, num_of_verts: " << vertices->size() << ", num_of_indices: " << indices->size() << endl;
        batch->set_vertices( vertices->get_array(), vertices->size(), sizeof(Vertex_doom3));
        batch->set_indices( indices->get_array(), indices->size(), sizeof(unsigned int));             		     
        m_batches.add(batch);
    }
	log_success << m_name << " loaded succesfully " << endl;    
}

