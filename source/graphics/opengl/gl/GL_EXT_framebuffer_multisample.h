#ifndef _H_GL_EXT_FRAMEBUFFER_MULTISAMPLE
#define _H_GL_EXT_FRAMEBUFFER_MULTISAMPLE

#ifndef GL_EXT_framebuffer_multisample
#define GL_EXT_framebuffer_multisample 1
#define GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#define GL_MAX_SAMPLES_EXT                0x8D57
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#ifdef GL_GLEXT_PROTOTYPES
GLAPI void APIENTRY glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#endif
#endif /* GL_EXT_framebuffer_multisample */


#endif	//	_H_GL_EXT_FRAMEBUFFER_MULTISAMPLE