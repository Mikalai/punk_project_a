#ifdef WIN32
#else
#include <dlfcn.h>
#endif

#include "error/module.h"
#include "extensions.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

#ifdef _WIN32
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
#elif defined __gnu_linux__
    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
    PFNGLXGETFBCONFIGSPROC glXGetFBConfigs;
    PFNGLXCHOOSEFBCONFIGPROC glXChooseFBConfig;
    PFNGLXGETFBCONFIGATTRIBPROC glXGetFBConfigAttrib;
    PFNGLXGETVISUALFROMFBCONFIGPROC glXGetVisualFromFBConfig;
    PFNGLXCREATEWINDOWPROC glXCreateWindow;
    PFNGLXDESTROYWINDOWPROC glXDestroyWindow;
    PFNGLXCREATEPIXMAPPROC glXCreatePixmap;
    PFNGLXDESTROYPIXMAPPROC glXDestroyPixmap;
    PFNGLXCREATEPBUFFERPROC glXCreatePbuffer;
    PFNGLXDESTROYPBUFFERPROC glXDestroyPbuffer;
    PFNGLXQUERYDRAWABLEPROC glXQueryDrawable;
    PFNGLXCREATENEWCONTEXTPROC glXCreateNewContext;
    PFNGLXMAKECONTEXTCURRENTPROC glXMakeContextCurrent;
    PFNGLXGETCURRENTREADDRAWABLEPROC glXGetCurrentReadDrawable;
    PFNGLXGETCURRENTDISPLAYPROC glXGetCurrentDisplay;
    PFNGLXQUERYCONTEXTPROC glXQueryContext;
    PFNGLXSELECTEVENTPROC glXSelectEvent;
    PFNGLXGETSELECTEDEVENTPROC glXGetSelectedEvent;
    PFNGLXGETPROCADDRESSPROC glXGetProcAddress;
    PFNGLXSWAPBUFFERPROC glXSwapBuffers;
    PFNGLXQUERYVERSIONPROC glXQueryVersion;
    PFNGLXQUERYEXTENSIONSTRING glXQueryExtensionsString;
    PFNGLXISDIRECTPROC glXIsDirect;
    PFNGLXMAKECURRENT glXMakeCurrent;
#endif

    PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;
    PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
    PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameterui64v;
    PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
    PFNGLTEXPARAMETERIPROC glTexParameteri;
    PFNGLPIXELSTOREIPROC glPixelStorei;
    PFNGLPIXELSTOREFPROC glPixelStoref;
    PFNGLBLENDCOLORPROC glBlendColor;
    PFNGLBLENDEQUATIONPROC glBlendEquation;
    PFNGLBLENDEQUATIONIPROC glBlendEquationi;
    PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
    PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
    PFNGLENABLEIPROC glEnablei;
    PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
    PFNGLBLENDFUNCPROC glBlendFunc;
    PFNGLBLENDFUNCIPROC glBlendFunci;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLBUFFERSUBDATAPROC glBufferSubData;
    PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLMAPBUFFERPROC glMapBuffer;
    PFNGLUNMAPBUFFERPROC glUnmapBuffer;
    PFNGLISBUFFERPROC glIsBuffer;
    PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
    PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
    PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
    PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
    PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
    PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
    PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
    PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
    PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture1D;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
    PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLDELETESHADERPROC glDeleteShader;
    PFNGLDELETEPROGRAMPROC glDeleteProgram;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLDETACHSHADERPROC glDetachShader;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLVALIDATEPROGRAMPROC glValidateProgram;
    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM1FVPROC glUniform1fv;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM1IVPROC glUniform1iv;
    PFNGLUNIFORM2FPROC glUniform2f;
    PFNGLUNIFORM2FVPROC glUniform2fv;
    PFNGLUNIFORM2IVPROC glUniform2iv;
    PFNGLUNIFORM3FPROC glUniform3f;
    PFNGLUNIFORM3IVPROC glUniform3iv;
    PFNGLUNIFORM3FVPROC glUniform3fv;
    PFNGLUNIFORM3IPROC glUniform3i;
    PFNGLUNIFORM4FPROC glUniform4f;
    PFNGLUNIFORM4IVPROC glUniform4iv;
    PFNGLUNIFORM4FVPROC glUniform4fv;
    PFNGLUNIFORM4IPROC glUniform4i;
    PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
    PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
    PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
    PFNGLGETSHADERSOURCEPROC glGetShaderSource;
    PFNGLGETUNIFORMFVPROC glGetUniformfv;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
    PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
    PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
    PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
    PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
    PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
    PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
    PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
    PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
    PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
    PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
    PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
    PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
    PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
    PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
    PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
    PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
    PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
    PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
    PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
    PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
    PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
    PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
    PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
    PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
    PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
    PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
    PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
    PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
    PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
    PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
    PFNGLGETSTRINGIPROC glGetStringi;
    PFNGLGETERRORPROC glGetError;
    PFNGLGETINTEGERVPROC glGetIntegerv;
    PFNGLVIEWPORTPROC glViewport;
    PFNGLCLEARCOLORPROC glClearColor;
    PFNGLENABLEPROC glEnable;
    PFNGLDISABLEPROC glDisable;
    PFNGLREADPIXELSPROC glReadPixels;
    PFNGLGETSTRINGPROC glGetString;
    PFNGLGENTEXTURESPROC glGenTextures;
    PFNGLBINDTEXTUREPROC glBindTexture;
    PFNGLTEXPARAMETERFPROC glTexParameterf;
    PFNGLTEXPARAMETERFVPROC glTexParameterfv;
    PFNGLTEXIMAGE2DPROC glTexImage2D;
    PFNGLTEXIMAGE3DPROC glTexImage3D;
    PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
    PFNGLDELETETEXTURESPROC glDeleteTextures;
    PFNGLDRAWBUFFERPROC glDrawBuffer;
    PFNGLREADBUFFERPROC glReadBuffer;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLDRAWARRAYSPROC glDrawArrays;
    PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;
    PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
    PFNGLDRAWELEMENTSPROC glDrawElements;
    PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;
    PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
    PFNGLCLEARPROC glClear;
    PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
    PFNGLPOLYGONMODEPROC glPolygonMode;
    PFNGLFENCESYNCPROC glFenceSync;
    PFNGLWAITSYNCPROC glWaitSync;
    PFNGLDELETESYNCPROC glDeleteSync;
    PFNGLDRAWBUFFERSPROC glDrawBuffers;
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
    PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
    PFNGLDEPTHFUNCPROC glDepthFunc;
    PFNGLDEPTHMASKPROC glDepthMask;
    PFNGLPOINTSIZEPROC glPointSize;
    PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
    PFNGLPOINTPARAMETERIPROC glPointParameteri;
    PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
    PFNGLPOINTPARAMETERFPROC glPointParameterf;
    PFNGLCULLFACEPROC glCullFace;
    PFNGLLINEWIDTHPROC glLineWidth;
    PFNGLCLEARDEPTHFPROC glClearDepthf;
    PFNGLCLEARDEPTHPROC glClearDepth;
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC glRenderbufferStorageMultisampleCoverageNV;
    PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;
    PFNGLPOLYGONOFFSETPROC glPolygonOffset;

    //GL_ARB_shading_language_include

    PFNGLNAMEDSTRINGARBPROC glNamedStringARB;
    PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
    PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB;
    PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB;
    PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB;
    PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB;

    void* GetGraphicsProcAddress(const char* name)
    {
#ifdef _WIN32
        void* res = (void*)wglGetProcAddress(name);
        if (res != 0)
            return res;
        HMODULE lib = LoadLibrary(L"OpenGL32.dll");
        res = (void*)::GetProcAddress(lib, name);
        FreeLibrary(lib);
        GetLastError();
        return res;
#elif defined __gnu_linux__
        static void* gl_lib = nullptr;
        if (!gl_lib)
        {
            gl_lib = dlopen("libGL.so.1", RTLD_NOW);
            if (!gl_lib)
                throw Error::OpenGLException("Can't load libGL.so");
            glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)dlsym(gl_lib, "glXGetProcAddress");
        }        
        void* res = dlsym(gl_lib, name);
        if (res)
            return res;
        res = (void*)glXGetProcAddress((const GLubyte*)name);
        return res;
#endif
    }

    void InitializeOpenGLWindowSystem() {
#ifdef WIN32

#elif defined __linux__
        glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)GetGraphicsProcAddress("glXCreateContextAttribsARB");
        glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC)GetGraphicsProcAddress("glXGetFBConfigs");
        glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC)GetGraphicsProcAddress("glXChooseFBConfig");
        glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)GetGraphicsProcAddress("glXGetFBConfigAttrib");
        glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)GetGraphicsProcAddress("glXGetVisualFromFBConfig");
        glXCreateWindow = (PFNGLXCREATEWINDOWPROC)GetGraphicsProcAddress("glXCreateWindow");
        glXDestroyWindow = (PFNGLXDESTROYWINDOWPROC)GetGraphicsProcAddress("glXDestroyWindow");
        glXCreatePixmap = (PFNGLXCREATEPIXMAPPROC)GetGraphicsProcAddress("glXCreatePixmap");
        glXDestroyPixmap = (PFNGLXDESTROYPIXMAPPROC)GetGraphicsProcAddress("glXDestroyPixmap");
        glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC)GetGraphicsProcAddress("glXCreatePbuffer");
        glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC)GetGraphicsProcAddress("glXDestroyPbuffer");
        glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC)GetGraphicsProcAddress("glXQueryDrawable");
        glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)GetGraphicsProcAddress("glXCreateNewContext");
        glXMakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC)GetGraphicsProcAddress("glXMakeContextCurrent");
        glXGetCurrentReadDrawable = (PFNGLXGETCURRENTREADDRAWABLEPROC)GetGraphicsProcAddress("glXGetCurrentReadDrawable");
        glXGetCurrentDisplay = (PFNGLXGETCURRENTDISPLAYPROC)GetGraphicsProcAddress("glXGetCurrentDisplay");
        glXQueryContext = (PFNGLXQUERYCONTEXTPROC)GetGraphicsProcAddress("glXQueryContext");
        glXSelectEvent = (PFNGLXSELECTEVENTPROC)GetGraphicsProcAddress("glXSelectEvent");
        glXGetSelectedEvent = (PFNGLXGETSELECTEDEVENTPROC)GetGraphicsProcAddress("glXGetSelectedEvent");
        glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)GetGraphicsProcAddress("glXGetProcAddress");
        glXSwapBuffers = (PFNGLXSWAPBUFFERPROC)GetGraphicsProcAddress("glXSwapBuffers");
        glXQueryVersion = (PFNGLXQUERYVERSIONPROC)GetGraphicsProcAddress("glXQueryVersion");
        glXQueryExtensionsString = (PFNGLXQUERYEXTENSIONSTRING)GetGraphicsProcAddress("glXQueryExtensionsString");
        glXIsDirect = (PFNGLXISDIRECTPROC)GetGraphicsProcAddress("glXIsDirect");
        glXMakeCurrent = (PFNGLXMAKECURRENT)GetGraphicsProcAddress("glXMakeCurrent");
#endif
    }

    void InitExtensions()
    {
#ifdef _WIN32
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetGraphicsProcAddress("wglGetExtensionsStringARB");
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)GetGraphicsProcAddress("wglSwapIntervalEXT");
#endif
        glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetGraphicsProcAddress("glTexParameterf");
        glBindTexture = (PFNGLBINDTEXTUREPROC)GetGraphicsProcAddress("glBindTexture");
        glGetIntegerv = (PFNGLGETINTEGERVPROC)GetGraphicsProcAddress("glGetIntegerv");
        glGetStringi = (PFNGLGETSTRINGIPROC)GetGraphicsProcAddress("glGetStringi");
        glGetError = (PFNGLGETERRORPROC)GetGraphicsProcAddress("glGetError");
        glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)GetGraphicsProcAddress("glDrawRangeElements");
        glViewport = (PFNGLVIEWPORTPROC)GetGraphicsProcAddress("glViewport");
        glClearColor = (PFNGLCLEARCOLORPROC)GetGraphicsProcAddress("glClearColor");
        glEnable = (PFNGLENABLEPROC)GetGraphicsProcAddress("glEnable");
        glDisable = (PFNGLDISABLEPROC)GetGraphicsProcAddress("glDisable");
        glReadPixels = (PFNGLREADPIXELSPROC)GetGraphicsProcAddress("glReadPixels");
        glGetString = (PFNGLGETSTRINGPROC)GetGraphicsProcAddress("glGetString");
        glGenTextures = (PFNGLGENTEXTURESPROC)GetGraphicsProcAddress("glGenTextures");
        glBindTexture = (PFNGLBINDTEXTUREPROC)GetGraphicsProcAddress("glBindTexture");
        glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetGraphicsProcAddress("glTexParameterf");
        glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetGraphicsProcAddress("glTexParameterfv");
        glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetGraphicsProcAddress("glTexImage2D");
        glTexImage3D = (PFNGLTEXIMAGE3DPROC)GetGraphicsProcAddress("glTexImage3D");
        glFramebufferTexture2D= (PFNGLFRAMEBUFFERTEXTURE2DPROC)GetGraphicsProcAddress("glFramebufferTexture2D");
        glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetGraphicsProcAddress("glDeleteTextures");
        glDrawBuffer = (PFNGLDRAWBUFFERPROC)GetGraphicsProcAddress("glDrawBuffer");
        glReadBuffer = (PFNGLREADBUFFERPROC)GetGraphicsProcAddress("glReadBuffer");
        glBufferData = (PFNGLBUFFERDATAPROC)GetGraphicsProcAddress("glBufferData");
        glBufferSubData = (PFNGLBUFFERSUBDATAPROC)GetGraphicsProcAddress("glBufferSubData");
        glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)GetGraphicsProcAddress("glGetBufferSubData");
        glGenBuffers = (PFNGLGENBUFFERSPROC)GetGraphicsProcAddress("glGenBuffers");
        glBindBuffer = (PFNGLBINDBUFFERPROC)GetGraphicsProcAddress("glBindBuffer");
        glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)GetGraphicsProcAddress("glDeleteBuffers");
        glMapBuffer = (PFNGLMAPBUFFERPROC)GetGraphicsProcAddress("glMapBuffer");
        glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)GetGraphicsProcAddress("glUnmapBuffer");
        glIsBuffer = (PFNGLISBUFFERPROC)GetGraphicsProcAddress("glIsBuffer");
        glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)GetGraphicsProcAddress("glIsRenderbuffer");
        glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)GetGraphicsProcAddress("glBindRenderbuffer");
        glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)GetGraphicsProcAddress("glDeleteRenderbuffers");
        glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)GetGraphicsProcAddress("glGenRenderbuffers");
        glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)GetGraphicsProcAddress("glRenderbufferStorage");
        glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)GetGraphicsProcAddress("glGetRenderbufferParameteriv");
        glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)GetGraphicsProcAddress("glIsFramebuffer");
        glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)GetGraphicsProcAddress("glBindFramebuffer");
        glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)GetGraphicsProcAddress("glDeleteFramebuffers");
        glGenFramebuffers =  (PFNGLGENFRAMEBUFFERSPROC)GetGraphicsProcAddress("glGenFramebuffers");
        glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)GetGraphicsProcAddress("glCheckFramebufferStatus");
        glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)GetGraphicsProcAddress("glFramebufferRenderbuffer");
        glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)GetGraphicsProcAddress("glGetFramebufferAttachmentParameteriv");
        glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetGraphicsProcAddress("glGenerateMipmap");;
        glCreateShader = (PFNGLCREATESHADERPROC)GetGraphicsProcAddress("glCreateShader");
        glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetGraphicsProcAddress("glCreateProgram");
        glDeleteProgram = (PFNGLDELETEPROGRAMPROC)GetGraphicsProcAddress("glDeleteProgram");
        glDeleteShader = (PFNGLDELETESHADERPROC)GetGraphicsProcAddress("glDeleteShader");
        glShaderSource = (PFNGLSHADERSOURCEPROC)GetGraphicsProcAddress("glShaderSource");
        glCompileShader = (PFNGLCOMPILESHADERPROC)GetGraphicsProcAddress("glCompileShader");
        glAttachShader = (PFNGLATTACHSHADERPROC)GetGraphicsProcAddress("glAttachShader");
        glDetachShader = (PFNGLDETACHSHADERPROC)GetGraphicsProcAddress("glDetachShader");
        glLinkProgram = (PFNGLLINKPROGRAMPROC)GetGraphicsProcAddress("glLinkProgram");
        glUseProgram = (PFNGLUSEPROGRAMPROC)GetGraphicsProcAddress("glUseProgram");
        glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GetGraphicsProcAddress("glValidateProgram");
        glUniform1f = (PFNGLUNIFORM1FPROC)GetGraphicsProcAddress("glUniform1f");
        glUniform1fv = (PFNGLUNIFORM1FVPROC )GetGraphicsProcAddress("glUniform1fv");
        glUniform1i = (PFNGLUNIFORM1IPROC )GetGraphicsProcAddress("glUniform1i");
        glUniform1iv = (PFNGLUNIFORM1IVPROC )GetGraphicsProcAddress("glUniform1iv");
        glUniform2f = (PFNGLUNIFORM2FPROC )GetGraphicsProcAddress("glUniform2f");
        glUniform2fv = (PFNGLUNIFORM2FVPROC )GetGraphicsProcAddress("glUniform2fv");
        glUniform2iv = (PFNGLUNIFORM2IVPROC )GetGraphicsProcAddress("glUniform2iv");
        glUniform3f = (PFNGLUNIFORM3FPROC )GetGraphicsProcAddress("glUniform3f");
        glUniform3iv = (PFNGLUNIFORM3IVPROC )GetGraphicsProcAddress("glUniform3iv");
        glUniform3fv = (PFNGLUNIFORM3FVPROC )GetGraphicsProcAddress("glUniform3fv");
        glUniform3i = (PFNGLUNIFORM3IPROC )GetGraphicsProcAddress("glUniform3i");
        glUniform4f = (PFNGLUNIFORM4FPROC )GetGraphicsProcAddress("glUniform4f");
        glUniform4iv = (PFNGLUNIFORM4IVPROC )GetGraphicsProcAddress("glUniform4iv");
        glUniform4fv = (PFNGLUNIFORM4FVPROC )GetGraphicsProcAddress("glUniform4fv");
        glUniform4i = (PFNGLUNIFORM4IPROC )GetGraphicsProcAddress("glUniform4i");
        glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC )GetGraphicsProcAddress("glGetActiveUniform");
        glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)GetGraphicsProcAddress("glGetAttachedShaders");
        glGetShaderSource = (PFNGLGETSHADERSOURCEPROC )GetGraphicsProcAddress("glGetShaderSource");
        glGetUniformfv = (PFNGLGETUNIFORMFVPROC )GetGraphicsProcAddress("glGetUniformfv");
        glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC )GetGraphicsProcAddress("glGetUniformLocation");
        glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)GetGraphicsProcAddress("glVertexAttrib1d");
        glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)GetGraphicsProcAddress("glVertexAttrib1dv");
        glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)GetGraphicsProcAddress("glVertexAttrib1f");
        glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)GetGraphicsProcAddress("glVertexAttrib1fv");
        glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC )GetGraphicsProcAddress("glVertexAttrib1s");
        glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC )GetGraphicsProcAddress("glVertexAttrib1sv");
        glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC )GetGraphicsProcAddress("glVertexAttrib2d");
        glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC )GetGraphicsProcAddress("glVertexAttrib2dv");
        glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC )GetGraphicsProcAddress("glVertexAttrib2f");
        glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC )GetGraphicsProcAddress("glVertexAttrib2fv");
        glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC )GetGraphicsProcAddress("glVertexAttrib2s");
        glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC )GetGraphicsProcAddress("glVertexAttrib2sv");
        glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC )GetGraphicsProcAddress("glVertexAttrib3d");
        glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC )GetGraphicsProcAddress("glVertexAttrib3dv");
        glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC )GetGraphicsProcAddress("glVertexAttrib3f");
        glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC )GetGraphicsProcAddress("glVertexAttrib3fv");
        glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC )GetGraphicsProcAddress("glVertexAttrib3s");
        glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC )GetGraphicsProcAddress("glVertexAttrib3sv");
        glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC )GetGraphicsProcAddress("glVertexAttrib4d");
        glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC )GetGraphicsProcAddress("glVertexAttrib4dv");
        glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC )GetGraphicsProcAddress("glVertexAttrib4f");
        glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC )GetGraphicsProcAddress("glVertexAttrib4fv");
        glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC )GetGraphicsProcAddress("glVertexAttrib4s");
        glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC )GetGraphicsProcAddress("glVertexAttrib4sv");
        glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC )GetGraphicsProcAddress("glVertexAttribPointer");
        glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC )GetGraphicsProcAddress("glBindAttribLocation");
        glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC )GetGraphicsProcAddress("glEnableVertexAttribArray");
        glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC )GetGraphicsProcAddress("glDisableVertexAttribArray");
        glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC )GetGraphicsProcAddress("glGetVertexAttribdv");
        glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC )GetGraphicsProcAddress("glGetVertexAttribfv");
        glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC )GetGraphicsProcAddress("glGetVertexAttribiv");
        glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC )GetGraphicsProcAddress("glGetVertexAttribPointerv");
        glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC )GetGraphicsProcAddress("glGetActiveAttrib");
        glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)GetGraphicsProcAddress("glUniformMatrix2fv");
        glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)GetGraphicsProcAddress("glUniformMatrix3fv");
        glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)GetGraphicsProcAddress("glUniformMatrix4fv");
        glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GetGraphicsProcAddress("glGetAttribLocation");
        glGetShaderiv = (PFNGLGETSHADERIVPROC)GetGraphicsProcAddress("glGetShaderiv");
        glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetGraphicsProcAddress("glGetShaderInfoLog");
        glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetGraphicsProcAddress("glGetProgramiv");
        glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetGraphicsProcAddress("glGenVertexArrays");
        glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)GetGraphicsProcAddress("glDeleteVertexArrays");
        glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetGraphicsProcAddress("glBindVertexArray");
        glDrawArrays = (PFNGLDRAWARRAYSPROC)GetGraphicsProcAddress("glDrawArrays");
        glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)GetGraphicsProcAddress("glDrawArraysIndirect");
        glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)GetGraphicsProcAddress("glDrawArraysInstanced");
        glDrawElements = (PFNGLDRAWELEMENTSPROC)GetGraphicsProcAddress("glDrawElements");
        glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)GetGraphicsProcAddress("glDrawElementsIndirect");
        glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)GetGraphicsProcAddress("glDrawElementsInstanced");
        glClear = (PFNGLCLEARPROC)GetGraphicsProcAddress("glClear");
        glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)GetGraphicsProcAddress("glCompressedTexImage2D");
        glActiveTexture = (PFNGLACTIVETEXTUREPROC)GetGraphicsProcAddress("glActiveTexture");
        glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetGraphicsProcAddress("glGetProgramiv");
        glBlendFunc = (PFNGLBLENDFUNCPROC)GetGraphicsProcAddress("glBlendFunc");
        glBlendEquation = (PFNGLBLENDEQUATIONPROC)GetGraphicsProcAddress("glBlendEquation");
        glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)GetGraphicsProcAddress("glBlendEquationi");
        glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)GetGraphicsProcAddress("glBlendEquationSeparate");
        glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)GetGraphicsProcAddress("glBlendEquationSeparatei");
        glEnablei = (PFNGLENABLEIPROC)GetGraphicsProcAddress("glEnablei");
        glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)GetGraphicsProcAddress("glBlendFuncSeparate");
        glBlendFunci = (PFNGLBLENDFUNCIPROC)GetGraphicsProcAddress("glBlendFunci");
        glBlendColor = (PFNGLBLENDCOLORPROC)GetGraphicsProcAddress("glBlendColor");
        glPixelStorei = (PFNGLPIXELSTOREIPROC)GetGraphicsProcAddress("glPixelStorei");
        glPixelStoref = (PFNGLPIXELSTOREFPROC)GetGraphicsProcAddress("glPixelStoref");
        glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetGraphicsProcAddress("glTexParameteri");
        glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetGraphicsProcAddress("glGenerateMipmap");
        glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetGraphicsProcAddress("glTexSubImage2D");
        glPolygonMode = (PFNGLPOLYGONMODEPROC)GetGraphicsProcAddress("glPolygonMode");
        glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)GetGraphicsProcAddress("glGetBufferParameteri64v");
        glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)GetGraphicsProcAddress("glGetBufferParameteriv");
        glGetBufferParameterui64v = (PFNGLGETBUFFERPARAMETERI64VPROC)GetGraphicsProcAddress("glGetBufferParameterui64v");
        glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)GetGraphicsProcAddress("glGetBufferPointerv");
        glFenceSync = (PFNGLFENCESYNCPROC )GetGraphicsProcAddress("glFenceSync");
        glWaitSync = (PFNGLWAITSYNCPROC)GetGraphicsProcAddress("glWaitSync");
        glDeleteSync = (PFNGLDELETESYNCPROC)GetGraphicsProcAddress("glDeleteSync");
        glDrawBuffers = (PFNGLDRAWBUFFERSPROC)GetGraphicsProcAddress("glDrawBuffers");
        glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)GetGraphicsProcAddress("glRenderbufferStorageMultisample");
        glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)GetGraphicsProcAddress("glBlitFramebuffer");
        glDepthFunc = (PFNGLDEPTHFUNCPROC)GetGraphicsProcAddress("glDepthFunc");
        glDepthMask = (PFNGLDEPTHMASKPROC)GetGraphicsProcAddress("glDepthMask");
        glPointSize = (PFNGLPOINTSIZEPROC)GetGraphicsProcAddress("glPointSize");
        glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)GetGraphicsProcAddress("glPointParameteriv");
        glPointParameteri = (PFNGLPOINTPARAMETERIPROC)GetGraphicsProcAddress("glPointParameteri");
        glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)GetGraphicsProcAddress("glPointParameterfv");
        glPointParameterf = (PFNGLPOINTPARAMETERFPROC)GetGraphicsProcAddress("glPointParameterf");
        glCullFace = (PFNGLCULLFACEPROC)GetGraphicsProcAddress("glCullFace");
        glLineWidth = (PFNGLLINEWIDTHPROC)GetGraphicsProcAddress("glLineWidth");
        glClearDepthf = (PFNGLCLEARDEPTHFPROC)GetGraphicsProcAddress("glClearDepthf");
        glClearDepth = (PFNGLCLEARDEPTHPROC)GetGraphicsProcAddress("glClearDepth");
        glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)GetGraphicsProcAddress("glRenderbufferStorageMultisampleCoverageNV");
        glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)GetGraphicsProcAddress("glFramebufferTextureLayer");
        glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)GetGraphicsProcAddress("glPolygonOffset");

        // GL_ARB_shading_language_include
        //if (IsShaderIncludeSupported(this))
        {
            glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)GetGraphicsProcAddress("glNamedStringARB");
            glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)GetGraphicsProcAddress("glDeleteNamedStringARB");
            glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)GetGraphicsProcAddress("glCompileShaderIncludeARB");
            glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)GetGraphicsProcAddress("glIsNamedStringARB");
            glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)GetGraphicsProcAddress("glGetNamedStringARB");
            glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)GetGraphicsProcAddress("glGetNamedStringivARB");
        }
    }
    }
}
PUNK_ENGINE_END
