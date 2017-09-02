                  /*--.          .-"-.
                 /   ._.        / ´ ` \
                 \_  (__\       \_°v°_/
                 //   \\        //   \\
                ((     ))      ((     ))
 ¤¤¤¤¤¤¤¤¤¤¤¤¤¤--""---""--¤¤¤¤--""---""--¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤                 |||            |||                                               ¤
 ¤  Author's note:  |              |                                                ¤
 ¤                                                                                  ¤
 ¤  This file is part of work done by Emil Persson, aka Humus.                      ¤
 ¤  You're free to use the code in any way you like, modified, unmodified           ¤
 ¤  or cut'n'pasted into your own work. But for the good of the whole               ¤
 ¤  programming community I will ask you to as long as possible and to the          ¤
 ¤  extent you find suitable to follow these points:                                ¤
 ¤   * If you use this file and it's contents unmodified, please leave this note.   ¤
 ¤   * If you use a major part of the file in your app, please credit the author(s) ¤
 ¤     in one way or the other as you find suitable, for instance a small notice    ¤
 ¤     in the readme file may do, or perhaps a link to the authors site.            ¤
 ¤   * Share your work and ideas too as much as you can.                            ¤
 ¤    _______                                                                       ¤
 ¤  /` _____ `\;,    Humus                                                          ¤
 ¤ (__(^===^)__)';,  emiper-8@student.luth.se                         ___           ¤
 ¤   /  :::  \   ,;  ICQ #47010716                                  /^   ^\         ¤
 ¤  |   :::   | ,;'                                                ( Ö   Ö )        ¤
 ¤¤¤'._______.'`¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤--°oOo--(_)--oOo°--¤¤*/

#include "gl_extensions.hpp"

bool GL_ARB_depth_texture_supported              = false;
bool GL_ARB_fragment_program_supported           = false;
bool GL_ARB_fragment_shader_supported            = false;
bool GL_ARB_multisample_supported                = false;
bool GL_ARB_multitexture_supported               = false;
bool GL_ARB_occlusion_query_supported            = false;
bool GL_ARB_shader_objects_supported             = false;
bool GL_ARB_shading_language_100_supported       = false;
bool GL_ARB_shadow_supported                     = false;
bool GL_ARB_shadow_ambient_supported             = false;
bool GL_ARB_texture_compression_supported        = false;
bool GL_ARB_texture_cube_map_supported           = false;
bool GL_ARB_texture_env_add_supported            = false;
bool GL_ARB_texture_env_combine_supported        = false;
bool GL_ARB_texture_env_crossbar_supported       = false;
bool GL_ARB_texture_env_dot3_supported           = false;
bool GL_ARB_transpose_matrix_supported           = false;
bool GL_ARB_vertex_blend_supported               = false;
bool GL_ARB_vertex_buffer_object_supported       = false;
bool GL_ARB_vertex_program_supported             = false;
bool GL_ARB_vertex_shader_supported              = false;

bool GL_ATI_element_array_supported              = false;
bool GL_ATI_envmap_normalmap_supported             = false;
bool GL_ATI_fragment_shader_supported            = false;
bool GL_ATI_map_object_buffer_supported          = false;
bool GL_ATI_pn_triangles_supported               = false;
bool GL_ATI_texture_float_supported              = false;
bool GL_ATI_texture_mirror_once_supported        = false;
bool GL_ATI_vertex_array_object_supported        = false;
bool GL_ATI_vertex_attrib_array_object_supported = false;
bool GL_ATI_vertex_streams_supported             = false;

bool GL_EXT_blend_color_supported                = false;
bool GL_EXT_blend_func_separate_supported        = false;
bool GL_EXT_blend_minmax_supported               = false;
bool GL_EXT_blend_subtract_supported             = false;
bool GL_EXT_draw_range_elements_supported        = false;
bool GL_EXT_fog_coord_supported                  = false;
bool GL_EXT_packed_pixels_supported              = false;
bool GL_EXT_polygon_offset_supported             = false;
bool GL_EXT_stencil_wrap_supported               = false;
bool GL_EXT_texture3D_supported                  = false;
bool GL_EXT_texture_compression_s3tc_supported   = false;
bool GL_EXT_texture_edge_clamp_supported         = false;
bool GL_EXT_texture_filter_anisotropic_supported = false;
bool GL_EXT_texture_lod_bias_supported           = false;
bool GL_EXT_texture_rectangle_supported          = false;

bool GL_HP_occlusion_test_supported              = false;

bool GL_NV_blend_square_supported                = false;
bool GL_NV_occlusion_query_supported             = false;
bool GL_NV_register_combiners_supported          = false;
bool GL_NV_texture_env_combine4_supported        = false;

bool GL_SGIS_generate_mipmap_supported           = false;

#if defined(_WIN32)

bool WGL_ARB_extensions_string_supported         = false;
bool WGL_ARB_make_current_read_supported         = false;
bool WGL_ARB_multisample_supported               = false;
bool WGL_ARB_pbuffer_supported                   = false;
bool WGL_ARB_pixel_format_supported              = false;
bool WGL_ARB_render_texture_supported            = false;

bool WGL_ATI_pixel_format_float_supported        = false;

bool WGL_EXT_swap_control_supported              = false;

#elif defined(LINUX)

#endif

// GL_ARB_multisample
PFNGLSAMPLECOVERAGEARBPROC glSampleCoverageARB = NULL;


// GL_ARB_multitexture
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB       = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;

PFNGLMULTITEXCOORD1FARBPROC  glMultiTexCoord1fARB  = NULL;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB = NULL;

PFNGLMULTITEXCOORD2FARBPROC  glMultiTexCoord2fARB  = NULL;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB = NULL;

PFNGLMULTITEXCOORD3FARBPROC  glMultiTexCoord3fARB  = NULL;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB = NULL;

PFNGLMULTITEXCOORD4FARBPROC  glMultiTexCoord4fARB  = NULL;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB = NULL;


// GL_ARB_occlusion_query
PFNGLGENQUERIESARBPROC glGenQueriesARB = NULL;
PFNGLDELETEQUERIESARBPROC glDeleteQueriesARB = NULL;
PFNGLISQUERYARBPROC glIsQueryARB = NULL;
PFNGLBEGINQUERYARBPROC glBeginQueryARB = NULL;
PFNGLENDQUERYARBPROC glEndQueryARB = NULL;
PFNGLGETQUERYIVARBPROC glGetQueryivARB = NULL;
PFNGLGETQUERYOBJECTIVARBPROC glGetQueryObjectivARB = NULL;
PFNGLGETQUERYOBJECTUIVARBPROC glGetQueryObjectuivARB = NULL;


// GL_ARB_shader_objects
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB = NULL;
PFNGLGETHANDLEARBPROC glGetHandleARB = NULL;
PFNGLDETACHOBJECTARBPROC glDetachObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB = NULL;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB = NULL;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB = NULL;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB = NULL;

PFNGLUNIFORM1FARBPROC glUniform1fARB = NULL;
PFNGLUNIFORM2FARBPROC glUniform2fARB = NULL;
PFNGLUNIFORM3FARBPROC glUniform3fARB = NULL;
PFNGLUNIFORM4FARBPROC glUniform4fARB = NULL;

PFNGLUNIFORM1IARBPROC glUniform1iARB = NULL;
PFNGLUNIFORM2IARBPROC glUniform2iARB = NULL;
PFNGLUNIFORM3IARBPROC glUniform3iARB = NULL;
PFNGLUNIFORM4IARBPROC glUniform4iARB = NULL;

PFNGLUNIFORM1FVARBPROC glUniform1fvARB = NULL;
PFNGLUNIFORM2FVARBPROC glUniform2fvARB = NULL;
PFNGLUNIFORM3FVARBPROC glUniform3fvARB = NULL;
PFNGLUNIFORM4FVARBPROC glUniform4fvARB = NULL;

PFNGLUNIFORM1IVARBPROC glUniform1ivARB = NULL;
PFNGLUNIFORM2IVARBPROC glUniform2ivARB = NULL;
PFNGLUNIFORM3IVARBPROC glUniform3ivARB = NULL;
PFNGLUNIFORM4IVARBPROC glUniform4ivARB = NULL;

PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB = NULL;
PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB = NULL;

PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC glGetAttachedObjectsARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB = NULL;
PFNGLGETACTIVEUNIFORMARBPROC glGetActiveUniformARB = NULL;
PFNGLGETUNIFORMFVARBPROC glGetUniformfvARB = NULL;
PFNGLGETUNIFORMIVARBPROC glGetUniformivARB = NULL;
PFNGLGETSHADERSOURCEARBPROC glGetShaderSourceARB = NULL;


// GL_ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC    glCompressedTexImage1DARB    = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC    glCompressedTexImage2DARB    = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC    glCompressedTexImage3DARB    = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1DARB = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3DARB = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC   glGetCompressedTexImageARB   = NULL;


// GL_ARB_transpose_matrix
PFNGLLOADTRANSPOSEMATRIXFARBPROC glLoadTransposeMatrixfARB = NULL;
PFNGLLOADTRANSPOSEMATRIXDARBPROC glLoadTransposeMatrixdARB = NULL;
PFNGLMULTTRANSPOSEMATRIXFARBPROC glMultTransposeMatrixfARB = NULL;
PFNGLMULTTRANSPOSEMATRIXDARBPROC glMultTransposeMatrixdARB = NULL;


// GL_ARB_vertex_blend
PFNGLWEIGHTBVARBPROC  glWeightbvARB  = NULL;
PFNGLWEIGHTSVARBPROC  glWeightsvARB  = NULL;
PFNGLWEIGHTIVARBPROC  glWeightivARB  = NULL;
PFNGLWEIGHTFVARBPROC  glWeightfvARB  = NULL;
PFNGLWEIGHTDVARBPROC  glWeightdvARB  = NULL;
PFNGLWEIGHTUBVARBPROC glWeightubvARB = NULL;
PFNGLWEIGHTUSVARBPROC glWeightusvARB = NULL;
PFNGLWEIGHTUIVARBPROC glWeightuivARB = NULL;

PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB = NULL;
PFNGLVERTEXBLENDARBPROC   glVertexBlendARB   = NULL;


// GL_ARB_vertex_buffer_object
PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLISBUFFERARBPROC glIsBufferARB;

PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;

PFNGLMAPBUFFERARBPROC glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;

PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;


// GL_ARB_vertex_program
PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB = NULL;
PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB = NULL;
PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB = NULL;
PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB = NULL;
PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB = NULL;
PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB = NULL;
PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB = NULL;
PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB = NULL;
PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB = NULL;
PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB = NULL;
PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB = NULL;
PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB = NULL;
PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB = NULL;
PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB = NULL;
PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB = NULL;
PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB = NULL;
PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB = NULL;
PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB = NULL;
PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB = NULL;
PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB = NULL;
PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB = NULL;
PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB = NULL;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB = NULL;
PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB = NULL;
PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB = NULL;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB = NULL;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB = NULL;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB = NULL;
PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB = NULL;
PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB = NULL;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB = NULL;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB = NULL;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB = NULL;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB = NULL;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB = NULL;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = NULL;
PFNGLPROGRAMSTRINGARBPROC glProgramStringARB = NULL;
PFNGLBINDPROGRAMARBPROC glBindProgramARB = NULL;
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB = NULL;
PFNGLGENPROGRAMSARBPROC glGenProgramsARB = NULL;
PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB = NULL;
PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB = NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB = NULL;
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB = NULL;
PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB = NULL;
PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB = NULL;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB = NULL;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB = NULL;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointervARB = NULL;
PFNGLISPROGRAMARBPROC glIsProgramARB = NULL;

// GL_ARB_vertex_shader
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB = NULL;
PFNGLGETACTIVEATTRIBARBPROC    glGetActiveAttribARB = NULL;
PFNGLGETATTRIBLOCATIONARBPROC  glGetAttribLocationARB = NULL;




// GL_ATI_element_array
PFNGLELEMENTPOINTERATIPROC        glElementPointerATI        = NULL;
PFNGLDRAWELEMENTARRAYATIPROC      glDrawElementArrayATI      = NULL;
PFNGLDRAWRANGEELEMENTARRAYATIPROC glDrawRangeElementArrayATI = NULL;


// GL_ATI_envmap_normalmap
PFNGLTEXBUMPPARAMETERIVATIPROC    glTexBumpParameterivATI = NULL;
PFNGLTEXBUMPPARAMETERFVATIPROC    glTexBumpParameterfvATI = NULL;
PFNGLGETTEXBUMPPARAMETERIVATIPROC glGetTexBumpParameterivATI = NULL;
PFNGLGETTEXBUMPPARAMETERFVATIPROC glGetTexBumpParameterfvATI = NULL;


// GL_ATI_fragment_shader
PFNGLGENFRAGMENTSHADERSATIPROC   glGenFragmentShadersATI   = NULL;
PFNGLBINDFRAGMENTSHADERATIPROC   glBindFragmentShaderATI   = NULL;
PFNGLDELETEFRAGMENTSHADERATIPROC glDeleteFragmentShaderATI = NULL;
PFNGLBEGINFRAGMENTSHADERATIPROC  glBeginFragmentShaderATI  = NULL;
PFNGLENDFRAGMENTSHADERATIPROC    glEndFragmentShaderATI    = NULL;
PFNGLPASSTEXCOORDATIPROC         glPassTexCoordATI         = NULL;
PFNGLSAMPLEMAPATIPROC            glSampleMapATI            = NULL;

PFNGLColorFRAGMENTOP1ATIPROC glColorFragmentOp1ATI = NULL;
PFNGLColorFRAGMENTOP2ATIPROC glColorFragmentOp2ATI = NULL;
PFNGLColorFRAGMENTOP3ATIPROC glColorFragmentOp3ATI = NULL;

PFNGLALPHAFRAGMENTOP1ATIPROC glAlphaFragmentOp1ATI = NULL;
PFNGLALPHAFRAGMENTOP2ATIPROC glAlphaFragmentOp2ATI = NULL;
PFNGLALPHAFRAGMENTOP3ATIPROC glAlphaFragmentOp3ATI = NULL;

PFNGLSETFRAGMENTSHADERCONSTANTATIPROC glSetFragmentShaderConstantATI = NULL;


// GL_ATI_map_object_buffer
PFNGLMAPOBJECTBUFFERATIPROC   glMapObjectBufferATI   = NULL;
PFNGLUNMAPOBJECTBUFFERATIPROC glUnmapObjectBufferATI = NULL;

// GL_ATI_pn_triangles
PFNGLPNTRIANGLESIATIPROC glPNTrianglesiATI = NULL;
PFNGLPNTRIANGLESFATIPROC glPNTrianglesfATI = NULL;


// GL_ATI_vertex_array_object
PFNGLNEWOBJECTBUFFERATIPROC    glNewObjectBufferATI    = NULL;
PFNGLISOBJECTBUFFERATIPROC     glIsObjectBufferATI     = NULL;
PFNGLUPDATEOBJECTBUFFERATIPROC glUpdateObjectBufferATI = NULL;
PFNGLGETOBJECTBUFFERFVATIPROC  glGetObjectBufferfvATI  = NULL;
PFNGLGETOBJECTBUFFERIVATIPROC  glGetObjectBufferivATI  = NULL;
PFNGLDELETEOBJECTBUFFERATIPROC glDeleteObjectBufferATI = NULL;

PFNGLARRAYOBJECTATIPROC        glArrayObjectATI        = NULL;
PFNGLGETARRAYOBJECTFVATIPROC   glGetArrayObjectfvATI   = NULL;
PFNGLGETARRAYOBJECTIVATIPROC   glGetArrayObjectivATI   = NULL;
PFNGLVARIANTARRAYOBJECTATIPROC glVariantArrayObjectATI = NULL;

PFNGLGETVARIANTARRAYOBJECTFVATIPROC glGetVariantArrayObjectfvATI = NULL;
PFNGLGETVARIANTARRAYOBJECTIVATIPROC glGetVariantArrayObjectivATI = NULL;


// GL_ATI_vertex_attrib_array_object
PFNGLVERTEXATTRIBARRAYOBJECTATIPROC glVertexAttribArrayObjectATI = NULL;


// GL_ATI_vertex_streams
PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC glClientActiveVertexStreamATI = NULL;
PFNGLVERTEXBLENDENVIATIPROC glVertexBlendEnviATI = NULL;
PFNGLVERTEXBLENDENVFATIPROC glVertexBlendEnvfATI = NULL;

PFNGLVERTEXSTREAM2SATIPROC  glVertexStream2sATI  = NULL;
PFNGLVERTEXSTREAM2SVATIPROC glVertexStream2svATI = NULL;
PFNGLVERTEXSTREAM2IATIPROC  glVertexStream2iATI  = NULL;
PFNGLVERTEXSTREAM2IVATIPROC glVertexStream2ivATI = NULL;
PFNGLVERTEXSTREAM2FATIPROC  glVertexStream2fATI  = NULL;
PFNGLVERTEXSTREAM2FVATIPROC glVertexStream2fvATI = NULL;
PFNGLVERTEXSTREAM2DATIPROC  glVertexStream2dATI  = NULL;
PFNGLVERTEXSTREAM2DVATIPROC glVertexStream2dvATI = NULL;

PFNGLVERTEXSTREAM3SATIPROC  glVertexStream3sATI  = NULL;
PFNGLVERTEXSTREAM3SVATIPROC glVertexStream3svATI = NULL;
PFNGLVERTEXSTREAM3IATIPROC  glVertexStream3iATI  = NULL;
PFNGLVERTEXSTREAM3IVATIPROC glVertexStream3ivATI = NULL;
PFNGLVERTEXSTREAM3FATIPROC  glVertexStream3fATI  = NULL;
PFNGLVERTEXSTREAM3FVATIPROC glVertexStream3fvATI = NULL;
PFNGLVERTEXSTREAM3DATIPROC  glVertexStream3dATI  = NULL;
PFNGLVERTEXSTREAM3DVATIPROC glVertexStream3dvATI = NULL;

PFNGLVERTEXSTREAM4SATIPROC  glVertexStream4sATI  = NULL;
PFNGLVERTEXSTREAM4SVATIPROC glVertexStream4svATI = NULL;
PFNGLVERTEXSTREAM4IATIPROC  glVertexStream4iATI  = NULL;
PFNGLVERTEXSTREAM4IVATIPROC glVertexStream4ivATI = NULL;
PFNGLVERTEXSTREAM4FATIPROC  glVertexStream4fATI  = NULL;
PFNGLVERTEXSTREAM4FVATIPROC glVertexStream4fvATI = NULL;
PFNGLVERTEXSTREAM4DATIPROC  glVertexStream4dATI  = NULL;
PFNGLVERTEXSTREAM4DVATIPROC glVertexStream4dvATI = NULL;

PFNGLNORMALSTREAM3BATIPROC  glNormalStream3bATI  = NULL;
PFNGLNORMALSTREAM3BVATIPROC glNormalStream3bvATI = NULL;
PFNGLNORMALSTREAM3SATIPROC  glNormalStream3sATI  = NULL;
PFNGLNORMALSTREAM3SVATIPROC glNormalStream3svATI = NULL;
PFNGLNORMALSTREAM3IATIPROC  glNormalStream3iATI  = NULL;
PFNGLNORMALSTREAM3IVATIPROC glNormalStream3ivATI = NULL;
PFNGLNORMALSTREAM3FATIPROC  glNormalStream3fATI  = NULL;
PFNGLNORMALSTREAM3FVATIPROC glNormalStream3fvATI = NULL;
PFNGLNORMALSTREAM3DATIPROC  glNormalStream3dATI  = NULL;
PFNGLNORMALSTREAM3DVATIPROC glNormalStream3dvATI = NULL;



// GL_EXT_blend_color
PFNGLBLENDColorEXTPROC glBlendColorEXT = NULL;

// GL_EXT_blend_func_separate
PFNGLBLENDFUNCSEPARATEEXTPROC glBlendFuncSeparateEXT = NULL;


// GL_EXT_blend_minmax
PFNGLBLENDEQUATIONEXTPROC glBlendEquationEXT = NULL;


// GL_EXT_draw_range_elements
PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElementsEXT = NULL;


// GL_EXT_fog_coord
PFNGLFOGCOORDFEXTPROC  glFogCoordfEXT  = NULL;
PFNGLFOGCOORDDEXTPROC  glFogCoorddEXT  = NULL;
PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT = NULL;
PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT = NULL;
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT = NULL;


// GL_EXT_polygon_offset
PFNGLPOLYGONOFFSETEXTPROC glPolygonOffsetEXT = NULL;


// GL_EXT_texture3D
PFNGLTEXIMAGE3DEXTPROC glTexImage3DEXT = NULL;







// GL_NV_occlusion_query
PFNGLGENOCCLUSIONQUERIESNVPROC    glGenOcclusionQueriesNV    = NULL;
PFNGLDELETEOCCLUSIONQUERIESNVPROC glDeleteOcclusionQueriesNV = NULL;
PFNGLISOCCLUSIONQUERYNVPROC       glIsOcclusionQueryNV       = NULL;
PFNGLBEGINOCCLUSIONQUERYNVPROC    glBeginOcclusionQueryNV    = NULL;
PFNGLENDOCCLUSIONQUERYNVPROC      glEndOcclusionQueryNV      = NULL;
PFNGLGETOCCLUSIONQUERYIVNVPROC    glGetOcclusionQueryivNV    = NULL;
PFNGLGETOCCLUSIONQUERYUIVNVPROC   glGetOcclusionQueryuivNV   = NULL;


// GL_NV_register_combiners
PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV = NULL;
PFNGLCOMBINERPARAMETERFNVPROC  glCombinerParameterfNV  = NULL;
PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV = NULL;
PFNGLCOMBINERPARAMETERINVPROC  glCombinerParameteriNV  = NULL;

PFNGLCOMBINERINPUTNVPROC       glCombinerInputNV       = NULL;
PFNGLCOMBINEROUTPUTNVPROC      glCombinerOutputNV      = NULL;
PFNGLFINALCOMBINERINPUTNVPROC  glFinalCombinerInputNV  = NULL;

PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC  glGetCombinerInputParameterfvNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC  glGetCombinerInputParameterivNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV = NULL;

PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV = NULL;


#ifdef WIN32
// WGL_ARB_extensions_string
WGL_ARB_EXTENSIONS_STRING wglGetExtensionsStringARB = NULL;


// WGL_ARB_make_current_read
PFNWGLMAKECONTEXTCURRENTARBPROC wglMakeContextCurrentARB = NULL;
PFNWGLGETCURRENTREADDCARBPROC wglGetCurrentReadDCARB = NULL;


// WGL_ARB_pbuffer
PFNWGLCREATEPBUFFERARBPROC    wglCreatePbufferARB    = NULL;
PFNWGLGETPBUFFERDCARBPROC     wglGetPbufferDCARB     = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC wglReleasePbufferDCARB = NULL;
PFNWGLDESTROYPBUFFERARBPROC   wglDestroyPbufferARB   = NULL;
PFNWGLQUERYPBUFFERARBPROC     wglQueryPbufferARB     = NULL;


// WGL_ARB_pixel_format
PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = NULL;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC      wglChoosePixelFormatARB      = NULL;


// WGL_ARB_render_texture
PFNWGLBINDTEXIMAGEARBPROC     wglBindTexImageARB     = NULL;
PFNWGLRELEASETEXIMAGEARBPROC  wglReleaseTexImageARB  = NULL;
PFNWGLSETPBUFFERATTRIBARBPROC wglSetPbufferAttribARB = NULL;


// WGL_EXT_swap_control
PFNWGLEXTSWAPINTERVALPROC wglSwapIntervalEXT = NULL;

#endif // WIN32




/* ------------------------------------------------------------------ */

bool findExtension(char *extensions, char *extension){
	if (extensions){
		char *str = extensions;
		int len = strlen(extension);
		
		while ((str = strstr(str, extension)) != NULL){
			str += len;
			if (*str == ' ' || *str == '\0') return true;
		}
	}
	return false;
}

void initExtensions() {

	char *extensions = (char *) glGetString(GL_EXTENSIONS);

	GL_ARB_depth_texture_supported    = isExtensionSupported("GL_ARB_depth_texture");
	GL_ARB_fragment_program_supported = isExtensionSupported("GL_ARB_fragment_program");
	GL_ARB_fragment_shader_supported  = isExtensionSupported("GL_ARB_fragment_shader");

	if (GL_ARB_multisample_supported = isExtensionSupported("GL_ARB_multisample")){
		glSampleCoverageARB = (PFNGLSAMPLECOVERAGEARBPROC) wglxGetProcAddress("glSampleCoverageARB");
	}

	if (GL_ARB_multitexture_supported = isExtensionSupported("GL_ARB_multitexture")){
		glActiveTextureARB       = (PFNGLACTIVETEXTUREARBPROC)       wglxGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglxGetProcAddress("glClientActiveTextureARB");

		glMultiTexCoord1fARB  = (PFNGLMULTITEXCOORD1FARBPROC)  wglxGetProcAddress("glMultiTexCoord1fARB");
		glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC) wglxGetProcAddress("glMultiTexCoord1fvARB");
		glMultiTexCoord2fARB  = (PFNGLMULTITEXCOORD2FARBPROC)  wglxGetProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) wglxGetProcAddress("glMultiTexCoord2fvARB");
		glMultiTexCoord3fARB  = (PFNGLMULTITEXCOORD3FARBPROC)  wglxGetProcAddress("glMultiTexCoord3fARB");
		glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC) wglxGetProcAddress("glMultiTexCoord3fvARB");
		glMultiTexCoord4fARB  = (PFNGLMULTITEXCOORD4FARBPROC)  wglxGetProcAddress("glMultiTexCoord4fARB");
		glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC) wglxGetProcAddress("glMultiTexCoord4fvARB");
	}

	if (GL_ARB_occlusion_query_supported = isExtensionSupported("GL_ARB_occlusion_query")){
		glGenQueriesARB    = (PFNGLGENQUERIESARBPROC)    wglxGetProcAddress("glGenQueriesARB");
		glDeleteQueriesARB = (PFNGLDELETEQUERIESARBPROC) wglxGetProcAddress("glDeleteQueriesARB");
		glIsQueryARB    = (PFNGLISQUERYARBPROC)    wglxGetProcAddress("glIsQueryARB");
		glBeginQueryARB = (PFNGLBEGINQUERYARBPROC) wglxGetProcAddress("glBeginQueryARB");
		glEndQueryARB   = (PFNGLENDQUERYARBPROC)   wglxGetProcAddress("glEndQueryARB");
		glGetQueryivARB = (PFNGLGETQUERYIVARBPROC) wglxGetProcAddress("glGetQueryivARB");
		glGetQueryObjectivARB  = (PFNGLGETQUERYOBJECTIVARBPROC)  wglxGetProcAddress("glGetQueryObjectivARB");
		glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) wglxGetProcAddress("glGetQueryObjectuivARB");
	}

	if (GL_ARB_shader_objects_supported = isExtensionSupported("GL_ARB_shader_objects")){
		glDeleteObjectARB        = (PFNGLDELETEOBJECTARBPROC)        wglxGetProcAddress("glDeleteObjectARB");
		glGetHandleARB           = (PFNGLGETHANDLEARBPROC)           wglxGetProcAddress("glGetHandleARB");
		glDetachObjectARB        = (PFNGLDETACHOBJECTARBPROC)        wglxGetProcAddress("glDetachObjectARB");
		glCreateShaderObjectARB  = (PFNGLCREATESHADEROBJECTARBPROC)  wglxGetProcAddress("glCreateShaderObjectARB");
		glShaderSourceARB        = (PFNGLSHADERSOURCEARBPROC)        wglxGetProcAddress("glShaderSourceARB");
		glCompileShaderARB       = (PFNGLCOMPILESHADERARBPROC)       wglxGetProcAddress("glCompileShaderARB");
		glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) wglxGetProcAddress("glCreateProgramObjectARB");
		glAttachObjectARB        = (PFNGLATTACHOBJECTARBPROC)        wglxGetProcAddress("glAttachObjectARB");
		glLinkProgramARB         = (PFNGLLINKPROGRAMARBPROC)         wglxGetProcAddress("glLinkProgramARB");
		glUseProgramObjectARB    = (PFNGLUSEPROGRAMOBJECTARBPROC)    wglxGetProcAddress("glUseProgramObjectARB");
		glValidateProgramARB     = (PFNGLVALIDATEPROGRAMARBPROC)     wglxGetProcAddress("glValidateProgramARB");

		glUniform1fARB = (PFNGLUNIFORM1FARBPROC) wglxGetProcAddress("glUniform1fARB");
		glUniform2fARB = (PFNGLUNIFORM2FARBPROC) wglxGetProcAddress("glUniform2fARB");
		glUniform3fARB = (PFNGLUNIFORM3FARBPROC) wglxGetProcAddress("glUniform3fARB");
		glUniform4fARB = (PFNGLUNIFORM4FARBPROC) wglxGetProcAddress("glUniform4fARB");

		glUniform1iARB = (PFNGLUNIFORM1IARBPROC) wglxGetProcAddress("glUniform1iARB");
		glUniform2iARB = (PFNGLUNIFORM2IARBPROC) wglxGetProcAddress("glUniform2iARB");
		glUniform3iARB = (PFNGLUNIFORM3IARBPROC) wglxGetProcAddress("glUniform3iARB");
		glUniform4iARB = (PFNGLUNIFORM4IARBPROC) wglxGetProcAddress("glUniform4iARB");

		glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC) wglxGetProcAddress("glUniform1fvARB");
		glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC) wglxGetProcAddress("glUniform2fvARB");
		glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC) wglxGetProcAddress("glUniform3fvARB");
		glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC) wglxGetProcAddress("glUniform4fvARB");

		glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC) wglxGetProcAddress("glUniform1ivARB");
		glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC) wglxGetProcAddress("glUniform2ivARB");
		glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC) wglxGetProcAddress("glUniform3ivARB");
		glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC) wglxGetProcAddress("glUniform4ivARB");

		glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC) wglxGetProcAddress("glUniformMatrix2fvARB");
		glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC) wglxGetProcAddress("glUniformMatrix3fvARB");
		glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) wglxGetProcAddress("glUniformMatrix4fvARB");

		glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) wglxGetProcAddress("glGetObjectParameterfvARB");
		glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) wglxGetProcAddress("glGetObjectParameterivARB");
		glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)           wglxGetProcAddress("glGetInfoLogARB");
		glGetAttachedObjectsARB   = (PFNGLGETATTACHEDOBJECTSARBPROC)   wglxGetProcAddress("glGetAttachedObjectsARB");
		glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)   wglxGetProcAddress("glGetUniformLocationARB");
		glGetActiveUniformARB     = (PFNGLGETACTIVEUNIFORMARBPROC)     wglxGetProcAddress("glGetActiveUniformARB");
		glGetUniformfvARB         = (PFNGLGETUNIFORMFVARBPROC)         wglxGetProcAddress("glGetUniformfvARB");
		glGetUniformivARB         = (PFNGLGETUNIFORMIVARBPROC)         wglxGetProcAddress("glGetUniformivARB");
		glGetShaderSourceARB      = (PFNGLGETSHADERSOURCEARBPROC)      wglxGetProcAddress("glGetShaderSourceARB");
	}

	GL_ARB_shading_language_100_supported = isExtensionSupported("GL_ARB_shading_language_100");

	GL_ARB_shadow_supported         = isExtensionSupported("GL_ARB_shadow");
	GL_ARB_shadow_ambient_supported = isExtensionSupported("GL_ARB_shadow_ambient");

	if (GL_ARB_texture_compression_supported = isExtensionSupported("GL_ARB_texture_compression")){
		glCompressedTexImage1DARB     = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)    wglxGetProcAddress("glCompressedTexImage1DARB");
		glCompressedTexImage2DARB     = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)    wglxGetProcAddress("glCompressedTexImage2DARB");
		glCompressedTexImage3DARB     = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)    wglxGetProcAddress("glCompressedTexImage3DARB");
		glCompressedTexSubImage1DARB  = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) wglxGetProcAddress("glCompressedTexSubImage1DARB");
		glCompressedTexSubImage2DARB  = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) wglxGetProcAddress("glCompressedTexSubImage2DARB");
		glCompressedTexSubImage3DARB  = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) wglxGetProcAddress("glCompressedTexSubImage3DARB");
		glGetCompressedTexImageARB    = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)   wglxGetProcAddress("glGetCompressedTexImageARB");

		// Workaround for a driver bug in current ATi Linux drivers
		//if (glCompressedTexImage2DARB == NULL) GL_ARB_texture_compression_supported = false;
	}

	GL_ARB_texture_cube_map_supported     = isExtensionSupported("GL_ARB_texture_cube_map");
    GL_ARB_texture_env_add_supported      = isExtensionSupported("GL_ARB_texture_env_add");
	GL_ARB_texture_env_combine_supported  = isExtensionSupported("GL_ARB_texture_env_combine");
	GL_ARB_texture_env_crossbar_supported = isExtensionSupported("GL_ARB_texture_env_crossbar");
	GL_ARB_texture_env_dot3_supported     = isExtensionSupported("GL_ARB_texture_env_dot3");

	if (GL_ARB_transpose_matrix_supported = isExtensionSupported("GL_ARB_transpose_matrix")){
		glLoadTransposeMatrixfARB = (PFNGLLOADTRANSPOSEMATRIXFARBPROC) wglxGetProcAddress("glLoadTransposeMatrixfARB");
		glLoadTransposeMatrixdARB = (PFNGLLOADTRANSPOSEMATRIXDARBPROC) wglxGetProcAddress("glLoadTransposeMatrixdARB");
		glMultTransposeMatrixfARB = (PFNGLMULTTRANSPOSEMATRIXFARBPROC) wglxGetProcAddress("glMultTransposeMatrixfARB");
		glMultTransposeMatrixdARB = (PFNGLMULTTRANSPOSEMATRIXDARBPROC) wglxGetProcAddress("glMultTransposeMatrixdARB");
	}

	if (GL_ARB_vertex_blend_supported = isExtensionSupported("GL_ARB_vertex_blend")){
		glWeightbvARB  = (PFNGLWEIGHTBVARBPROC)  wglxGetProcAddress("glWeightbvARB");
		glWeightsvARB  = (PFNGLWEIGHTSVARBPROC)  wglxGetProcAddress("glWeightsvARB");
		glWeightivARB  = (PFNGLWEIGHTIVARBPROC)  wglxGetProcAddress("glWeightivARB");
		glWeightfvARB  = (PFNGLWEIGHTFVARBPROC)  wglxGetProcAddress("glWeightfvARB");
		glWeightdvARB  = (PFNGLWEIGHTDVARBPROC)  wglxGetProcAddress("glWeightdvARB");
		glWeightubvARB = (PFNGLWEIGHTUBVARBPROC) wglxGetProcAddress("glWeightubvARB");
		glWeightusvARB = (PFNGLWEIGHTUSVARBPROC) wglxGetProcAddress("glWeightusvARB");
		glWeightuivARB = (PFNGLWEIGHTUIVARBPROC) wglxGetProcAddress("glWeightuivARB");
		
		glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC) wglxGetProcAddress("glWeightPointerARB");
		glVertexBlendARB   = (PFNGLVERTEXBLENDARBPROC)   wglxGetProcAddress("glVertexBlendARB");
	}

	if (GL_ARB_vertex_buffer_object_supported = isExtensionSupported("GL_ARB_vertex_buffer_object")){
		glBindBufferARB    = (PFNGLBINDBUFFERARBPROC)    wglxGetProcAddress("glBindBufferARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglxGetProcAddress("glDeleteBuffersARB");
		glGenBuffersARB    = (PFNGLGENBUFFERSARBPROC)    wglxGetProcAddress("glGenBuffersARB");
		glIsBufferARB      = (PFNGLISBUFFERARBPROC)      wglxGetProcAddress("glIsBufferARB");

		glBufferDataARB       = (PFNGLBUFFERDATAARBPROC)       wglxGetProcAddress("glBufferDataARB");
		glBufferSubDataARB    = (PFNGLBUFFERSUBDATAARBPROC)    wglxGetProcAddress("glBufferSubDataARB");
		glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC) wglxGetProcAddress("glGetBufferSubDataARB");

		glMapBufferARB   = (PFNGLMAPBUFFERARBPROC)   wglxGetProcAddress("glMapBufferARB");
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) wglxGetProcAddress("glUnmapBufferARB");

		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) wglxGetProcAddress("glGetBufferParameterivARB");
		glGetBufferPointervARB    = (PFNGLGETBUFFERPOINTERVARBPROC)    wglxGetProcAddress("glGetBufferPointervARB");
	}

	GL_ARB_vertex_program_supported = isExtensionSupported("GL_ARB_vertex_program");

	if (GL_ARB_vertex_program_supported || GL_ARB_fragment_program_supported){
		glProgramStringARB  = (PFNGLPROGRAMSTRINGARBPROC)  wglxGetProcAddress("glProgramStringARB");
		glBindProgramARB    = (PFNGLBINDPROGRAMARBPROC)    wglxGetProcAddress("glBindProgramARB");
		glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC) wglxGetProcAddress("glDeleteProgramsARB");
		glGenProgramsARB    = (PFNGLGENPROGRAMSARBPROC)    wglxGetProcAddress("glGenProgramsARB");
		glProgramEnvParameter4dARB    = (PFNGLPROGRAMENVPARAMETER4DARBPROC)    wglxGetProcAddress("glProgramEnvParameter4dARB");
		glProgramEnvParameter4dvARB   = (PFNGLPROGRAMENVPARAMETER4DVARBPROC)   wglxGetProcAddress("glProgramEnvParameter4dvARB");
		glProgramEnvParameter4fARB    = (PFNGLPROGRAMENVPARAMETER4FARBPROC)    wglxGetProcAddress("glProgramEnvParameter4fARB");
		glProgramEnvParameter4fvARB   = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)   wglxGetProcAddress("glProgramEnvParameter4fvARB");
		glProgramLocalParameter4dARB  = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)  wglxGetProcAddress("glProgramLocalParameter4dARB");
		glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC) wglxGetProcAddress("glProgramLocalParameter4dvARB");
		glProgramLocalParameter4fARB  = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)  wglxGetProcAddress("glProgramLocalParameter4fARB");
		glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC) wglxGetProcAddress("glProgramLocalParameter4fvARB");
		glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC) wglxGetProcAddress("glGetProgramEnvParameterdvARB");
		glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC) wglxGetProcAddress("glGetProgramEnvParameterfvARB");
		glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC) wglxGetProcAddress("glGetProgramLocalParameterdvARB");
		glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC) wglxGetProcAddress("glGetProgramLocalParameterfvARB");
		glGetProgramivARB     = (PFNGLGETPROGRAMIVARBPROC)     wglxGetProcAddress("glGetProgramivARB");
		glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC) wglxGetProcAddress("glGetProgramStringARB");
		glIsProgramARB        = (PFNGLISPROGRAMARBPROC)        wglxGetProcAddress("glIsProgramARB");
	}

	if (GL_ARB_vertex_shader_supported = isExtensionSupported("GL_ARB_vertex_shader")){
		glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) wglxGetProcAddress("glBindAttribLocationARB");
		glGetActiveAttribARB    = (PFNGLGETACTIVEATTRIBARBPROC)    wglxGetProcAddress("glGetActiveAttribARB");
		glGetAttribLocationARB  = (PFNGLGETATTRIBLOCATIONARBPROC)  wglxGetProcAddress("glGetAttribLocationARB");
	}

	if (GL_ARB_vertex_program_supported || GL_ARB_vertex_shader_supported){
		glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC) wglxGetProcAddress("glVertexAttrib1sARB");
		glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC) wglxGetProcAddress("glVertexAttrib1fARB");
		glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC) wglxGetProcAddress("glVertexAttrib1dARB");
		glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC) wglxGetProcAddress("glVertexAttrib2sARB");
		glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC) wglxGetProcAddress("glVertexAttrib2fARB");
		glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC) wglxGetProcAddress("glVertexAttrib2dARB");
		glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC) wglxGetProcAddress("glVertexAttrib3sARB");
		glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC) wglxGetProcAddress("glVertexAttrib3fARB");
		glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC) wglxGetProcAddress("glVertexAttrib3dARB");
		glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC) wglxGetProcAddress("glVertexAttrib4sARB");
		glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC) wglxGetProcAddress("glVertexAttrib4fARB");
		glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC) wglxGetProcAddress("glVertexAttrib4dARB");
		glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC) wglxGetProcAddress("glVertexAttrib4NubARB");
		glVertexAttrib1svARB  = (PFNGLVERTEXATTRIB1SVARBPROC)  wglxGetProcAddress("glVertexAttrib1svARB");
		glVertexAttrib1fvARB  = (PFNGLVERTEXATTRIB1FVARBPROC)  wglxGetProcAddress("glVertexAttrib1fvARB");
		glVertexAttrib1dvARB  = (PFNGLVERTEXATTRIB1DVARBPROC)  wglxGetProcAddress("glVertexAttrib1dvARB");
		glVertexAttrib2svARB  = (PFNGLVERTEXATTRIB2SVARBPROC)  wglxGetProcAddress("glVertexAttrib2svARB");
		glVertexAttrib2fvARB  = (PFNGLVERTEXATTRIB2FVARBPROC)  wglxGetProcAddress("glVertexAttrib2fvARB");
		glVertexAttrib2dvARB  = (PFNGLVERTEXATTRIB2DVARBPROC)  wglxGetProcAddress("glVertexAttrib2dvARB");
		glVertexAttrib3svARB  = (PFNGLVERTEXATTRIB3SVARBPROC)  wglxGetProcAddress("glVertexAttrib3svARB");
		glVertexAttrib3fvARB  = (PFNGLVERTEXATTRIB3FVARBPROC)  wglxGetProcAddress("glVertexAttrib3fvARB");
		glVertexAttrib3dvARB  = (PFNGLVERTEXATTRIB3DVARBPROC)  wglxGetProcAddress("glVertexAttrib3dvARB");
		glVertexAttrib4bvARB  = (PFNGLVERTEXATTRIB4BVARBPROC)  wglxGetProcAddress("glVertexAttrib4bvARB");
		glVertexAttrib4svARB  = (PFNGLVERTEXATTRIB4SVARBPROC)  wglxGetProcAddress("glVertexAttrib4svARB");
		glVertexAttrib4ivARB  = (PFNGLVERTEXATTRIB4IVARBPROC)  wglxGetProcAddress("glVertexAttrib4ivARB");
		glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC) wglxGetProcAddress("glVertexAttrib4ubvARB");
		glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC) wglxGetProcAddress("glVertexAttrib4usvARB");
		glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC) wglxGetProcAddress("glVertexAttrib4uivARB");
		glVertexAttrib4fvARB  = (PFNGLVERTEXATTRIB4FVARBPROC)  wglxGetProcAddress("glVertexAttrib4fvARB");
		glVertexAttrib4dvARB  = (PFNGLVERTEXATTRIB4DVARBPROC)  wglxGetProcAddress("glVertexAttrib4dvARB");
		glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC) wglxGetProcAddress("glVertexAttrib4NbvARB");
		glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC) wglxGetProcAddress("glVertexAttrib4NsvARB");
		glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC) wglxGetProcAddress("glVertexAttrib4NivARB");
		glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC) wglxGetProcAddress("glVertexAttrib4NubvARB");
		glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC) wglxGetProcAddress("glVertexAttrib4NusvARB");
		glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC) wglxGetProcAddress("glVertexAttrib4NuivARB");

		glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) wglxGetProcAddress("glVertexAttribPointerARB");
		glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) wglxGetProcAddress("glEnableVertexAttribArrayARB");
		glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) wglxGetProcAddress("glDisableVertexAttribArrayARB");

		glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC) wglxGetProcAddress("glGetVertexAttribdvARB");
		glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC) wglxGetProcAddress("glGetVertexAttribfvARB");
		glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC) wglxGetProcAddress("glGetVertexAttribivARB");
		glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC) wglxGetProcAddress("glGetVertexAttribPointervARB");
	}




	if (GL_ATI_element_array_supported = isExtensionSupported("GL_ATI_element_array")){
		glElementPointerATI        = (PFNGLELEMENTPOINTERATIPROC)        wglxGetProcAddress("glElementPointerATI");
		glDrawElementArrayATI      = (PFNGLDRAWELEMENTARRAYATIPROC)      wglxGetProcAddress("glDrawElementArrayATI");
		glDrawRangeElementArrayATI = (PFNGLDRAWRANGEELEMENTARRAYATIPROC) wglxGetProcAddress("glDrawRangeElementArrayATI");
	}

	if (GL_ATI_envmap_normalmap_supported = isExtensionSupported("GL_ATI_envmap_normalmap")){
		glTexBumpParameterivATI = (PFNGLTEXBUMPPARAMETERIVATIPROC) wglxGetProcAddress("glTexBumpParameterivATI");
		glTexBumpParameterfvATI = (PFNGLTEXBUMPPARAMETERFVATIPROC) wglxGetProcAddress("glTexBumpParameterfvATI");
		glGetTexBumpParameterivATI = (PFNGLGETTEXBUMPPARAMETERIVATIPROC) wglxGetProcAddress("glGetTexBumpParameterivATI");
		glGetTexBumpParameterfvATI = (PFNGLGETTEXBUMPPARAMETERFVATIPROC) wglxGetProcAddress("glGetTexBumpParameterfvATI");
	}

	if (GL_ATI_fragment_shader_supported = isExtensionSupported("GL_ATI_fragment_shader")){
		glGenFragmentShadersATI   = (PFNGLGENFRAGMENTSHADERSATIPROC)   wglxGetProcAddress("glGenFragmentShadersATI");
		glBindFragmentShaderATI   = (PFNGLBINDFRAGMENTSHADERATIPROC)   wglxGetProcAddress("glBindFragmentShaderATI");
		glDeleteFragmentShaderATI = (PFNGLDELETEFRAGMENTSHADERATIPROC) wglxGetProcAddress("glDeleteFragmentShaderATI");
		glBeginFragmentShaderATI  = (PFNGLBEGINFRAGMENTSHADERATIPROC)  wglxGetProcAddress("glBeginFragmentShaderATI");
		glEndFragmentShaderATI    = (PFNGLENDFRAGMENTSHADERATIPROC)    wglxGetProcAddress("glEndFragmentShaderATI");
		glPassTexCoordATI         = (PFNGLPASSTEXCOORDATIPROC)         wglxGetProcAddress("glPassTexCoordATI");
		glSampleMapATI            = (PFNGLSAMPLEMAPATIPROC)            wglxGetProcAddress("glSampleMapATI");
		
		glColorFragmentOp1ATI = (PFNGLColorFRAGMENTOP1ATIPROC) wglxGetProcAddress("glColorFragmentOp1ATI");
		glColorFragmentOp2ATI = (PFNGLColorFRAGMENTOP2ATIPROC) wglxGetProcAddress("glColorFragmentOp2ATI");
		glColorFragmentOp3ATI = (PFNGLColorFRAGMENTOP3ATIPROC) wglxGetProcAddress("glColorFragmentOp3ATI");
		
		glAlphaFragmentOp1ATI = (PFNGLALPHAFRAGMENTOP1ATIPROC) wglxGetProcAddress("glAlphaFragmentOp1ATI");
		glAlphaFragmentOp2ATI = (PFNGLALPHAFRAGMENTOP2ATIPROC) wglxGetProcAddress("glAlphaFragmentOp2ATI");
		glAlphaFragmentOp3ATI = (PFNGLALPHAFRAGMENTOP3ATIPROC) wglxGetProcAddress("glAlphaFragmentOp3ATI");
		
		glSetFragmentShaderConstantATI = (PFNGLSETFRAGMENTSHADERCONSTANTATIPROC) wglxGetProcAddress("glSetFragmentShaderConstantATI");
	}

	if (GL_ATI_map_object_buffer_supported = isExtensionSupported("GL_ATI_map_object_buffer")){
		glMapObjectBufferATI   = (PFNGLMAPOBJECTBUFFERATIPROC)   wglxGetProcAddress("glMapObjectBufferATI");
		glUnmapObjectBufferATI = (PFNGLUNMAPOBJECTBUFFERATIPROC) wglxGetProcAddress("glUnmapObjectBufferATI");
	}



	if (GL_ATI_pn_triangles_supported = isExtensionSupported("GL_ATI_pn_triangles")){
		glPNTrianglesiATI = (PFNGLPNTRIANGLESIATIPROC) wglxGetProcAddress("glPNTrianglesiATI");
		glPNTrianglesfATI = (PFNGLPNTRIANGLESFATIPROC) wglxGetProcAddress("glPNTrianglesfATI");
	}

	GL_ATI_texture_float_supported       = isExtensionSupported("GL_ATI_texture_float");
	GL_ATI_texture_mirror_once_supported = isExtensionSupported("GL_ATI_texture_mirror_once");

	if (GL_ATI_vertex_array_object_supported = isExtensionSupported("GL_ATI_vertex_array_object")){
		glNewObjectBufferATI    = (PFNGLNEWOBJECTBUFFERATIPROC)    wglxGetProcAddress("glNewObjectBufferATI");
		glIsObjectBufferATI     = (PFNGLISOBJECTBUFFERATIPROC)     wglxGetProcAddress("glIsObjectBufferATI");
		glUpdateObjectBufferATI = (PFNGLUPDATEOBJECTBUFFERATIPROC) wglxGetProcAddress("glUpdateObjectBufferATI");
		glGetObjectBufferfvATI  = (PFNGLGETOBJECTBUFFERFVATIPROC)  wglxGetProcAddress("glGetObjectBufferfvATI");
		glGetObjectBufferivATI  = (PFNGLGETOBJECTBUFFERIVATIPROC)  wglxGetProcAddress("glGetObjectBufferivATI");
		glDeleteObjectBufferATI = (PFNGLDELETEOBJECTBUFFERATIPROC) wglxGetProcAddress("glDeleteObjectBufferATI");
		
		glArrayObjectATI        = (PFNGLARRAYOBJECTATIPROC)        wglxGetProcAddress("glArrayObjectATI");
		glGetArrayObjectfvATI   = (PFNGLGETARRAYOBJECTFVATIPROC)   wglxGetProcAddress("glGetArrayObjectfvATI");
		glGetArrayObjectivATI   = (PFNGLGETARRAYOBJECTIVATIPROC)   wglxGetProcAddress("glGetArrayObjectivATI");
		glVariantArrayObjectATI = (PFNGLVARIANTARRAYOBJECTATIPROC) wglxGetProcAddress("glVariantArrayObjectATI");
		
		glGetVariantArrayObjectfvATI = (PFNGLGETVARIANTARRAYOBJECTFVATIPROC) wglxGetProcAddress("glGetVariantArrayObjectfvATI");
		glGetVariantArrayObjectivATI = (PFNGLGETVARIANTARRAYOBJECTIVATIPROC) wglxGetProcAddress("glGetVariantArrayObjectivATI");
	}

	if (GL_ATI_vertex_attrib_array_object_supported = isExtensionSupported("GL_ATI_vertex_attrib_array_object")){
		/* TODO: Fix this */
		glVertexAttribArrayObjectATI = (PFNGLVERTEXATTRIBARRAYOBJECTATIPROC) wglxGetProcAddress("glVertexAttribArrayObjectATI");
		//glGetVertexAttribArrayObjectivATI
		//glGetVertexAttribArrayObjectfvATI
		//glVertexAttribArrayObjectATI
	}

	if (GL_ATI_vertex_streams_supported = isExtensionSupported("GL_ATI_vertex_streams")){
		glClientActiveVertexStreamATI = (PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC) wglxGetProcAddress("glClientActiveVertexStreamATI");
		glVertexBlendEnviATI = (PFNGLVERTEXBLENDENVIATIPROC) wglxGetProcAddress("glVertexBlendEnviATI");
		glVertexBlendEnvfATI = (PFNGLVERTEXBLENDENVFATIPROC) wglxGetProcAddress("glVertexBlendEnvfATI");
		
		glVertexStream2sATI  = (PFNGLVERTEXSTREAM2SATIPROC)  wglxGetProcAddress("glVertexStream2sATI");
		glVertexStream2svATI = (PFNGLVERTEXSTREAM2SVATIPROC) wglxGetProcAddress("glVertexStream2svATI");
		glVertexStream2iATI  = (PFNGLVERTEXSTREAM2IATIPROC)  wglxGetProcAddress("glVertexStream2iATI");
		glVertexStream2ivATI = (PFNGLVERTEXSTREAM2IVATIPROC) wglxGetProcAddress("glVertexStream2ivATI");
		glVertexStream2fATI  = (PFNGLVERTEXSTREAM2FATIPROC)  wglxGetProcAddress("glVertexStream2fATI");
		glVertexStream2fvATI = (PFNGLVERTEXSTREAM2FVATIPROC) wglxGetProcAddress("glVertexStream2fvATI");
		glVertexStream2dATI  = (PFNGLVERTEXSTREAM2DATIPROC)  wglxGetProcAddress("glVertexStream2dATI");
		glVertexStream2dvATI = (PFNGLVERTEXSTREAM2DVATIPROC) wglxGetProcAddress("glVertexStream2dvATI");
		
		glVertexStream3sATI  = (PFNGLVERTEXSTREAM3SATIPROC)  wglxGetProcAddress("glVertexStream3sATI");
		glVertexStream3svATI = (PFNGLVERTEXSTREAM3SVATIPROC) wglxGetProcAddress("glVertexStream3svATI");
		glVertexStream3iATI  = (PFNGLVERTEXSTREAM3IATIPROC)  wglxGetProcAddress("glVertexStream3iATI");
		glVertexStream3ivATI = (PFNGLVERTEXSTREAM3IVATIPROC) wglxGetProcAddress("glVertexStream3ivATI");
		glVertexStream3fATI  = (PFNGLVERTEXSTREAM3FATIPROC)  wglxGetProcAddress("glVertexStream3fATI");
		glVertexStream3fvATI = (PFNGLVERTEXSTREAM3FVATIPROC) wglxGetProcAddress("glVertexStream3fvATI");
		glVertexStream3dATI  = (PFNGLVERTEXSTREAM3DATIPROC)  wglxGetProcAddress("glVertexStream3dATI");
		glVertexStream3dvATI = (PFNGLVERTEXSTREAM3DVATIPROC) wglxGetProcAddress("glVertexStream3dvATI");
		
		glVertexStream4sATI  = (PFNGLVERTEXSTREAM4SATIPROC)  wglxGetProcAddress("glVertexStream4sATI");
		glVertexStream4svATI = (PFNGLVERTEXSTREAM4SVATIPROC) wglxGetProcAddress("glVertexStream4svATI");
		glVertexStream4iATI  = (PFNGLVERTEXSTREAM4IATIPROC)  wglxGetProcAddress("glVertexStream4iATI");
		glVertexStream4ivATI = (PFNGLVERTEXSTREAM4IVATIPROC) wglxGetProcAddress("glVertexStream4ivATI");
		glVertexStream4fATI  = (PFNGLVERTEXSTREAM4FATIPROC)  wglxGetProcAddress("glVertexStream4fATI");
		glVertexStream4fvATI = (PFNGLVERTEXSTREAM4FVATIPROC) wglxGetProcAddress("glVertexStream4fvATI");
		glVertexStream4dATI  = (PFNGLVERTEXSTREAM4DATIPROC)  wglxGetProcAddress("glVertexStream4dATI");
		glVertexStream4dvATI = (PFNGLVERTEXSTREAM4DVATIPROC) wglxGetProcAddress("glVertexStream4dvATI");
		
		glNormalStream3bATI  = (PFNGLNORMALSTREAM3BATIPROC)  wglxGetProcAddress("glNormalStream3bATI");
		glNormalStream3bvATI = (PFNGLNORMALSTREAM3BVATIPROC) wglxGetProcAddress("glNormalStream3bvATI");
		glNormalStream3sATI  = (PFNGLNORMALSTREAM3SATIPROC)  wglxGetProcAddress("glNormalStream3sATI");
		glNormalStream3svATI = (PFNGLNORMALSTREAM3SVATIPROC) wglxGetProcAddress("glNormalStream3svATI");
		glNormalStream3iATI  = (PFNGLNORMALSTREAM3IATIPROC)  wglxGetProcAddress("glNormalStream3iATI");
		glNormalStream3ivATI = (PFNGLNORMALSTREAM3IVATIPROC) wglxGetProcAddress("glNormalStream3ivATI");
		glNormalStream3fATI  = (PFNGLNORMALSTREAM3FATIPROC)  wglxGetProcAddress("glNormalStream3fATI");
		glNormalStream3fvATI = (PFNGLNORMALSTREAM3FVATIPROC) wglxGetProcAddress("glNormalStream3fvATI");
		glNormalStream3dATI  = (PFNGLNORMALSTREAM3DATIPROC)  wglxGetProcAddress("glNormalStream3dATI");
		glNormalStream3dvATI = (PFNGLNORMALSTREAM3DVATIPROC) wglxGetProcAddress("glNormalStream3dvATI");		
	}





	if (GL_EXT_blend_color_supported = isExtensionSupported("GL_EXT_blend_color")){
#ifdef LINUX
		glBlendColorEXT = (PFNGLBLENDColorEXTPROC) wglxGetProcAddress("glBlendColor");
		if (glBlendColorEXT == NULL)
#endif
		glBlendColorEXT = (PFNGLBLENDColorEXTPROC) wglxGetProcAddress("glBlendColorEXT");
	}

	if (GL_EXT_blend_func_separate_supported = isExtensionSupported("GL_EXT_blend_func_separate")){
		glBlendFuncSeparateEXT = (PFNGLBLENDFUNCSEPARATEEXTPROC) wglxGetProcAddress("glBlendFuncSeparateEXT");
	}

	GL_EXT_blend_minmax_supported   = isExtensionSupported("GL_EXT_blend_minmax");
	GL_EXT_blend_subtract_supported = isExtensionSupported("GL_EXT_blend_subtract");
	if (GL_EXT_blend_minmax_supported || GL_EXT_blend_subtract_supported){
// Workaround for a driver bug in current ATi Linux drivers
#ifdef LINUX
		glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC) wglxGetProcAddress("glBlendEquation");
		if (glBlendEquationEXT == NULL)
#endif
		glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC) wglxGetProcAddress("glBlendEquationEXT");
	}

	if (GL_EXT_draw_range_elements_supported = isExtensionSupported("GL_EXT_draw_range_elements")){
		glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC) wglxGetProcAddress("glDrawRangeElementsEXT");
	}

	if (GL_EXT_fog_coord_supported = isExtensionSupported("GL_EXT_fog_coord")){
		glFogCoordfEXT  = (PFNGLFOGCOORDFEXTPROC)  wglxGetProcAddress("glFogCoordfEXT");
		glFogCoorddEXT  = (PFNGLFOGCOORDDEXTPROC)  wglxGetProcAddress("glFogCoorddEXT");
		glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC) wglxGetProcAddress("glFogCoordfvEXT");
		glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC) wglxGetProcAddress("glFogCoorddvEXT");
		glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC) wglxGetProcAddress("glFogCoordPointerEXT");
	}

	GL_EXT_packed_pixels_supported = isExtensionSupported("GL_EXT_packed_pixels");

	if (GL_EXT_polygon_offset_supported = isExtensionSupported("GL_EXT_polygon_offset")){
		glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC) wglxGetProcAddress("glPolygonOffsetEXT");
	}

	GL_EXT_stencil_wrap_supported = isExtensionSupported("GL_EXT_stencil_wrap");
	
	if (GL_EXT_texture3D_supported = isExtensionSupported("GL_EXT_texture3D")){
// Workaround for a driver bug in current ATi Linux drivers
/*#ifdef LINUX
		glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC) wglxGetProcAddress("glTexImage3D");
		if (glTexImage3DEXT == NULL)
#endif*/
		glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC) wglxGetProcAddress("glTexImage3DEXT");
	}

	GL_EXT_texture_compression_s3tc_supported   = isExtensionSupported("GL_EXT_texture_compression_s3tc");
	GL_EXT_texture_edge_clamp_supported         = isExtensionSupported("GL_EXT_texture_edge_clamp") | isExtensionSupported("GL_SGIS_texture_edge_clamp");
	GL_EXT_texture_filter_anisotropic_supported = isExtensionSupported("GL_EXT_texture_filter_anisotropic");
	GL_EXT_texture_lod_bias_supported           = isExtensionSupported("GL_EXT_texture_lod_bias");
	GL_EXT_texture_rectangle_supported          = isExtensionSupported("GL_EXT_texture_rectangle");


	
	GL_HP_occlusion_test_supported = isExtensionSupported("GL_HP_occlusion_test");



	GL_NV_blend_square_supported = isExtensionSupported("GL_NV_blend_square");

	if (GL_NV_occlusion_query_supported = isExtensionSupported("GL_NV_occlusion_query")){
		glGenOcclusionQueriesNV    = (PFNGLGENOCCLUSIONQUERIESNVPROC)    wglxGetProcAddress("glGenOcclusionQueriesNV");
		glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC) wglxGetProcAddress("glDeleteOcclusionQueriesNV");
		glIsOcclusionQueryNV       = (PFNGLISOCCLUSIONQUERYNVPROC)       wglxGetProcAddress("glIsOcclusionQueryNV");
		glBeginOcclusionQueryNV    = (PFNGLBEGINOCCLUSIONQUERYNVPROC)    wglxGetProcAddress("glBeginOcclusionQueryNV");
		glEndOcclusionQueryNV      = (PFNGLENDOCCLUSIONQUERYNVPROC)      wglxGetProcAddress("glEndOcclusionQueryNV");
		glGetOcclusionQueryivNV    = (PFNGLGETOCCLUSIONQUERYIVNVPROC)    wglxGetProcAddress("glGetOcclusionQueryivNV");
		glGetOcclusionQueryuivNV   = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)   wglxGetProcAddress("glGetOcclusionQueryuivNV");
	}

    if (GL_NV_register_combiners_supported = isExtensionSupported("GL_NV_register_combiners")){
        glCombinerParameterfvNV = (PFNGLCOMBINERPARAMETERFVNVPROC) wglxGetProcAddress("glCombinerParameterfvNV");
        glCombinerParameterfNV  = (PFNGLCOMBINERPARAMETERFNVPROC)  wglxGetProcAddress("glCombinerParameterfNV");
        glCombinerParameterivNV = (PFNGLCOMBINERPARAMETERIVNVPROC) wglxGetProcAddress("glCombinerParameterivNV");
        glCombinerParameteriNV  = (PFNGLCOMBINERPARAMETERINVPROC)  wglxGetProcAddress("glCombinerParameteriNV");

        glCombinerInputNV       = (PFNGLCOMBINERINPUTNVPROC)       wglxGetProcAddress("glCombinerInputNV");
        glCombinerOutputNV      = (PFNGLCOMBINEROUTPUTNVPROC)      wglxGetProcAddress("glCombinerOutputNV");
        glFinalCombinerInputNV  = (PFNGLFINALCOMBINERINPUTNVPROC)  wglxGetProcAddress("glFinalCombinerInputNV");

        glGetCombinerInputParameterfvNV  = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)  wglxGetProcAddress("glGetCombinerInputParameterfvNV");
        glGetCombinerInputParameterivNV  = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)  wglxGetProcAddress("glGetCombinerInputParameterivNV");
        glGetCombinerOutputParameterfvNV = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC) wglxGetProcAddress("glGetCombinerOutputParameterfvNV");
        glGetCombinerOutputParameterivNV = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC) wglxGetProcAddress("glGetCombinerOutputParameterivNV");

        glGetFinalCombinerInputParameterfvNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC) wglxGetProcAddress("glGetFinalCombinerInputParameterfvNV");
        glGetFinalCombinerInputParameterivNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC) wglxGetProcAddress("glGetFinalCombinerInputParameterivNV");
    }

	GL_NV_texture_env_combine4_supported = isExtensionSupported("GL_NV_texture_env_combine4");




	GL_SGIS_generate_mipmap_supported = isExtensionSupported("GL_SGIS_generate_mipmap");
}
