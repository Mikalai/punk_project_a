#ifndef _H_GL_NV_FRAMEBUFFER_MULTISAMPLE_COVERAGE
#define _H_GL_NV_FRAMEBUFFER_MULTISAMPLE_COVERAGE

#ifndef GL_NV_framebuffer_multisample_coverage
#define GL_NV_framebuffer_multisample_coverage 1
#define GL_RENDERBUFFER_COVERAGE_SAMPLES_NV 0x8CAB
#define GL_RENDERBUFFER_COLOR_SAMPLES_NV  0x8E10
#define GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV 0x8E11
#define GL_MULTISAMPLE_COVERAGE_MODES_NV  0x8E12
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
#ifdef GL_GLEXT_PROTOTYPES
GLAPI void APIENTRY glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
#endif
#endif /* GL_NV_framebuffer_multisample_coverage */


#endif _H_GL_NV_FRAMEBUFFER_MULTISAMPLE_COVERAGE