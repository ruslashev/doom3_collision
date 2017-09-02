all:
	g++ doom3_collision/main.cpp framework/base.cpp \
		framework/base_sdl/base_sdl.cpp framework/material/image.cpp \
		framework/material/texture.cpp framework/math/geometry.cpp \
		framework/math/matrix.cpp framework/math/vector.cpp \
		framework/misc/log.cpp framework/model/batch.cpp \
		framework/model/controller.cpp framework/model/model.cpp \
		framework/physics/collision_set_bsp.cpp framework/renderer.cpp \
		framework/renderer_opengl/renderer_opengl.cpp \
		framework/scene/camera.cpp framework/scene/scene_portal.cpp

