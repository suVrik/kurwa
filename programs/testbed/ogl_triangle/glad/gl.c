#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#if _MSC_VER >= 1400
#define GLAD_IMPL_UTIL_STRNCPY(dest, source, len) strncpy_s(dest, len, source, len-1);
#else
#define GLAD_IMPL_UTIL_STRNCPY(dest, source, len) strncpy(dest, source, len);
#endif

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */


int GLAD_GL_VERSION_1_0;
int GLAD_GL_VERSION_1_1;
int GLAD_GL_VERSION_1_2;
int GLAD_GL_VERSION_1_3;
int GLAD_GL_VERSION_1_4;
int GLAD_GL_VERSION_1_5;
int GLAD_GL_VERSION_2_0;
int GLAD_GL_VERSION_2_1;
int GLAD_GL_VERSION_3_0;
int GLAD_GL_VERSION_3_1;
int GLAD_GL_VERSION_3_2;
int GLAD_GL_VERSION_3_3;


void _pre_call_gl_callback_default(const char *name, GLADapiproc apiproc, int len_args, ...) {
    (void) len_args;

    if (apiproc == NULL) {
        fprintf(stderr, "GLAD: ERROR %s is NULL!\n", name);
        return;
    }
    if (glad_glGetError == NULL) {
        fprintf(stderr, "GLAD: ERROR glGetError is NULL!\n");
        return;
    }

    (void) glad_glGetError();
}
void _post_call_gl_callback_default(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...) {
    GLenum error_code;

    (void) ret;
    (void) apiproc;
    (void) len_args;

    error_code = glad_glGetError();

    if (error_code != GL_NO_ERROR) {
        fprintf(stderr, "GLAD: ERROR %d in %s!\n", error_code, name);
    }
}

static GLADprecallback _pre_call_gl_callback = _pre_call_gl_callback_default;
void gladSetglPreCallback(GLADprecallback cb) {
    _pre_call_gl_callback = cb;
}
static GLADpostcallback _post_call_gl_callback = _post_call_gl_callback_default;
void gladSetglPostCallback(GLADpostcallback cb) {
    _post_call_gl_callback = cb;
}

PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D;
void GLAD_API_PTR glad_debug_impl_glCopyTexImage1D(GLenum arg0, GLint arg1, GLenum arg2, GLint arg3, GLint arg4, GLsizei arg5, GLint arg6) {
    _pre_call_gl_callback("glCopyTexImage1D", (GLADapiproc) glCopyTexImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glCopyTexImage1D(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glCopyTexImage1D", (GLADapiproc) glCopyTexImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLCOPYTEXIMAGE1DPROC glad_debug_glCopyTexImage1D = glad_debug_impl_glCopyTexImage1D;
PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI3ui(GLuint arg0, GLuint arg1, GLuint arg2, GLuint arg3) {
    _pre_call_gl_callback("glVertexAttribI3ui", (GLADapiproc) glVertexAttribI3ui, 4, arg0, arg1, arg2, arg3);
    glVertexAttribI3ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribI3ui", (GLADapiproc) glVertexAttribI3ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBI3UIPROC glad_debug_glVertexAttribI3ui = glad_debug_impl_glVertexAttribI3ui;
PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;
void GLAD_API_PTR glad_debug_impl_glStencilMaskSeparate(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glStencilMaskSeparate", (GLADapiproc) glStencilMaskSeparate, 2, arg0, arg1);
    glStencilMaskSeparate(arg0, arg1);
    _post_call_gl_callback(NULL, "glStencilMaskSeparate", (GLADapiproc) glStencilMaskSeparate, 2, arg0, arg1);
    
}
PFNGLSTENCILMASKSEPARATEPROC glad_debug_glStencilMaskSeparate = glad_debug_impl_glStencilMaskSeparate;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
void GLAD_API_PTR glad_debug_impl_glFramebufferRenderbuffer(GLenum arg0, GLenum arg1, GLenum arg2, GLuint arg3) {
    _pre_call_gl_callback("glFramebufferRenderbuffer", (GLADapiproc) glFramebufferRenderbuffer, 4, arg0, arg1, arg2, arg3);
    glFramebufferRenderbuffer(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glFramebufferRenderbuffer", (GLADapiproc) glFramebufferRenderbuffer, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_debug_glFramebufferRenderbuffer = glad_debug_impl_glFramebufferRenderbuffer;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexSubImage3D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLsizei arg5, GLsizei arg6, GLsizei arg7, GLenum arg8, GLsizei arg9, const void * arg10) {
    _pre_call_gl_callback("glCompressedTexSubImage3D", (GLADapiproc) glCompressedTexSubImage3D, 11, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    glCompressedTexSubImage3D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    _post_call_gl_callback(NULL, "glCompressedTexSubImage3D", (GLADapiproc) glCompressedTexSubImage3D, 11, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    
}
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_debug_glCompressedTexSubImage3D = glad_debug_impl_glCompressedTexSubImage3D;
PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1sv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttrib1sv", (GLADapiproc) glVertexAttrib1sv, 2, arg0, arg1);
    glVertexAttrib1sv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1sv", (GLADapiproc) glVertexAttrib1sv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1SVPROC glad_debug_glVertexAttrib1sv = glad_debug_impl_glVertexAttrib1sv;
PFNGLBINDSAMPLERPROC glad_glBindSampler;
void GLAD_API_PTR glad_debug_impl_glBindSampler(GLuint arg0, GLuint arg1) {
    _pre_call_gl_callback("glBindSampler", (GLADapiproc) glBindSampler, 2, arg0, arg1);
    glBindSampler(arg0, arg1);
    _post_call_gl_callback(NULL, "glBindSampler", (GLADapiproc) glBindSampler, 2, arg0, arg1);
    
}
PFNGLBINDSAMPLERPROC glad_debug_glBindSampler = glad_debug_impl_glBindSampler;
PFNGLLINEWIDTHPROC glad_glLineWidth;
void GLAD_API_PTR glad_debug_impl_glLineWidth(GLfloat arg0) {
    _pre_call_gl_callback("glLineWidth", (GLADapiproc) glLineWidth, 1, arg0);
    glLineWidth(arg0);
    _post_call_gl_callback(NULL, "glLineWidth", (GLADapiproc) glLineWidth, 1, arg0);
    
}
PFNGLLINEWIDTHPROC glad_debug_glLineWidth = glad_debug_impl_glLineWidth;
PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v;
void GLAD_API_PTR glad_debug_impl_glGetIntegeri_v(GLenum arg0, GLuint arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetIntegeri_v", (GLADapiproc) glGetIntegeri_v, 3, arg0, arg1, arg2);
    glGetIntegeri_v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetIntegeri_v", (GLADapiproc) glGetIntegeri_v, 3, arg0, arg1, arg2);
    
}
PFNGLGETINTEGERI_VPROC glad_debug_glGetIntegeri_v = glad_debug_impl_glGetIntegeri_v;
PFNGLCOMPILESHADERPROC glad_glCompileShader;
void GLAD_API_PTR glad_debug_impl_glCompileShader(GLuint arg0) {
    _pre_call_gl_callback("glCompileShader", (GLADapiproc) glCompileShader, 1, arg0);
    glCompileShader(arg0);
    _post_call_gl_callback(NULL, "glCompileShader", (GLADapiproc) glCompileShader, 1, arg0);
    
}
PFNGLCOMPILESHADERPROC glad_debug_glCompileShader = glad_debug_impl_glCompileShader;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying;
void GLAD_API_PTR glad_debug_impl_glGetTransformFeedbackVarying(GLuint arg0, GLuint arg1, GLsizei arg2, GLsizei * arg3, GLsizei * arg4, GLenum * arg5, GLchar * arg6) {
    _pre_call_gl_callback("glGetTransformFeedbackVarying", (GLADapiproc) glGetTransformFeedbackVarying, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glGetTransformFeedbackVarying(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glGetTransformFeedbackVarying", (GLADapiproc) glGetTransformFeedbackVarying, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_debug_glGetTransformFeedbackVarying = glad_debug_impl_glGetTransformFeedbackVarying;
PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer;
void GLAD_API_PTR glad_debug_impl_glVertexAttribIPointer(GLuint arg0, GLint arg1, GLenum arg2, GLsizei arg3, const void * arg4) {
    _pre_call_gl_callback("glVertexAttribIPointer", (GLADapiproc) glVertexAttribIPointer, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttribIPointer(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttribIPointer", (GLADapiproc) glVertexAttribIPointer, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIBIPOINTERPROC glad_debug_glVertexAttribIPointer = glad_debug_impl_glVertexAttribIPointer;
PFNGLENABLEIPROC glad_glEnablei;
void GLAD_API_PTR glad_debug_impl_glEnablei(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glEnablei", (GLADapiproc) glEnablei, 2, arg0, arg1);
    glEnablei(arg0, arg1);
    _post_call_gl_callback(NULL, "glEnablei", (GLADapiproc) glEnablei, 2, arg0, arg1);
    
}
PFNGLENABLEIPROC glad_debug_glEnablei = glad_debug_impl_glEnablei;
PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP4ui(GLuint arg0, GLenum arg1, GLboolean arg2, GLuint arg3) {
    _pre_call_gl_callback("glVertexAttribP4ui", (GLADapiproc) glVertexAttribP4ui, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP4ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP4ui", (GLADapiproc) glVertexAttribP4ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP4UIPROC glad_debug_glVertexAttribP4ui = glad_debug_impl_glVertexAttribP4ui;
PFNGLCREATESHADERPROC glad_glCreateShader;
GLuint GLAD_API_PTR glad_debug_impl_glCreateShader(GLenum arg0) {
    GLuint ret;
    _pre_call_gl_callback("glCreateShader", (GLADapiproc) glCreateShader, 1, arg0);
    ret = glCreateShader(arg0);
    _post_call_gl_callback((void*) &ret, "glCreateShader", (GLADapiproc) glCreateShader, 1, arg0);
    return ret;
}
PFNGLCREATESHADERPROC glad_debug_glCreateShader = glad_debug_impl_glCreateShader;
PFNGLISBUFFERPROC glad_glIsBuffer;
GLboolean GLAD_API_PTR glad_debug_impl_glIsBuffer(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsBuffer", (GLADapiproc) glIsBuffer, 1, arg0);
    ret = glIsBuffer(arg0);
    _post_call_gl_callback((void*) &ret, "glIsBuffer", (GLADapiproc) glIsBuffer, 1, arg0);
    return ret;
}
PFNGLISBUFFERPROC glad_debug_glIsBuffer = glad_debug_impl_glIsBuffer;
PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv;
void GLAD_API_PTR glad_debug_impl_glGetMultisamplefv(GLenum arg0, GLuint arg1, GLfloat * arg2) {
    _pre_call_gl_callback("glGetMultisamplefv", (GLADapiproc) glGetMultisamplefv, 3, arg0, arg1, arg2);
    glGetMultisamplefv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetMultisamplefv", (GLADapiproc) glGetMultisamplefv, 3, arg0, arg1, arg2);
    
}
PFNGLGETMULTISAMPLEFVPROC glad_debug_glGetMultisamplefv = glad_debug_impl_glGetMultisamplefv;
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
void GLAD_API_PTR glad_debug_impl_glGenRenderbuffers(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenRenderbuffers", (GLADapiproc) glGenRenderbuffers, 2, arg0, arg1);
    glGenRenderbuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenRenderbuffers", (GLADapiproc) glGenRenderbuffers, 2, arg0, arg1);
    
}
PFNGLGENRENDERBUFFERSPROC glad_debug_glGenRenderbuffers = glad_debug_impl_glGenRenderbuffers;
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
void GLAD_API_PTR glad_debug_impl_glCopyTexSubImage2D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLint arg5, GLsizei arg6, GLsizei arg7) {
    _pre_call_gl_callback("glCopyTexSubImage2D", (GLADapiproc) glCopyTexSubImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    glCopyTexSubImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    _post_call_gl_callback(NULL, "glCopyTexSubImage2D", (GLADapiproc) glCopyTexSubImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    
}
PFNGLCOPYTEXSUBIMAGE2DPROC glad_debug_glCopyTexSubImage2D = glad_debug_impl_glCopyTexSubImage2D;
PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1d(GLuint arg0, GLdouble arg1) {
    _pre_call_gl_callback("glVertexAttrib1d", (GLADapiproc) glVertexAttrib1d, 2, arg0, arg1);
    glVertexAttrib1d(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1d", (GLADapiproc) glVertexAttrib1d, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1DPROC glad_debug_glVertexAttrib1d = glad_debug_impl_glVertexAttrib1d;
PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1f(GLuint arg0, GLfloat arg1) {
    _pre_call_gl_callback("glVertexAttrib1f", (GLADapiproc) glVertexAttrib1f, 2, arg0, arg1);
    glVertexAttrib1f(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1f", (GLADapiproc) glVertexAttrib1f, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1FPROC glad_debug_glVertexAttrib1f = glad_debug_impl_glVertexAttrib1f;
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
void GLAD_API_PTR glad_debug_impl_glBlendFuncSeparate(GLenum arg0, GLenum arg1, GLenum arg2, GLenum arg3) {
    _pre_call_gl_callback("glBlendFuncSeparate", (GLADapiproc) glBlendFuncSeparate, 4, arg0, arg1, arg2, arg3);
    glBlendFuncSeparate(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glBlendFuncSeparate", (GLADapiproc) glBlendFuncSeparate, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLBLENDFUNCSEPARATEPROC glad_debug_glBlendFuncSeparate = glad_debug_impl_glBlendFuncSeparate;
PFNGLDRAWBUFFERSPROC glad_glDrawBuffers;
void GLAD_API_PTR glad_debug_impl_glDrawBuffers(GLsizei arg0, const GLenum * arg1) {
    _pre_call_gl_callback("glDrawBuffers", (GLADapiproc) glDrawBuffers, 2, arg0, arg1);
    glDrawBuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glDrawBuffers", (GLADapiproc) glDrawBuffers, 2, arg0, arg1);
    
}
PFNGLDRAWBUFFERSPROC glad_debug_glDrawBuffers = glad_debug_impl_glDrawBuffers;
PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1s(GLuint arg0, GLshort arg1) {
    _pre_call_gl_callback("glVertexAttrib1s", (GLADapiproc) glVertexAttrib1s, 2, arg0, arg1);
    glVertexAttrib1s(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1s", (GLADapiproc) glVertexAttrib1s, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1SPROC glad_debug_glVertexAttrib1s = glad_debug_impl_glVertexAttrib1s;
PFNGLSAMPLEMASKIPROC glad_glSampleMaski;
void GLAD_API_PTR glad_debug_impl_glSampleMaski(GLuint arg0, GLbitfield arg1) {
    _pre_call_gl_callback("glSampleMaski", (GLADapiproc) glSampleMaski, 2, arg0, arg1);
    glSampleMaski(arg0, arg1);
    _post_call_gl_callback(NULL, "glSampleMaski", (GLADapiproc) glSampleMaski, 2, arg0, arg1);
    
}
PFNGLSAMPLEMASKIPROC glad_debug_glSampleMaski = glad_debug_impl_glSampleMaski;
PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix3x2fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix3x2fv", (GLADapiproc) glUniformMatrix3x2fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix3x2fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix3x2fv", (GLADapiproc) glUniformMatrix3x2fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX3X2FVPROC glad_debug_glUniformMatrix3x2fv = glad_debug_impl_glUniformMatrix3x2fv;
PFNGLPOINTSIZEPROC glad_glPointSize;
void GLAD_API_PTR glad_debug_impl_glPointSize(GLfloat arg0) {
    _pre_call_gl_callback("glPointSize", (GLADapiproc) glPointSize, 1, arg0);
    glPointSize(arg0);
    _post_call_gl_callback(NULL, "glPointSize", (GLADapiproc) glPointSize, 1, arg0);
    
}
PFNGLPOINTSIZEPROC glad_debug_glPointSize = glad_debug_impl_glPointSize;
PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2dv(GLuint arg0, const GLdouble * arg1) {
    _pre_call_gl_callback("glVertexAttrib2dv", (GLADapiproc) glVertexAttrib2dv, 2, arg0, arg1);
    glVertexAttrib2dv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib2dv", (GLADapiproc) glVertexAttrib2dv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB2DVPROC glad_debug_glVertexAttrib2dv = glad_debug_impl_glVertexAttrib2dv;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
void GLAD_API_PTR glad_debug_impl_glDeleteProgram(GLuint arg0) {
    _pre_call_gl_callback("glDeleteProgram", (GLADapiproc) glDeleteProgram, 1, arg0);
    glDeleteProgram(arg0);
    _post_call_gl_callback(NULL, "glDeleteProgram", (GLADapiproc) glDeleteProgram, 1, arg0);
    
}
PFNGLDELETEPROGRAMPROC glad_debug_glDeleteProgram = glad_debug_impl_glDeleteProgram;
PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nuiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Nuiv", (GLADapiproc) glVertexAttrib4Nuiv, 2, arg0, arg1);
    glVertexAttrib4Nuiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nuiv", (GLADapiproc) glVertexAttrib4Nuiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NUIVPROC glad_debug_glVertexAttrib4Nuiv = glad_debug_impl_glVertexAttrib4Nuiv;
PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix3x4fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix3x4fv", (GLADapiproc) glUniformMatrix3x4fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix3x4fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix3x4fv", (GLADapiproc) glUniformMatrix3x4fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX3X4FVPROC glad_debug_glUniformMatrix3x4fv = glad_debug_impl_glUniformMatrix3x4fv;
PFNGLWAITSYNCPROC glad_glWaitSync;
void GLAD_API_PTR glad_debug_impl_glWaitSync(GLsync arg0, GLbitfield arg1, GLuint64 arg2) {
    _pre_call_gl_callback("glWaitSync", (GLADapiproc) glWaitSync, 3, arg0, arg1, arg2);
    glWaitSync(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glWaitSync", (GLADapiproc) glWaitSync, 3, arg0, arg1, arg2);
    
}
PFNGLWAITSYNCPROC glad_debug_glWaitSync = glad_debug_impl_glWaitSync;
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
void GLAD_API_PTR glad_debug_impl_glRenderbufferStorage(GLenum arg0, GLenum arg1, GLsizei arg2, GLsizei arg3) {
    _pre_call_gl_callback("glRenderbufferStorage", (GLADapiproc) glRenderbufferStorage, 4, arg0, arg1, arg2, arg3);
    glRenderbufferStorage(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glRenderbufferStorage", (GLADapiproc) glRenderbufferStorage, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLRENDERBUFFERSTORAGEPROC glad_debug_glRenderbufferStorage = glad_debug_impl_glRenderbufferStorage;
PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix4x3fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix4x3fv", (GLADapiproc) glUniformMatrix4x3fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix4x3fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix4x3fv", (GLADapiproc) glUniformMatrix4x3fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX4X3FVPROC glad_debug_glUniformMatrix4x3fv = glad_debug_impl_glUniformMatrix4x3fv;
PFNGLUNIFORM3IPROC glad_glUniform3i;
void GLAD_API_PTR glad_debug_impl_glUniform3i(GLint arg0, GLint arg1, GLint arg2, GLint arg3) {
    _pre_call_gl_callback("glUniform3i", (GLADapiproc) glUniform3i, 4, arg0, arg1, arg2, arg3);
    glUniform3i(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniform3i", (GLADapiproc) glUniform3i, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORM3IPROC glad_debug_glUniform3i = glad_debug_impl_glUniform3i;
PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv;
void GLAD_API_PTR glad_debug_impl_glClearBufferfv(GLenum arg0, GLint arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glClearBufferfv", (GLADapiproc) glClearBufferfv, 3, arg0, arg1, arg2);
    glClearBufferfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glClearBufferfv", (GLADapiproc) glClearBufferfv, 3, arg0, arg1, arg2);
    
}
PFNGLCLEARBUFFERFVPROC glad_debug_glClearBufferfv = glad_debug_impl_glClearBufferfv;
PFNGLUNIFORM3FPROC glad_glUniform3f;
void GLAD_API_PTR glad_debug_impl_glUniform3f(GLint arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3) {
    _pre_call_gl_callback("glUniform3f", (GLADapiproc) glUniform3f, 4, arg0, arg1, arg2, arg3);
    glUniform3f(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniform3f", (GLADapiproc) glUniform3f, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORM3FPROC glad_debug_glUniform3f = glad_debug_impl_glUniform3f;
PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4ubv(GLuint arg0, const GLubyte * arg1) {
    _pre_call_gl_callback("glVertexAttrib4ubv", (GLADapiproc) glVertexAttrib4ubv, 2, arg0, arg1);
    glVertexAttrib4ubv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4ubv", (GLADapiproc) glVertexAttrib4ubv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4UBVPROC glad_debug_glVertexAttrib4ubv = glad_debug_impl_glVertexAttrib4ubv;
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetBufferParameteriv(GLenum arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetBufferParameteriv", (GLADapiproc) glGetBufferParameteriv, 3, arg0, arg1, arg2);
    glGetBufferParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetBufferParameteriv", (GLADapiproc) glGetBufferParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLGETBUFFERPARAMETERIVPROC glad_debug_glGetBufferParameteriv = glad_debug_impl_glGetBufferParameteriv;
PFNGLCOLORMASKIPROC glad_glColorMaski;
void GLAD_API_PTR glad_debug_impl_glColorMaski(GLuint arg0, GLboolean arg1, GLboolean arg2, GLboolean arg3, GLboolean arg4) {
    _pre_call_gl_callback("glColorMaski", (GLADapiproc) glColorMaski, 5, arg0, arg1, arg2, arg3, arg4);
    glColorMaski(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glColorMaski", (GLADapiproc) glColorMaski, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLCOLORMASKIPROC glad_debug_glColorMaski = glad_debug_impl_glColorMaski;
PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi;
void GLAD_API_PTR glad_debug_impl_glClearBufferfi(GLenum arg0, GLint arg1, GLfloat arg2, GLint arg3) {
    _pre_call_gl_callback("glClearBufferfi", (GLADapiproc) glClearBufferfi, 4, arg0, arg1, arg2, arg3);
    glClearBufferfi(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glClearBufferfi", (GLADapiproc) glClearBufferfi, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLCLEARBUFFERFIPROC glad_debug_glClearBufferfi = glad_debug_impl_glClearBufferfi;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
void GLAD_API_PTR glad_debug_impl_glGenVertexArrays(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenVertexArrays", (GLADapiproc) glGenVertexArrays, 2, arg0, arg1);
    glGenVertexArrays(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenVertexArrays", (GLADapiproc) glGenVertexArrays, 2, arg0, arg1);
    
}
PFNGLGENVERTEXARRAYSPROC glad_debug_glGenVertexArrays = glad_debug_impl_glGenVertexArrays;
PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv;
void GLAD_API_PTR glad_debug_impl_glGetSamplerParameterIiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetSamplerParameterIiv", (GLADapiproc) glGetSamplerParameterIiv, 3, arg0, arg1, arg2);
    glGetSamplerParameterIiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetSamplerParameterIiv", (GLADapiproc) glGetSamplerParameterIiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETSAMPLERPARAMETERIIVPROC glad_debug_glGetSamplerParameterIiv = glad_debug_impl_glGetSamplerParameterIiv;
PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex;
GLint GLAD_API_PTR glad_debug_impl_glGetFragDataIndex(GLuint arg0, const GLchar * arg1) {
    GLint ret;
    _pre_call_gl_callback("glGetFragDataIndex", (GLADapiproc) glGetFragDataIndex, 2, arg0, arg1);
    ret = glGetFragDataIndex(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetFragDataIndex", (GLADapiproc) glGetFragDataIndex, 2, arg0, arg1);
    return ret;
}
PFNGLGETFRAGDATAINDEXPROC glad_debug_glGetFragDataIndex = glad_debug_impl_glGetFragDataIndex;
PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribdv(GLuint arg0, GLenum arg1, GLdouble * arg2) {
    _pre_call_gl_callback("glGetVertexAttribdv", (GLADapiproc) glGetVertexAttribdv, 3, arg0, arg1, arg2);
    glGetVertexAttribdv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribdv", (GLADapiproc) glGetVertexAttribdv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBDVPROC glad_debug_glGetVertexAttribdv = glad_debug_impl_glGetVertexAttribdv;
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;
void GLAD_API_PTR glad_debug_impl_glDeleteFramebuffers(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteFramebuffers", (GLADapiproc) glDeleteFramebuffers, 2, arg0, arg1);
    glDeleteFramebuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteFramebuffers", (GLADapiproc) glDeleteFramebuffers, 2, arg0, arg1);
    
}
PFNGLDELETEFRAMEBUFFERSPROC glad_debug_glDeleteFramebuffers = glad_debug_impl_glDeleteFramebuffers;
PFNGLDRAWARRAYSPROC glad_glDrawArrays;
void GLAD_API_PTR glad_debug_impl_glDrawArrays(GLenum arg0, GLint arg1, GLsizei arg2) {
    _pre_call_gl_callback("glDrawArrays", (GLADapiproc) glDrawArrays, 3, arg0, arg1, arg2);
    glDrawArrays(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glDrawArrays", (GLADapiproc) glDrawArrays, 3, arg0, arg1, arg2);
    
}
PFNGLDRAWARRAYSPROC glad_debug_glDrawArrays = glad_debug_impl_glDrawArrays;
PFNGLUNIFORM1UIPROC glad_glUniform1ui;
void GLAD_API_PTR glad_debug_impl_glUniform1ui(GLint arg0, GLuint arg1) {
    _pre_call_gl_callback("glUniform1ui", (GLADapiproc) glUniform1ui, 2, arg0, arg1);
    glUniform1ui(arg0, arg1);
    _post_call_gl_callback(NULL, "glUniform1ui", (GLADapiproc) glUniform1ui, 2, arg0, arg1);
    
}
PFNGLUNIFORM1UIPROC glad_debug_glUniform1ui = glad_debug_impl_glUniform1ui;
PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI2i(GLuint arg0, GLint arg1, GLint arg2) {
    _pre_call_gl_callback("glVertexAttribI2i", (GLADapiproc) glVertexAttribI2i, 3, arg0, arg1, arg2);
    glVertexAttribI2i(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glVertexAttribI2i", (GLADapiproc) glVertexAttribI2i, 3, arg0, arg1, arg2);
    
}
PFNGLVERTEXATTRIBI2IPROC glad_debug_glVertexAttribI2i = glad_debug_impl_glVertexAttribI2i;
PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3d(GLuint arg0, GLdouble arg1, GLdouble arg2, GLdouble arg3) {
    _pre_call_gl_callback("glVertexAttrib3d", (GLADapiproc) glVertexAttrib3d, 4, arg0, arg1, arg2, arg3);
    glVertexAttrib3d(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttrib3d", (GLADapiproc) glVertexAttrib3d, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIB3DPROC glad_debug_glVertexAttrib3d = glad_debug_impl_glVertexAttrib3d;
PFNGLCLEARPROC glad_glClear;
void GLAD_API_PTR glad_debug_impl_glClear(GLbitfield arg0) {
    _pre_call_gl_callback("glClear", (GLADapiproc) glClear, 1, arg0);
    glClear(arg0);
    _post_call_gl_callback(NULL, "glClear", (GLADapiproc) glClear, 1, arg0);
    
}
PFNGLCLEARPROC glad_debug_glClear = glad_debug_impl_glClear;
PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName;
void GLAD_API_PTR glad_debug_impl_glGetActiveUniformName(GLuint arg0, GLuint arg1, GLsizei arg2, GLsizei * arg3, GLchar * arg4) {
    _pre_call_gl_callback("glGetActiveUniformName", (GLADapiproc) glGetActiveUniformName, 5, arg0, arg1, arg2, arg3, arg4);
    glGetActiveUniformName(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glGetActiveUniformName", (GLADapiproc) glGetActiveUniformName, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLGETACTIVEUNIFORMNAMEPROC glad_debug_glGetActiveUniformName = glad_debug_impl_glGetActiveUniformName;
PFNGLISENABLEDPROC glad_glIsEnabled;
GLboolean GLAD_API_PTR glad_debug_impl_glIsEnabled(GLenum arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsEnabled", (GLADapiproc) glIsEnabled, 1, arg0);
    ret = glIsEnabled(arg0);
    _post_call_gl_callback((void*) &ret, "glIsEnabled", (GLADapiproc) glIsEnabled, 1, arg0);
    return ret;
}
PFNGLISENABLEDPROC glad_debug_glIsEnabled = glad_debug_impl_glIsEnabled;
PFNGLSTENCILOPPROC glad_glStencilOp;
void GLAD_API_PTR glad_debug_impl_glStencilOp(GLenum arg0, GLenum arg1, GLenum arg2) {
    _pre_call_gl_callback("glStencilOp", (GLADapiproc) glStencilOp, 3, arg0, arg1, arg2);
    glStencilOp(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glStencilOp", (GLADapiproc) glStencilOp, 3, arg0, arg1, arg2);
    
}
PFNGLSTENCILOPPROC glad_debug_glStencilOp = glad_debug_impl_glStencilOp;
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
void GLAD_API_PTR glad_debug_impl_glFramebufferTexture2D(GLenum arg0, GLenum arg1, GLenum arg2, GLuint arg3, GLint arg4) {
    _pre_call_gl_callback("glFramebufferTexture2D", (GLADapiproc) glFramebufferTexture2D, 5, arg0, arg1, arg2, arg3, arg4);
    glFramebufferTexture2D(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glFramebufferTexture2D", (GLADapiproc) glFramebufferTexture2D, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_debug_glFramebufferTexture2D = glad_debug_impl_glFramebufferTexture2D;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetFramebufferAttachmentParameteriv(GLenum arg0, GLenum arg1, GLenum arg2, GLint * arg3) {
    _pre_call_gl_callback("glGetFramebufferAttachmentParameteriv", (GLADapiproc) glGetFramebufferAttachmentParameteriv, 4, arg0, arg1, arg2, arg3);
    glGetFramebufferAttachmentParameteriv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetFramebufferAttachmentParameteriv", (GLADapiproc) glGetFramebufferAttachmentParameteriv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_debug_glGetFramebufferAttachmentParameteriv = glad_debug_impl_glGetFramebufferAttachmentParameteriv;
PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nub(GLuint arg0, GLubyte arg1, GLubyte arg2, GLubyte arg3, GLubyte arg4) {
    _pre_call_gl_callback("glVertexAttrib4Nub", (GLADapiproc) glVertexAttrib4Nub, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttrib4Nub(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nub", (GLADapiproc) glVertexAttrib4Nub, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIB4NUBPROC glad_debug_glVertexAttrib4Nub = glad_debug_impl_glVertexAttrib4Nub;
PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation;
GLint GLAD_API_PTR glad_debug_impl_glGetFragDataLocation(GLuint arg0, const GLchar * arg1) {
    GLint ret;
    _pre_call_gl_callback("glGetFragDataLocation", (GLADapiproc) glGetFragDataLocation, 2, arg0, arg1);
    ret = glGetFragDataLocation(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetFragDataLocation", (GLADapiproc) glGetFragDataLocation, 2, arg0, arg1);
    return ret;
}
PFNGLGETFRAGDATALOCATIONPROC glad_debug_glGetFragDataLocation = glad_debug_impl_glGetFragDataLocation;
PFNGLTEXIMAGE1DPROC glad_glTexImage1D;
void GLAD_API_PTR glad_debug_impl_glTexImage1D(GLenum arg0, GLint arg1, GLint arg2, GLsizei arg3, GLint arg4, GLenum arg5, GLenum arg6, const void * arg7) {
    _pre_call_gl_callback("glTexImage1D", (GLADapiproc) glTexImage1D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    glTexImage1D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    _post_call_gl_callback(NULL, "glTexImage1D", (GLADapiproc) glTexImage1D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    
}
PFNGLTEXIMAGE1DPROC glad_debug_glTexImage1D = glad_debug_impl_glTexImage1D;
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
void GLAD_API_PTR glad_debug_impl_glTexParameteriv(GLenum arg0, GLenum arg1, const GLint * arg2) {
    _pre_call_gl_callback("glTexParameteriv", (GLADapiproc) glTexParameteriv, 3, arg0, arg1, arg2);
    glTexParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameteriv", (GLADapiproc) glTexParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERIVPROC glad_debug_glTexParameteriv = glad_debug_impl_glTexParameteriv;
PFNGLGETTEXIMAGEPROC glad_glGetTexImage;
void GLAD_API_PTR glad_debug_impl_glGetTexImage(GLenum arg0, GLint arg1, GLenum arg2, GLenum arg3, void * arg4) {
    _pre_call_gl_callback("glGetTexImage", (GLADapiproc) glGetTexImage, 5, arg0, arg1, arg2, arg3, arg4);
    glGetTexImage(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glGetTexImage", (GLADapiproc) glGetTexImage, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLGETTEXIMAGEPROC glad_debug_glGetTexImage = glad_debug_impl_glGetTexImage;
PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v;
void GLAD_API_PTR glad_debug_impl_glGetQueryObjecti64v(GLuint arg0, GLenum arg1, GLint64 * arg2) {
    _pre_call_gl_callback("glGetQueryObjecti64v", (GLADapiproc) glGetQueryObjecti64v, 3, arg0, arg1, arg2);
    glGetQueryObjecti64v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetQueryObjecti64v", (GLADapiproc) glGetQueryObjecti64v, 3, arg0, arg1, arg2);
    
}
PFNGLGETQUERYOBJECTI64VPROC glad_debug_glGetQueryObjecti64v = glad_debug_impl_glGetQueryObjecti64v;
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
void GLAD_API_PTR glad_debug_impl_glGenFramebuffers(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenFramebuffers", (GLADapiproc) glGenFramebuffers, 2, arg0, arg1);
    glGenFramebuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenFramebuffers", (GLADapiproc) glGenFramebuffers, 2, arg0, arg1);
    
}
PFNGLGENFRAMEBUFFERSPROC glad_debug_glGenFramebuffers = glad_debug_impl_glGenFramebuffers;
PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;
void GLAD_API_PTR glad_debug_impl_glGetAttachedShaders(GLuint arg0, GLsizei arg1, GLsizei * arg2, GLuint * arg3) {
    _pre_call_gl_callback("glGetAttachedShaders", (GLADapiproc) glGetAttachedShaders, 4, arg0, arg1, arg2, arg3);
    glGetAttachedShaders(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetAttachedShaders", (GLADapiproc) glGetAttachedShaders, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETATTACHEDSHADERSPROC glad_debug_glGetAttachedShaders = glad_debug_impl_glGetAttachedShaders;
PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;
GLboolean GLAD_API_PTR glad_debug_impl_glIsRenderbuffer(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsRenderbuffer", (GLADapiproc) glIsRenderbuffer, 1, arg0);
    ret = glIsRenderbuffer(arg0);
    _post_call_gl_callback((void*) &ret, "glIsRenderbuffer", (GLADapiproc) glIsRenderbuffer, 1, arg0);
    return ret;
}
PFNGLISRENDERBUFFERPROC glad_debug_glIsRenderbuffer = glad_debug_impl_glIsRenderbuffer;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
void GLAD_API_PTR glad_debug_impl_glDeleteVertexArrays(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteVertexArrays", (GLADapiproc) glDeleteVertexArrays, 2, arg0, arg1);
    glDeleteVertexArrays(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteVertexArrays", (GLADapiproc) glDeleteVertexArrays, 2, arg0, arg1);
    
}
PFNGLDELETEVERTEXARRAYSPROC glad_debug_glDeleteVertexArrays = glad_debug_impl_glDeleteVertexArrays;
PFNGLISVERTEXARRAYPROC glad_glIsVertexArray;
GLboolean GLAD_API_PTR glad_debug_impl_glIsVertexArray(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsVertexArray", (GLADapiproc) glIsVertexArray, 1, arg0);
    ret = glIsVertexArray(arg0);
    _post_call_gl_callback((void*) &ret, "glIsVertexArray", (GLADapiproc) glIsVertexArray, 1, arg0);
    return ret;
}
PFNGLISVERTEXARRAYPROC glad_debug_glIsVertexArray = glad_debug_impl_glIsVertexArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
void GLAD_API_PTR glad_debug_impl_glDisableVertexAttribArray(GLuint arg0) {
    _pre_call_gl_callback("glDisableVertexAttribArray", (GLADapiproc) glDisableVertexAttribArray, 1, arg0);
    glDisableVertexAttribArray(arg0);
    _post_call_gl_callback(NULL, "glDisableVertexAttribArray", (GLADapiproc) glDisableVertexAttribArray, 1, arg0);
    
}
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_debug_glDisableVertexAttribArray = glad_debug_impl_glDisableVertexAttribArray;
PFNGLGETQUERYIVPROC glad_glGetQueryiv;
void GLAD_API_PTR glad_debug_impl_glGetQueryiv(GLenum arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetQueryiv", (GLADapiproc) glGetQueryiv, 3, arg0, arg1, arg2);
    glGetQueryiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetQueryiv", (GLADapiproc) glGetQueryiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETQUERYIVPROC glad_debug_glGetQueryiv = glad_debug_impl_glGetQueryiv;
PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv;
void GLAD_API_PTR glad_debug_impl_glGetSamplerParameterfv(GLuint arg0, GLenum arg1, GLfloat * arg2) {
    _pre_call_gl_callback("glGetSamplerParameterfv", (GLADapiproc) glGetSamplerParameterfv, 3, arg0, arg1, arg2);
    glGetSamplerParameterfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetSamplerParameterfv", (GLADapiproc) glGetSamplerParameterfv, 3, arg0, arg1, arg2);
    
}
PFNGLGETSAMPLERPARAMETERFVPROC glad_debug_glGetSamplerParameterfv = glad_debug_impl_glGetSamplerParameterfv;
PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices;
void GLAD_API_PTR glad_debug_impl_glGetUniformIndices(GLuint arg0, GLsizei arg1, const GLchar *const* arg2, GLuint * arg3) {
    _pre_call_gl_callback("glGetUniformIndices", (GLADapiproc) glGetUniformIndices, 4, arg0, arg1, arg2, arg3);
    glGetUniformIndices(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetUniformIndices", (GLADapiproc) glGetUniformIndices, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETUNIFORMINDICESPROC glad_debug_glGetUniformIndices = glad_debug_impl_glGetUniformIndices;
PFNGLISSHADERPROC glad_glIsShader;
GLboolean GLAD_API_PTR glad_debug_impl_glIsShader(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsShader", (GLADapiproc) glIsShader, 1, arg0);
    ret = glIsShader(arg0);
    _post_call_gl_callback((void*) &ret, "glIsShader", (GLADapiproc) glIsShader, 1, arg0);
    return ret;
}
PFNGLISSHADERPROC glad_debug_glIsShader = glad_debug_impl_glIsShader;
PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4ubv(GLuint arg0, const GLubyte * arg1) {
    _pre_call_gl_callback("glVertexAttribI4ubv", (GLADapiproc) glVertexAttribI4ubv, 2, arg0, arg1);
    glVertexAttribI4ubv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4ubv", (GLADapiproc) glVertexAttribI4ubv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4UBVPROC glad_debug_glVertexAttribI4ubv = glad_debug_impl_glVertexAttribI4ubv;
PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv;
void GLAD_API_PTR glad_debug_impl_glPointParameteriv(GLenum arg0, const GLint * arg1) {
    _pre_call_gl_callback("glPointParameteriv", (GLADapiproc) glPointParameteriv, 2, arg0, arg1);
    glPointParameteriv(arg0, arg1);
    _post_call_gl_callback(NULL, "glPointParameteriv", (GLADapiproc) glPointParameteriv, 2, arg0, arg1);
    
}
PFNGLPOINTPARAMETERIVPROC glad_debug_glPointParameteriv = glad_debug_impl_glPointParameteriv;
PFNGLDISABLEPROC glad_glDisable;
void GLAD_API_PTR glad_debug_impl_glDisable(GLenum arg0) {
    _pre_call_gl_callback("glDisable", (GLADapiproc) glDisable, 1, arg0);
    glDisable(arg0);
    _post_call_gl_callback(NULL, "glDisable", (GLADapiproc) glDisable, 1, arg0);
    
}
PFNGLDISABLEPROC glad_debug_glDisable = glad_debug_impl_glDisable;
PFNGLENABLEPROC glad_glEnable;
void GLAD_API_PTR glad_debug_impl_glEnable(GLenum arg0) {
    _pre_call_gl_callback("glEnable", (GLADapiproc) glEnable, 1, arg0);
    glEnable(arg0);
    _post_call_gl_callback(NULL, "glEnable", (GLADapiproc) glEnable, 1, arg0);
    
}
PFNGLENABLEPROC glad_debug_glEnable = glad_debug_impl_glEnable;
PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv;
void GLAD_API_PTR glad_debug_impl_glGetActiveUniformsiv(GLuint arg0, GLsizei arg1, const GLuint * arg2, GLenum arg3, GLint * arg4) {
    _pre_call_gl_callback("glGetActiveUniformsiv", (GLADapiproc) glGetActiveUniformsiv, 5, arg0, arg1, arg2, arg3, arg4);
    glGetActiveUniformsiv(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glGetActiveUniformsiv", (GLADapiproc) glGetActiveUniformsiv, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLGETACTIVEUNIFORMSIVPROC glad_debug_glGetActiveUniformsiv = glad_debug_impl_glGetActiveUniformsiv;
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;
GLint GLAD_API_PTR glad_debug_impl_glGetAttribLocation(GLuint arg0, const GLchar * arg1) {
    GLint ret;
    _pre_call_gl_callback("glGetAttribLocation", (GLADapiproc) glGetAttribLocation, 2, arg0, arg1);
    ret = glGetAttribLocation(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetAttribLocation", (GLADapiproc) glGetAttribLocation, 2, arg0, arg1);
    return ret;
}
PFNGLGETATTRIBLOCATIONPROC glad_debug_glGetAttribLocation = glad_debug_impl_glGetAttribLocation;
PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4dv(GLuint arg0, const GLdouble * arg1) {
    _pre_call_gl_callback("glVertexAttrib4dv", (GLADapiproc) glVertexAttrib4dv, 2, arg0, arg1);
    glVertexAttrib4dv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4dv", (GLADapiproc) glVertexAttrib4dv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4DVPROC glad_debug_glVertexAttrib4dv = glad_debug_impl_glVertexAttrib4dv;
PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP3ui(GLuint arg0, GLenum arg1, GLboolean arg2, GLuint arg3) {
    _pre_call_gl_callback("glVertexAttribP3ui", (GLADapiproc) glVertexAttribP3ui, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP3ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP3ui", (GLADapiproc) glVertexAttribP3ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP3UIPROC glad_debug_glVertexAttribP3ui = glad_debug_impl_glVertexAttribP3ui;
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
void GLAD_API_PTR glad_debug_impl_glPolygonOffset(GLfloat arg0, GLfloat arg1) {
    _pre_call_gl_callback("glPolygonOffset", (GLADapiproc) glPolygonOffset, 2, arg0, arg1);
    glPolygonOffset(arg0, arg1);
    _post_call_gl_callback(NULL, "glPolygonOffset", (GLADapiproc) glPolygonOffset, 2, arg0, arg1);
    
}
PFNGLPOLYGONOFFSETPROC glad_debug_glPolygonOffset = glad_debug_impl_glPolygonOffset;
PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv;
void GLAD_API_PTR glad_debug_impl_glGetUniformuiv(GLuint arg0, GLint arg1, GLuint * arg2) {
    _pre_call_gl_callback("glGetUniformuiv", (GLADapiproc) glGetUniformuiv, 3, arg0, arg1, arg2);
    glGetUniformuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetUniformuiv", (GLADapiproc) glGetUniformuiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETUNIFORMUIVPROC glad_debug_glGetUniformuiv = glad_debug_impl_glGetUniformuiv;
PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribIiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetVertexAttribIiv", (GLADapiproc) glGetVertexAttribIiv, 3, arg0, arg1, arg2);
    glGetVertexAttribIiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribIiv", (GLADapiproc) glGetVertexAttribIiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBIIVPROC glad_debug_glGetVertexAttribIiv = glad_debug_impl_glGetVertexAttribIiv;
PFNGLDRAWBUFFERPROC glad_glDrawBuffer;
void GLAD_API_PTR glad_debug_impl_glDrawBuffer(GLenum arg0) {
    _pre_call_gl_callback("glDrawBuffer", (GLADapiproc) glDrawBuffer, 1, arg0);
    glDrawBuffer(arg0);
    _post_call_gl_callback(NULL, "glDrawBuffer", (GLADapiproc) glDrawBuffer, 1, arg0);
    
}
PFNGLDRAWBUFFERPROC glad_debug_glDrawBuffer = glad_debug_impl_glDrawBuffer;
PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv;
void GLAD_API_PTR glad_debug_impl_glClearBufferuiv(GLenum arg0, GLint arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glClearBufferuiv", (GLADapiproc) glClearBufferuiv, 3, arg0, arg1, arg2);
    glClearBufferuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glClearBufferuiv", (GLADapiproc) glClearBufferuiv, 3, arg0, arg1, arg2);
    
}
PFNGLCLEARBUFFERUIVPROC glad_debug_glClearBufferuiv = glad_debug_impl_glClearBufferuiv;
PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced;
void GLAD_API_PTR glad_debug_impl_glDrawElementsInstanced(GLenum arg0, GLsizei arg1, GLenum arg2, const void * arg3, GLsizei arg4) {
    _pre_call_gl_callback("glDrawElementsInstanced", (GLADapiproc) glDrawElementsInstanced, 5, arg0, arg1, arg2, arg3, arg4);
    glDrawElementsInstanced(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glDrawElementsInstanced", (GLADapiproc) glDrawElementsInstanced, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLDRAWELEMENTSINSTANCEDPROC glad_debug_glDrawElementsInstanced = glad_debug_impl_glDrawElementsInstanced;
PFNGLFLUSHPROC glad_glFlush;
void GLAD_API_PTR glad_debug_impl_glFlush(void) {
    _pre_call_gl_callback("glFlush", (GLADapiproc) glFlush, 0);
    glFlush();
    _post_call_gl_callback(NULL, "glFlush", (GLADapiproc) glFlush, 0);
    
}
PFNGLFLUSHPROC glad_debug_glFlush = glad_debug_impl_glFlush;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetRenderbufferParameteriv(GLenum arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetRenderbufferParameteriv", (GLADapiproc) glGetRenderbufferParameteriv, 3, arg0, arg1, arg2);
    glGetRenderbufferParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetRenderbufferParameteriv", (GLADapiproc) glGetRenderbufferParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_debug_glGetRenderbufferParameteriv = glad_debug_impl_glGetRenderbufferParameteriv;
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribPointerv(GLuint arg0, GLenum arg1, void ** arg2) {
    _pre_call_gl_callback("glGetVertexAttribPointerv", (GLADapiproc) glGetVertexAttribPointerv, 3, arg0, arg1, arg2);
    glGetVertexAttribPointerv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribPointerv", (GLADapiproc) glGetVertexAttribPointerv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_debug_glGetVertexAttribPointerv = glad_debug_impl_glGetVertexAttribPointerv;
PFNGLFENCESYNCPROC glad_glFenceSync;
GLsync GLAD_API_PTR glad_debug_impl_glFenceSync(GLenum arg0, GLbitfield arg1) {
    GLsync ret;
    _pre_call_gl_callback("glFenceSync", (GLADapiproc) glFenceSync, 2, arg0, arg1);
    ret = glFenceSync(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glFenceSync", (GLADapiproc) glFenceSync, 2, arg0, arg1);
    return ret;
}
PFNGLFENCESYNCPROC glad_debug_glFenceSync = glad_debug_impl_glFenceSync;
PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3sv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttrib3sv", (GLADapiproc) glVertexAttrib3sv, 2, arg0, arg1);
    glVertexAttrib3sv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib3sv", (GLADapiproc) glVertexAttrib3sv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB3SVPROC glad_debug_glVertexAttrib3sv = glad_debug_impl_glVertexAttrib3sv;
PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender;
void GLAD_API_PTR glad_debug_impl_glBeginConditionalRender(GLuint arg0, GLenum arg1) {
    _pre_call_gl_callback("glBeginConditionalRender", (GLADapiproc) glBeginConditionalRender, 2, arg0, arg1);
    glBeginConditionalRender(arg0, arg1);
    _post_call_gl_callback(NULL, "glBeginConditionalRender", (GLADapiproc) glBeginConditionalRender, 2, arg0, arg1);
    
}
PFNGLBEGINCONDITIONALRENDERPROC glad_debug_glBeginConditionalRender = glad_debug_impl_glBeginConditionalRender;
PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetTexLevelParameteriv(GLenum arg0, GLint arg1, GLenum arg2, GLint * arg3) {
    _pre_call_gl_callback("glGetTexLevelParameteriv", (GLADapiproc) glGetTexLevelParameteriv, 4, arg0, arg1, arg2, arg3);
    glGetTexLevelParameteriv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetTexLevelParameteriv", (GLADapiproc) glGetTexLevelParameteriv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETTEXLEVELPARAMETERIVPROC glad_debug_glGetTexLevelParameteriv = glad_debug_impl_glGetTexLevelParameteriv;
PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;
void GLAD_API_PTR glad_debug_impl_glStencilFuncSeparate(GLenum arg0, GLenum arg1, GLint arg2, GLuint arg3) {
    _pre_call_gl_callback("glStencilFuncSeparate", (GLADapiproc) glStencilFuncSeparate, 4, arg0, arg1, arg2, arg3);
    glStencilFuncSeparate(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glStencilFuncSeparate", (GLADapiproc) glStencilFuncSeparate, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLSTENCILFUNCSEPARATEPROC glad_debug_glStencilFuncSeparate = glad_debug_impl_glStencilFuncSeparate;
PFNGLGENSAMPLERSPROC glad_glGenSamplers;
void GLAD_API_PTR glad_debug_impl_glGenSamplers(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenSamplers", (GLADapiproc) glGenSamplers, 2, arg0, arg1);
    glGenSamplers(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenSamplers", (GLADapiproc) glGenSamplers, 2, arg0, arg1);
    
}
PFNGLGENSAMPLERSPROC glad_debug_glGenSamplers = glad_debug_impl_glGenSamplers;
PFNGLCLAMPCOLORPROC glad_glClampColor;
void GLAD_API_PTR glad_debug_impl_glClampColor(GLenum arg0, GLenum arg1) {
    _pre_call_gl_callback("glClampColor", (GLADapiproc) glClampColor, 2, arg0, arg1);
    glClampColor(arg0, arg1);
    _post_call_gl_callback(NULL, "glClampColor", (GLADapiproc) glClampColor, 2, arg0, arg1);
    
}
PFNGLCLAMPCOLORPROC glad_debug_glClampColor = glad_debug_impl_glClampColor;
PFNGLUNIFORM4IVPROC glad_glUniform4iv;
void GLAD_API_PTR glad_debug_impl_glUniform4iv(GLint arg0, GLsizei arg1, const GLint * arg2) {
    _pre_call_gl_callback("glUniform4iv", (GLADapiproc) glUniform4iv, 3, arg0, arg1, arg2);
    glUniform4iv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform4iv", (GLADapiproc) glUniform4iv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM4IVPROC glad_debug_glUniform4iv = glad_debug_impl_glUniform4iv;
PFNGLCLEARSTENCILPROC glad_glClearStencil;
void GLAD_API_PTR glad_debug_impl_glClearStencil(GLint arg0) {
    _pre_call_gl_callback("glClearStencil", (GLADapiproc) glClearStencil, 1, arg0);
    glClearStencil(arg0);
    _post_call_gl_callback(NULL, "glClearStencil", (GLADapiproc) glClearStencil, 1, arg0);
    
}
PFNGLCLEARSTENCILPROC glad_debug_glClearStencil = glad_debug_impl_glClearStencil;
PFNGLGENTEXTURESPROC glad_glGenTextures;
void GLAD_API_PTR glad_debug_impl_glGenTextures(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenTextures", (GLADapiproc) glGenTextures, 2, arg0, arg1);
    glGenTextures(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenTextures", (GLADapiproc) glGenTextures, 2, arg0, arg1);
    
}
PFNGLGENTEXTURESPROC glad_debug_glGenTextures = glad_debug_impl_glGenTextures;
PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv;
void GLAD_API_PTR glad_debug_impl_glGetTexParameterIuiv(GLenum arg0, GLenum arg1, GLuint * arg2) {
    _pre_call_gl_callback("glGetTexParameterIuiv", (GLADapiproc) glGetTexParameterIuiv, 3, arg0, arg1, arg2);
    glGetTexParameterIuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetTexParameterIuiv", (GLADapiproc) glGetTexParameterIuiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETTEXPARAMETERIUIVPROC glad_debug_glGetTexParameterIuiv = glad_debug_impl_glGetTexParameterIuiv;
PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nbv(GLuint arg0, const GLbyte * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Nbv", (GLADapiproc) glVertexAttrib4Nbv, 2, arg0, arg1);
    glVertexAttrib4Nbv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nbv", (GLADapiproc) glVertexAttrib4Nbv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NBVPROC glad_debug_glVertexAttrib4Nbv = glad_debug_impl_glVertexAttrib4Nbv;
PFNGLISSYNCPROC glad_glIsSync;
GLboolean GLAD_API_PTR glad_debug_impl_glIsSync(GLsync arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsSync", (GLADapiproc) glIsSync, 1, arg0);
    ret = glIsSync(arg0);
    _post_call_gl_callback((void*) &ret, "glIsSync", (GLADapiproc) glIsSync, 1, arg0);
    return ret;
}
PFNGLISSYNCPROC glad_debug_glIsSync = glad_debug_impl_glIsSync;
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;
void GLAD_API_PTR glad_debug_impl_glDeleteRenderbuffers(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteRenderbuffers", (GLADapiproc) glDeleteRenderbuffers, 2, arg0, arg1);
    glDeleteRenderbuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteRenderbuffers", (GLADapiproc) glDeleteRenderbuffers, 2, arg0, arg1);
    
}
PFNGLDELETERENDERBUFFERSPROC glad_debug_glDeleteRenderbuffers = glad_debug_impl_glDeleteRenderbuffers;
PFNGLUNIFORM2IPROC glad_glUniform2i;
void GLAD_API_PTR glad_debug_impl_glUniform2i(GLint arg0, GLint arg1, GLint arg2) {
    _pre_call_gl_callback("glUniform2i", (GLADapiproc) glUniform2i, 3, arg0, arg1, arg2);
    glUniform2i(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2i", (GLADapiproc) glUniform2i, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2IPROC glad_debug_glUniform2i = glad_debug_impl_glUniform2i;
PFNGLUNIFORM2FPROC glad_glUniform2f;
void GLAD_API_PTR glad_debug_impl_glUniform2f(GLint arg0, GLfloat arg1, GLfloat arg2) {
    _pre_call_gl_callback("glUniform2f", (GLADapiproc) glUniform2f, 3, arg0, arg1, arg2);
    glUniform2f(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2f", (GLADapiproc) glUniform2f, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2FPROC glad_debug_glUniform2f = glad_debug_impl_glUniform2f;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
void GLAD_API_PTR glad_debug_impl_glGetProgramiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetProgramiv", (GLADapiproc) glGetProgramiv, 3, arg0, arg1, arg2);
    glGetProgramiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetProgramiv", (GLADapiproc) glGetProgramiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETPROGRAMIVPROC glad_debug_glGetProgramiv = glad_debug_impl_glGetProgramiv;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
void GLAD_API_PTR glad_debug_impl_glVertexAttribPointer(GLuint arg0, GLint arg1, GLenum arg2, GLboolean arg3, GLsizei arg4, const void * arg5) {
    _pre_call_gl_callback("glVertexAttribPointer", (GLADapiproc) glVertexAttribPointer, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glVertexAttribPointer(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glVertexAttribPointer", (GLADapiproc) glVertexAttribPointer, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLVERTEXATTRIBPOINTERPROC glad_debug_glVertexAttribPointer = glad_debug_impl_glVertexAttribPointer;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer;
void GLAD_API_PTR glad_debug_impl_glFramebufferTextureLayer(GLenum arg0, GLenum arg1, GLuint arg2, GLint arg3, GLint arg4) {
    _pre_call_gl_callback("glFramebufferTextureLayer", (GLADapiproc) glFramebufferTextureLayer, 5, arg0, arg1, arg2, arg3, arg4);
    glFramebufferTextureLayer(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glFramebufferTextureLayer", (GLADapiproc) glFramebufferTextureLayer, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_debug_glFramebufferTextureLayer = glad_debug_impl_glFramebufferTextureLayer;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange;
void GLAD_API_PTR glad_debug_impl_glFlushMappedBufferRange(GLenum arg0, GLintptr arg1, GLsizeiptr arg2) {
    _pre_call_gl_callback("glFlushMappedBufferRange", (GLADapiproc) glFlushMappedBufferRange, 3, arg0, arg1, arg2);
    glFlushMappedBufferRange(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glFlushMappedBufferRange", (GLADapiproc) glFlushMappedBufferRange, 3, arg0, arg1, arg2);
    
}
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_debug_glFlushMappedBufferRange = glad_debug_impl_glFlushMappedBufferRange;
PFNGLGENQUERIESPROC glad_glGenQueries;
void GLAD_API_PTR glad_debug_impl_glGenQueries(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenQueries", (GLADapiproc) glGenQueries, 2, arg0, arg1);
    glGenQueries(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenQueries", (GLADapiproc) glGenQueries, 2, arg0, arg1);
    
}
PFNGLGENQUERIESPROC glad_debug_glGenQueries = glad_debug_impl_glGenQueries;
PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP1ui(GLuint arg0, GLenum arg1, GLboolean arg2, GLuint arg3) {
    _pre_call_gl_callback("glVertexAttribP1ui", (GLADapiproc) glVertexAttribP1ui, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP1ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP1ui", (GLADapiproc) glVertexAttribP1ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP1UIPROC glad_debug_glVertexAttribP1ui = glad_debug_impl_glVertexAttribP1ui;
PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D;
void GLAD_API_PTR glad_debug_impl_glTexSubImage3D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLsizei arg5, GLsizei arg6, GLsizei arg7, GLenum arg8, GLenum arg9, const void * arg10) {
    _pre_call_gl_callback("glTexSubImage3D", (GLADapiproc) glTexSubImage3D, 11, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    glTexSubImage3D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    _post_call_gl_callback(NULL, "glTexSubImage3D", (GLADapiproc) glTexSubImage3D, 11, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    
}
PFNGLTEXSUBIMAGE3DPROC glad_debug_glTexSubImage3D = glad_debug_impl_glTexSubImage3D;
PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v;
void GLAD_API_PTR glad_debug_impl_glGetInteger64i_v(GLenum arg0, GLuint arg1, GLint64 * arg2) {
    _pre_call_gl_callback("glGetInteger64i_v", (GLADapiproc) glGetInteger64i_v, 3, arg0, arg1, arg2);
    glGetInteger64i_v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetInteger64i_v", (GLADapiproc) glGetInteger64i_v, 3, arg0, arg1, arg2);
    
}
PFNGLGETINTEGER64I_VPROC glad_debug_glGetInteger64i_v = glad_debug_impl_glGetInteger64i_v;
PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers;
void GLAD_API_PTR glad_debug_impl_glDeleteSamplers(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteSamplers", (GLADapiproc) glDeleteSamplers, 2, arg0, arg1);
    glDeleteSamplers(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteSamplers", (GLADapiproc) glDeleteSamplers, 2, arg0, arg1);
    
}
PFNGLDELETESAMPLERSPROC glad_debug_glDeleteSamplers = glad_debug_impl_glDeleteSamplers;
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
void GLAD_API_PTR glad_debug_impl_glCopyTexImage2D(GLenum arg0, GLint arg1, GLenum arg2, GLint arg3, GLint arg4, GLsizei arg5, GLsizei arg6, GLint arg7) {
    _pre_call_gl_callback("glCopyTexImage2D", (GLADapiproc) glCopyTexImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    glCopyTexImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    _post_call_gl_callback(NULL, "glCopyTexImage2D", (GLADapiproc) glCopyTexImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    
}
PFNGLCOPYTEXIMAGE2DPROC glad_debug_glCopyTexImage2D = glad_debug_impl_glCopyTexImage2D;
PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer;
void GLAD_API_PTR glad_debug_impl_glBlitFramebuffer(GLint arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLint arg5, GLint arg6, GLint arg7, GLbitfield arg8, GLenum arg9) {
    _pre_call_gl_callback("glBlitFramebuffer", (GLADapiproc) glBlitFramebuffer, 10, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    glBlitFramebuffer(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    _post_call_gl_callback(NULL, "glBlitFramebuffer", (GLADapiproc) glBlitFramebuffer, 10, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    
}
PFNGLBLITFRAMEBUFFERPROC glad_debug_glBlitFramebuffer = glad_debug_impl_glBlitFramebuffer;
PFNGLISENABLEDIPROC glad_glIsEnabledi;
GLboolean GLAD_API_PTR glad_debug_impl_glIsEnabledi(GLenum arg0, GLuint arg1) {
    GLboolean ret;
    _pre_call_gl_callback("glIsEnabledi", (GLADapiproc) glIsEnabledi, 2, arg0, arg1);
    ret = glIsEnabledi(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glIsEnabledi", (GLADapiproc) glIsEnabledi, 2, arg0, arg1);
    return ret;
}
PFNGLISENABLEDIPROC glad_debug_glIsEnabledi = glad_debug_impl_glIsEnabledi;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed;
void GLAD_API_PTR glad_debug_impl_glBindFragDataLocationIndexed(GLuint arg0, GLuint arg1, GLuint arg2, const GLchar * arg3) {
    _pre_call_gl_callback("glBindFragDataLocationIndexed", (GLADapiproc) glBindFragDataLocationIndexed, 4, arg0, arg1, arg2, arg3);
    glBindFragDataLocationIndexed(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glBindFragDataLocationIndexed", (GLADapiproc) glBindFragDataLocationIndexed, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_debug_glBindFragDataLocationIndexed = glad_debug_impl_glBindFragDataLocationIndexed;
PFNGLUNIFORM2IVPROC glad_glUniform2iv;
void GLAD_API_PTR glad_debug_impl_glUniform2iv(GLint arg0, GLsizei arg1, const GLint * arg2) {
    _pre_call_gl_callback("glUniform2iv", (GLADapiproc) glUniform2iv, 3, arg0, arg1, arg2);
    glUniform2iv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2iv", (GLADapiproc) glUniform2iv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2IVPROC glad_debug_glUniform2iv = glad_debug_impl_glUniform2iv;
PFNGLUNIFORM4UIVPROC glad_glUniform4uiv;
void GLAD_API_PTR glad_debug_impl_glUniform4uiv(GLint arg0, GLsizei arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glUniform4uiv", (GLADapiproc) glUniform4uiv, 3, arg0, arg1, arg2);
    glUniform4uiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform4uiv", (GLADapiproc) glUniform4uiv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM4UIVPROC glad_debug_glUniform4uiv = glad_debug_impl_glUniform4uiv;
PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D;
void GLAD_API_PTR glad_debug_impl_glFramebufferTexture1D(GLenum arg0, GLenum arg1, GLenum arg2, GLuint arg3, GLint arg4) {
    _pre_call_gl_callback("glFramebufferTexture1D", (GLADapiproc) glFramebufferTexture1D, 5, arg0, arg1, arg2, arg3, arg4);
    glFramebufferTexture1D(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glFramebufferTexture1D", (GLADapiproc) glFramebufferTexture1D, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLFRAMEBUFFERTEXTURE1DPROC glad_debug_glFramebufferTexture1D = glad_debug_impl_glFramebufferTexture1D;
PFNGLGETSHADERIVPROC glad_glGetShaderiv;
void GLAD_API_PTR glad_debug_impl_glGetShaderiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetShaderiv", (GLADapiproc) glGetShaderiv, 3, arg0, arg1, arg2);
    glGetShaderiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetShaderiv", (GLADapiproc) glGetShaderiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETSHADERIVPROC glad_debug_glGetShaderiv = glad_debug_impl_glGetShaderiv;
PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation;
void GLAD_API_PTR glad_debug_impl_glBindFragDataLocation(GLuint arg0, GLuint arg1, const GLchar * arg2) {
    _pre_call_gl_callback("glBindFragDataLocation", (GLADapiproc) glBindFragDataLocation, 3, arg0, arg1, arg2);
    glBindFragDataLocation(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glBindFragDataLocation", (GLADapiproc) glBindFragDataLocation, 3, arg0, arg1, arg2);
    
}
PFNGLBINDFRAGDATALOCATIONPROC glad_debug_glBindFragDataLocation = glad_debug_impl_glBindFragDataLocation;
PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;
void GLAD_API_PTR glad_debug_impl_glGetUniformfv(GLuint arg0, GLint arg1, GLfloat * arg2) {
    _pre_call_gl_callback("glGetUniformfv", (GLADapiproc) glGetUniformfv, 3, arg0, arg1, arg2);
    glGetUniformfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetUniformfv", (GLADapiproc) glGetUniformfv, 3, arg0, arg1, arg2);
    
}
PFNGLGETUNIFORMFVPROC glad_debug_glGetUniformfv = glad_debug_impl_glGetUniformfv;
PFNGLGETDOUBLEVPROC glad_glGetDoublev;
void GLAD_API_PTR glad_debug_impl_glGetDoublev(GLenum arg0, GLdouble * arg1) {
    _pre_call_gl_callback("glGetDoublev", (GLADapiproc) glGetDoublev, 2, arg0, arg1);
    glGetDoublev(arg0, arg1);
    _post_call_gl_callback(NULL, "glGetDoublev", (GLADapiproc) glGetDoublev, 2, arg0, arg1);
    
}
PFNGLGETDOUBLEVPROC glad_debug_glGetDoublev = glad_debug_impl_glGetDoublev;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexImage2D(GLenum arg0, GLint arg1, GLenum arg2, GLsizei arg3, GLsizei arg4, GLint arg5, GLsizei arg6, const void * arg7) {
    _pre_call_gl_callback("glCompressedTexImage2D", (GLADapiproc) glCompressedTexImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    glCompressedTexImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    _post_call_gl_callback(NULL, "glCompressedTexImage2D", (GLADapiproc) glCompressedTexImage2D, 8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    
}
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_debug_glCompressedTexImage2D = glad_debug_impl_glCompressedTexImage2D;
PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1fv(GLuint arg0, const GLfloat * arg1) {
    _pre_call_gl_callback("glVertexAttrib1fv", (GLADapiproc) glVertexAttrib1fv, 2, arg0, arg1);
    glVertexAttrib1fv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1fv", (GLADapiproc) glVertexAttrib1fv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1FVPROC glad_debug_glVertexAttrib1fv = glad_debug_impl_glVertexAttrib1fv;
PFNGLUNIFORM3FVPROC glad_glUniform3fv;
void GLAD_API_PTR glad_debug_impl_glUniform3fv(GLint arg0, GLsizei arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glUniform3fv", (GLADapiproc) glUniform3fv, 3, arg0, arg1, arg2);
    glUniform3fv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform3fv", (GLADapiproc) glUniform3fv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM3FVPROC glad_debug_glUniform3fv = glad_debug_impl_glUniform3fv;
PFNGLDEPTHRANGEPROC glad_glDepthRange;
void GLAD_API_PTR glad_debug_impl_glDepthRange(GLdouble arg0, GLdouble arg1) {
    _pre_call_gl_callback("glDepthRange", (GLADapiproc) glDepthRange, 2, arg0, arg1);
    glDepthRange(arg0, arg1);
    _post_call_gl_callback(NULL, "glDepthRange", (GLADapiproc) glDepthRange, 2, arg0, arg1);
    
}
PFNGLDEPTHRANGEPROC glad_debug_glDepthRange = glad_debug_impl_glDepthRange;
PFNGLMAPBUFFERPROC glad_glMapBuffer;
void * GLAD_API_PTR glad_debug_impl_glMapBuffer(GLenum arg0, GLenum arg1) {
    void * ret;
    _pre_call_gl_callback("glMapBuffer", (GLADapiproc) glMapBuffer, 2, arg0, arg1);
    ret = glMapBuffer(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glMapBuffer", (GLADapiproc) glMapBuffer, 2, arg0, arg1);
    return ret;
}
PFNGLMAPBUFFERPROC glad_debug_glMapBuffer = glad_debug_impl_glMapBuffer;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexImage3D(GLenum arg0, GLint arg1, GLenum arg2, GLsizei arg3, GLsizei arg4, GLsizei arg5, GLint arg6, GLsizei arg7, const void * arg8) {
    _pre_call_gl_callback("glCompressedTexImage3D", (GLADapiproc) glCompressedTexImage3D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    glCompressedTexImage3D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    _post_call_gl_callback(NULL, "glCompressedTexImage3D", (GLADapiproc) glCompressedTexImage3D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    
}
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_debug_glCompressedTexImage3D = glad_debug_impl_glCompressedTexImage3D;
PFNGLDELETESYNCPROC glad_glDeleteSync;
void GLAD_API_PTR glad_debug_impl_glDeleteSync(GLsync arg0) {
    _pre_call_gl_callback("glDeleteSync", (GLADapiproc) glDeleteSync, 1, arg0);
    glDeleteSync(arg0);
    _post_call_gl_callback(NULL, "glDeleteSync", (GLADapiproc) glDeleteSync, 1, arg0);
    
}
PFNGLDELETESYNCPROC glad_debug_glDeleteSync = glad_debug_impl_glDeleteSync;
PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D;
void GLAD_API_PTR glad_debug_impl_glCopyTexSubImage3D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLint arg5, GLint arg6, GLsizei arg7, GLsizei arg8) {
    _pre_call_gl_callback("glCopyTexSubImage3D", (GLADapiproc) glCopyTexSubImage3D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    glCopyTexSubImage3D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    _post_call_gl_callback(NULL, "glCopyTexSubImage3D", (GLADapiproc) glCopyTexSubImage3D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    
}
PFNGLCOPYTEXSUBIMAGE3DPROC glad_debug_glCopyTexSubImage3D = glad_debug_impl_glCopyTexSubImage3D;
PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetVertexAttribiv", (GLADapiproc) glGetVertexAttribiv, 3, arg0, arg1, arg2);
    glGetVertexAttribiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribiv", (GLADapiproc) glGetVertexAttribiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBIVPROC glad_debug_glGetVertexAttribiv = glad_debug_impl_glGetVertexAttribiv;
PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements;
void GLAD_API_PTR glad_debug_impl_glMultiDrawElements(GLenum arg0, const GLsizei * arg1, GLenum arg2, const void *const* arg3, GLsizei arg4) {
    _pre_call_gl_callback("glMultiDrawElements", (GLADapiproc) glMultiDrawElements, 5, arg0, arg1, arg2, arg3, arg4);
    glMultiDrawElements(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glMultiDrawElements", (GLADapiproc) glMultiDrawElements, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLMULTIDRAWELEMENTSPROC glad_debug_glMultiDrawElements = glad_debug_impl_glMultiDrawElements;
PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3fv(GLuint arg0, const GLfloat * arg1) {
    _pre_call_gl_callback("glVertexAttrib3fv", (GLADapiproc) glVertexAttrib3fv, 2, arg0, arg1);
    glVertexAttrib3fv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib3fv", (GLADapiproc) glVertexAttrib3fv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB3FVPROC glad_debug_glVertexAttrib3fv = glad_debug_impl_glVertexAttrib3fv;
PFNGLUNIFORM3IVPROC glad_glUniform3iv;
void GLAD_API_PTR glad_debug_impl_glUniform3iv(GLint arg0, GLsizei arg1, const GLint * arg2) {
    _pre_call_gl_callback("glUniform3iv", (GLADapiproc) glUniform3iv, 3, arg0, arg1, arg2);
    glUniform3iv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform3iv", (GLADapiproc) glUniform3iv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM3IVPROC glad_debug_glUniform3iv = glad_debug_impl_glUniform3iv;
PFNGLPOLYGONMODEPROC glad_glPolygonMode;
void GLAD_API_PTR glad_debug_impl_glPolygonMode(GLenum arg0, GLenum arg1) {
    _pre_call_gl_callback("glPolygonMode", (GLADapiproc) glPolygonMode, 2, arg0, arg1);
    glPolygonMode(arg0, arg1);
    _post_call_gl_callback(NULL, "glPolygonMode", (GLADapiproc) glPolygonMode, 2, arg0, arg1);
    
}
PFNGLPOLYGONMODEPROC glad_debug_glPolygonMode = glad_debug_impl_glPolygonMode;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv;
void GLAD_API_PTR glad_debug_impl_glGetActiveUniformBlockiv(GLuint arg0, GLuint arg1, GLenum arg2, GLint * arg3) {
    _pre_call_gl_callback("glGetActiveUniformBlockiv", (GLADapiproc) glGetActiveUniformBlockiv, 4, arg0, arg1, arg2, arg3);
    glGetActiveUniformBlockiv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetActiveUniformBlockiv", (GLADapiproc) glGetActiveUniformBlockiv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_debug_glGetActiveUniformBlockiv = glad_debug_impl_glGetActiveUniformBlockiv;
PFNGLUSEPROGRAMPROC glad_glUseProgram;
void GLAD_API_PTR glad_debug_impl_glUseProgram(GLuint arg0) {
    _pre_call_gl_callback("glUseProgram", (GLADapiproc) glUseProgram, 1, arg0);
    glUseProgram(arg0);
    _post_call_gl_callback(NULL, "glUseProgram", (GLADapiproc) glUseProgram, 1, arg0);
    
}
PFNGLUSEPROGRAMPROC glad_debug_glUseProgram = glad_debug_impl_glUseProgram;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
void GLAD_API_PTR glad_debug_impl_glGetProgramInfoLog(GLuint arg0, GLsizei arg1, GLsizei * arg2, GLchar * arg3) {
    _pre_call_gl_callback("glGetProgramInfoLog", (GLADapiproc) glGetProgramInfoLog, 4, arg0, arg1, arg2, arg3);
    glGetProgramInfoLog(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetProgramInfoLog", (GLADapiproc) glGetProgramInfoLog, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETPROGRAMINFOLOGPROC glad_debug_glGetProgramInfoLog = glad_debug_impl_glGetProgramInfoLog;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
void GLAD_API_PTR glad_debug_impl_glBindVertexArray(GLuint arg0) {
    _pre_call_gl_callback("glBindVertexArray", (GLADapiproc) glBindVertexArray, 1, arg0);
    glBindVertexArray(arg0);
    _post_call_gl_callback(NULL, "glBindVertexArray", (GLADapiproc) glBindVertexArray, 1, arg0);
    
}
PFNGLBINDVERTEXARRAYPROC glad_debug_glBindVertexArray = glad_debug_impl_glBindVertexArray;
PFNGLGETINTEGER64VPROC glad_glGetInteger64v;
void GLAD_API_PTR glad_debug_impl_glGetInteger64v(GLenum arg0, GLint64 * arg1) {
    _pre_call_gl_callback("glGetInteger64v", (GLADapiproc) glGetInteger64v, 2, arg0, arg1);
    glGetInteger64v(arg0, arg1);
    _post_call_gl_callback(NULL, "glGetInteger64v", (GLADapiproc) glGetInteger64v, 2, arg0, arg1);
    
}
PFNGLGETINTEGER64VPROC glad_debug_glGetInteger64v = glad_debug_impl_glGetInteger64v;
PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv;
void GLAD_API_PTR glad_debug_impl_glSamplerParameterIiv(GLuint arg0, GLenum arg1, const GLint * arg2) {
    _pre_call_gl_callback("glSamplerParameterIiv", (GLADapiproc) glSamplerParameterIiv, 3, arg0, arg1, arg2);
    glSamplerParameterIiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameterIiv", (GLADapiproc) glSamplerParameterIiv, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERIIVPROC glad_debug_glSamplerParameterIiv = glad_debug_impl_glSamplerParameterIiv;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex;
void GLAD_API_PTR glad_debug_impl_glMultiDrawElementsBaseVertex(GLenum arg0, const GLsizei * arg1, GLenum arg2, const void *const* arg3, GLsizei arg4, const GLint * arg5) {
    _pre_call_gl_callback("glMultiDrawElementsBaseVertex", (GLADapiproc) glMultiDrawElementsBaseVertex, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glMultiDrawElementsBaseVertex(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glMultiDrawElementsBaseVertex", (GLADapiproc) glMultiDrawElementsBaseVertex, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_debug_glMultiDrawElementsBaseVertex = glad_debug_impl_glMultiDrawElementsBaseVertex;
PFNGLUNIFORM2UIVPROC glad_glUniform2uiv;
void GLAD_API_PTR glad_debug_impl_glUniform2uiv(GLint arg0, GLsizei arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glUniform2uiv", (GLADapiproc) glUniform2uiv, 3, arg0, arg1, arg2);
    glUniform2uiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2uiv", (GLADapiproc) glUniform2uiv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2UIVPROC glad_debug_glUniform2uiv = glad_debug_impl_glUniform2uiv;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexSubImage1D(GLenum arg0, GLint arg1, GLint arg2, GLsizei arg3, GLenum arg4, GLsizei arg5, const void * arg6) {
    _pre_call_gl_callback("glCompressedTexSubImage1D", (GLADapiproc) glCompressedTexSubImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glCompressedTexSubImage1D(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glCompressedTexSubImage1D", (GLADapiproc) glCompressedTexSubImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_debug_glCompressedTexSubImage1D = glad_debug_impl_glCompressedTexSubImage1D;
PFNGLFINISHPROC glad_glFinish;
void GLAD_API_PTR glad_debug_impl_glFinish(void) {
    _pre_call_gl_callback("glFinish", (GLADapiproc) glFinish, 0);
    glFinish();
    _post_call_gl_callback(NULL, "glFinish", (GLADapiproc) glFinish, 0);
    
}
PFNGLFINISHPROC glad_debug_glFinish = glad_debug_impl_glFinish;
PFNGLDELETESHADERPROC glad_glDeleteShader;
void GLAD_API_PTR glad_debug_impl_glDeleteShader(GLuint arg0) {
    _pre_call_gl_callback("glDeleteShader", (GLADapiproc) glDeleteShader, 1, arg0);
    glDeleteShader(arg0);
    _post_call_gl_callback(NULL, "glDeleteShader", (GLADapiproc) glDeleteShader, 1, arg0);
    
}
PFNGLDELETESHADERPROC glad_debug_glDeleteShader = glad_debug_impl_glDeleteShader;
PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nsv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Nsv", (GLADapiproc) glVertexAttrib4Nsv, 2, arg0, arg1);
    glVertexAttrib4Nsv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nsv", (GLADapiproc) glVertexAttrib4Nsv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NSVPROC glad_debug_glVertexAttrib4Nsv = glad_debug_impl_glVertexAttrib4Nsv;
PFNGLVIEWPORTPROC glad_glViewport;
void GLAD_API_PTR glad_debug_impl_glViewport(GLint arg0, GLint arg1, GLsizei arg2, GLsizei arg3) {
    _pre_call_gl_callback("glViewport", (GLADapiproc) glViewport, 4, arg0, arg1, arg2, arg3);
    glViewport(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glViewport", (GLADapiproc) glViewport, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVIEWPORTPROC glad_debug_glViewport = glad_debug_impl_glViewport;
PFNGLUNIFORM1UIVPROC glad_glUniform1uiv;
void GLAD_API_PTR glad_debug_impl_glUniform1uiv(GLint arg0, GLsizei arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glUniform1uiv", (GLADapiproc) glUniform1uiv, 3, arg0, arg1, arg2);
    glUniform1uiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform1uiv", (GLADapiproc) glUniform1uiv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM1UIVPROC glad_debug_glUniform1uiv = glad_debug_impl_glUniform1uiv;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings;
void GLAD_API_PTR glad_debug_impl_glTransformFeedbackVaryings(GLuint arg0, GLsizei arg1, const GLchar *const* arg2, GLenum arg3) {
    _pre_call_gl_callback("glTransformFeedbackVaryings", (GLADapiproc) glTransformFeedbackVaryings, 4, arg0, arg1, arg2, arg3);
    glTransformFeedbackVaryings(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glTransformFeedbackVaryings", (GLADapiproc) glTransformFeedbackVaryings, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_debug_glTransformFeedbackVaryings = glad_debug_impl_glTransformFeedbackVaryings;
PFNGLUNIFORM2UIPROC glad_glUniform2ui;
void GLAD_API_PTR glad_debug_impl_glUniform2ui(GLint arg0, GLuint arg1, GLuint arg2) {
    _pre_call_gl_callback("glUniform2ui", (GLADapiproc) glUniform2ui, 3, arg0, arg1, arg2);
    glUniform2ui(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2ui", (GLADapiproc) glUniform2ui, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2UIPROC glad_debug_glUniform2ui = glad_debug_impl_glUniform2ui;
PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI3i(GLuint arg0, GLint arg1, GLint arg2, GLint arg3) {
    _pre_call_gl_callback("glVertexAttribI3i", (GLADapiproc) glVertexAttribI3i, 4, arg0, arg1, arg2, arg3);
    glVertexAttribI3i(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribI3i", (GLADapiproc) glVertexAttribI3i, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBI3IPROC glad_debug_glVertexAttribI3i = glad_debug_impl_glVertexAttribI3i;
PFNGLCLEARDEPTHPROC glad_glClearDepth;
void GLAD_API_PTR glad_debug_impl_glClearDepth(GLdouble arg0) {
    _pre_call_gl_callback("glClearDepth", (GLADapiproc) glClearDepth, 1, arg0);
    glClearDepth(arg0);
    _post_call_gl_callback(NULL, "glClearDepth", (GLADapiproc) glClearDepth, 1, arg0);
    
}
PFNGLCLEARDEPTHPROC glad_debug_glClearDepth = glad_debug_impl_glClearDepth;
PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4usv(GLuint arg0, const GLushort * arg1) {
    _pre_call_gl_callback("glVertexAttribI4usv", (GLADapiproc) glVertexAttribI4usv, 2, arg0, arg1);
    glVertexAttribI4usv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4usv", (GLADapiproc) glVertexAttribI4usv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4USVPROC glad_debug_glVertexAttribI4usv = glad_debug_impl_glVertexAttribI4usv;
PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
void GLAD_API_PTR glad_debug_impl_glTexParameterf(GLenum arg0, GLenum arg1, GLfloat arg2) {
    _pre_call_gl_callback("glTexParameterf", (GLADapiproc) glTexParameterf, 3, arg0, arg1, arg2);
    glTexParameterf(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameterf", (GLADapiproc) glTexParameterf, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERFPROC glad_debug_glTexParameterf = glad_debug_impl_glTexParameterf;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
void GLAD_API_PTR glad_debug_impl_glTexParameteri(GLenum arg0, GLenum arg1, GLint arg2) {
    _pre_call_gl_callback("glTexParameteri", (GLADapiproc) glTexParameteri, 3, arg0, arg1, arg2);
    glTexParameteri(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameteri", (GLADapiproc) glTexParameteri, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERIPROC glad_debug_glTexParameteri = glad_debug_impl_glTexParameteri;
PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;
void GLAD_API_PTR glad_debug_impl_glGetShaderSource(GLuint arg0, GLsizei arg1, GLsizei * arg2, GLchar * arg3) {
    _pre_call_gl_callback("glGetShaderSource", (GLADapiproc) glGetShaderSource, 4, arg0, arg1, arg2, arg3);
    glGetShaderSource(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetShaderSource", (GLADapiproc) glGetShaderSource, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETSHADERSOURCEPROC glad_debug_glGetShaderSource = glad_debug_impl_glGetShaderSource;
PFNGLTEXBUFFERPROC glad_glTexBuffer;
void GLAD_API_PTR glad_debug_impl_glTexBuffer(GLenum arg0, GLenum arg1, GLuint arg2) {
    _pre_call_gl_callback("glTexBuffer", (GLADapiproc) glTexBuffer, 3, arg0, arg1, arg2);
    glTexBuffer(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexBuffer", (GLADapiproc) glTexBuffer, 3, arg0, arg1, arg2);
    
}
PFNGLTEXBUFFERPROC glad_debug_glTexBuffer = glad_debug_impl_glTexBuffer;
PFNGLPIXELSTOREIPROC glad_glPixelStorei;
void GLAD_API_PTR glad_debug_impl_glPixelStorei(GLenum arg0, GLint arg1) {
    _pre_call_gl_callback("glPixelStorei", (GLADapiproc) glPixelStorei, 2, arg0, arg1);
    glPixelStorei(arg0, arg1);
    _post_call_gl_callback(NULL, "glPixelStorei", (GLADapiproc) glPixelStorei, 2, arg0, arg1);
    
}
PFNGLPIXELSTOREIPROC glad_debug_glPixelStorei = glad_debug_impl_glPixelStorei;
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;
void GLAD_API_PTR glad_debug_impl_glValidateProgram(GLuint arg0) {
    _pre_call_gl_callback("glValidateProgram", (GLADapiproc) glValidateProgram, 1, arg0);
    glValidateProgram(arg0);
    _post_call_gl_callback(NULL, "glValidateProgram", (GLADapiproc) glValidateProgram, 1, arg0);
    
}
PFNGLVALIDATEPROGRAMPROC glad_debug_glValidateProgram = glad_debug_impl_glValidateProgram;
PFNGLPIXELSTOREFPROC glad_glPixelStoref;
void GLAD_API_PTR glad_debug_impl_glPixelStoref(GLenum arg0, GLfloat arg1) {
    _pre_call_gl_callback("glPixelStoref", (GLADapiproc) glPixelStoref, 2, arg0, arg1);
    glPixelStoref(arg0, arg1);
    _post_call_gl_callback(NULL, "glPixelStoref", (GLADapiproc) glPixelStoref, 2, arg0, arg1);
    
}
PFNGLPIXELSTOREFPROC glad_debug_glPixelStoref = glad_debug_impl_glPixelStoref;
PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v;
void GLAD_API_PTR glad_debug_impl_glGetBooleani_v(GLenum arg0, GLuint arg1, GLboolean * arg2) {
    _pre_call_gl_callback("glGetBooleani_v", (GLADapiproc) glGetBooleani_v, 3, arg0, arg1, arg2);
    glGetBooleani_v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetBooleani_v", (GLADapiproc) glGetBooleani_v, 3, arg0, arg1, arg2);
    
}
PFNGLGETBOOLEANI_VPROC glad_debug_glGetBooleani_v = glad_debug_impl_glGetBooleani_v;
PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP1uiv(GLuint arg0, GLenum arg1, GLboolean arg2, const GLuint * arg3) {
    _pre_call_gl_callback("glVertexAttribP1uiv", (GLADapiproc) glVertexAttribP1uiv, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP1uiv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP1uiv", (GLADapiproc) glVertexAttribP1uiv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP1UIVPROC glad_debug_glVertexAttribP1uiv = glad_debug_impl_glVertexAttribP1uiv;
PFNGLLINKPROGRAMPROC glad_glLinkProgram;
void GLAD_API_PTR glad_debug_impl_glLinkProgram(GLuint arg0) {
    _pre_call_gl_callback("glLinkProgram", (GLADapiproc) glLinkProgram, 1, arg0);
    glLinkProgram(arg0);
    _post_call_gl_callback(NULL, "glLinkProgram", (GLADapiproc) glLinkProgram, 1, arg0);
    
}
PFNGLLINKPROGRAMPROC glad_debug_glLinkProgram = glad_debug_impl_glLinkProgram;
PFNGLBINDTEXTUREPROC glad_glBindTexture;
void GLAD_API_PTR glad_debug_impl_glBindTexture(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glBindTexture", (GLADapiproc) glBindTexture, 2, arg0, arg1);
    glBindTexture(arg0, arg1);
    _post_call_gl_callback(NULL, "glBindTexture", (GLADapiproc) glBindTexture, 2, arg0, arg1);
    
}
PFNGLBINDTEXTUREPROC glad_debug_glBindTexture = glad_debug_impl_glBindTexture;
PFNGLGETSTRINGPROC glad_glGetString;
const GLubyte * GLAD_API_PTR glad_debug_impl_glGetString(GLenum arg0) {
    const GLubyte * ret;
    _pre_call_gl_callback("glGetString", (GLADapiproc) glGetString, 1, arg0);
    ret = glGetString(arg0);
    _post_call_gl_callback((void*) &ret, "glGetString", (GLADapiproc) glGetString, 1, arg0);
    return ret;
}
PFNGLGETSTRINGPROC glad_debug_glGetString = glad_debug_impl_glGetString;
PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP2uiv(GLuint arg0, GLenum arg1, GLboolean arg2, const GLuint * arg3) {
    _pre_call_gl_callback("glVertexAttribP2uiv", (GLADapiproc) glVertexAttribP2uiv, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP2uiv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP2uiv", (GLADapiproc) glVertexAttribP2uiv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP2UIVPROC glad_debug_glVertexAttribP2uiv = glad_debug_impl_glVertexAttribP2uiv;
PFNGLDETACHSHADERPROC glad_glDetachShader;
void GLAD_API_PTR glad_debug_impl_glDetachShader(GLuint arg0, GLuint arg1) {
    _pre_call_gl_callback("glDetachShader", (GLADapiproc) glDetachShader, 2, arg0, arg1);
    glDetachShader(arg0, arg1);
    _post_call_gl_callback(NULL, "glDetachShader", (GLADapiproc) glDetachShader, 2, arg0, arg1);
    
}
PFNGLDETACHSHADERPROC glad_debug_glDetachShader = glad_debug_impl_glDetachShader;
PFNGLENDQUERYPROC glad_glEndQuery;
void GLAD_API_PTR glad_debug_impl_glEndQuery(GLenum arg0) {
    _pre_call_gl_callback("glEndQuery", (GLADapiproc) glEndQuery, 1, arg0);
    glEndQuery(arg0);
    _post_call_gl_callback(NULL, "glEndQuery", (GLADapiproc) glEndQuery, 1, arg0);
    
}
PFNGLENDQUERYPROC glad_debug_glEndQuery = glad_debug_impl_glEndQuery;
PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI2ui(GLuint arg0, GLuint arg1, GLuint arg2) {
    _pre_call_gl_callback("glVertexAttribI2ui", (GLADapiproc) glVertexAttribI2ui, 3, arg0, arg1, arg2);
    glVertexAttribI2ui(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glVertexAttribI2ui", (GLADapiproc) glVertexAttribI2ui, 3, arg0, arg1, arg2);
    
}
PFNGLVERTEXATTRIBI2UIPROC glad_debug_glVertexAttribI2ui = glad_debug_impl_glVertexAttribI2ui;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
void GLAD_API_PTR glad_debug_impl_glDeleteTextures(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteTextures", (GLADapiproc) glDeleteTextures, 2, arg0, arg1);
    glDeleteTextures(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteTextures", (GLADapiproc) glDeleteTextures, 2, arg0, arg1);
    
}
PFNGLDELETETEXTURESPROC glad_debug_glDeleteTextures = glad_debug_impl_glDeleteTextures;
PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;
void GLAD_API_PTR glad_debug_impl_glStencilOpSeparate(GLenum arg0, GLenum arg1, GLenum arg2, GLenum arg3) {
    _pre_call_gl_callback("glStencilOpSeparate", (GLADapiproc) glStencilOpSeparate, 4, arg0, arg1, arg2, arg3);
    glStencilOpSeparate(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glStencilOpSeparate", (GLADapiproc) glStencilOpSeparate, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLSTENCILOPSEPARATEPROC glad_debug_glStencilOpSeparate = glad_debug_impl_glStencilOpSeparate;
PFNGLDELETEQUERIESPROC glad_glDeleteQueries;
void GLAD_API_PTR glad_debug_impl_glDeleteQueries(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteQueries", (GLADapiproc) glDeleteQueries, 2, arg0, arg1);
    glDeleteQueries(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteQueries", (GLADapiproc) glDeleteQueries, 2, arg0, arg1);
    
}
PFNGLDELETEQUERIESPROC glad_debug_glDeleteQueries = glad_debug_impl_glDeleteQueries;
PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4f(GLuint arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3, GLfloat arg4) {
    _pre_call_gl_callback("glVertexAttrib4f", (GLADapiproc) glVertexAttrib4f, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttrib4f(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttrib4f", (GLADapiproc) glVertexAttrib4f, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIB4FPROC glad_debug_glVertexAttrib4f = glad_debug_impl_glVertexAttrib4f;
PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4d(GLuint arg0, GLdouble arg1, GLdouble arg2, GLdouble arg3, GLdouble arg4) {
    _pre_call_gl_callback("glVertexAttrib4d", (GLADapiproc) glVertexAttrib4d, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttrib4d(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttrib4d", (GLADapiproc) glVertexAttrib4d, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIB4DPROC glad_debug_glVertexAttrib4d = glad_debug_impl_glVertexAttrib4d;
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetTexParameteriv(GLenum arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetTexParameteriv", (GLADapiproc) glGetTexParameteriv, 3, arg0, arg1, arg2);
    glGetTexParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetTexParameteriv", (GLADapiproc) glGetTexParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLGETTEXPARAMETERIVPROC glad_debug_glGetTexParameteriv = glad_debug_impl_glGetTexParameteriv;
PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4s(GLuint arg0, GLshort arg1, GLshort arg2, GLshort arg3, GLshort arg4) {
    _pre_call_gl_callback("glVertexAttrib4s", (GLADapiproc) glVertexAttrib4s, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttrib4s(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttrib4s", (GLADapiproc) glVertexAttrib4s, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIB4SPROC glad_debug_glVertexAttrib4s = glad_debug_impl_glVertexAttrib4s;
PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex;
void GLAD_API_PTR glad_debug_impl_glDrawElementsBaseVertex(GLenum arg0, GLsizei arg1, GLenum arg2, const void * arg3, GLint arg4) {
    _pre_call_gl_callback("glDrawElementsBaseVertex", (GLADapiproc) glDrawElementsBaseVertex, 5, arg0, arg1, arg2, arg3, arg4);
    glDrawElementsBaseVertex(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glDrawElementsBaseVertex", (GLADapiproc) glDrawElementsBaseVertex, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLDRAWELEMENTSBASEVERTEXPROC glad_debug_glDrawElementsBaseVertex = glad_debug_impl_glDrawElementsBaseVertex;
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
void GLAD_API_PTR glad_debug_impl_glSampleCoverage(GLfloat arg0, GLboolean arg1) {
    _pre_call_gl_callback("glSampleCoverage", (GLADapiproc) glSampleCoverage, 2, arg0, arg1);
    glSampleCoverage(arg0, arg1);
    _post_call_gl_callback(NULL, "glSampleCoverage", (GLADapiproc) glSampleCoverage, 2, arg0, arg1);
    
}
PFNGLSAMPLECOVERAGEPROC glad_debug_glSampleCoverage = glad_debug_impl_glSampleCoverage;
PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri;
void GLAD_API_PTR glad_debug_impl_glSamplerParameteri(GLuint arg0, GLenum arg1, GLint arg2) {
    _pre_call_gl_callback("glSamplerParameteri", (GLADapiproc) glSamplerParameteri, 3, arg0, arg1, arg2);
    glSamplerParameteri(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameteri", (GLADapiproc) glSamplerParameteri, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERIPROC glad_debug_glSamplerParameteri = glad_debug_impl_glSamplerParameteri;
PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf;
void GLAD_API_PTR glad_debug_impl_glSamplerParameterf(GLuint arg0, GLenum arg1, GLfloat arg2) {
    _pre_call_gl_callback("glSamplerParameterf", (GLADapiproc) glSamplerParameterf, 3, arg0, arg1, arg2);
    glSamplerParameterf(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameterf", (GLADapiproc) glSamplerParameterf, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERFPROC glad_debug_glSamplerParameterf = glad_debug_impl_glSamplerParameterf;
PFNGLUNIFORM1FPROC glad_glUniform1f;
void GLAD_API_PTR glad_debug_impl_glUniform1f(GLint arg0, GLfloat arg1) {
    _pre_call_gl_callback("glUniform1f", (GLADapiproc) glUniform1f, 2, arg0, arg1);
    glUniform1f(arg0, arg1);
    _post_call_gl_callback(NULL, "glUniform1f", (GLADapiproc) glUniform1f, 2, arg0, arg1);
    
}
PFNGLUNIFORM1FPROC glad_debug_glUniform1f = glad_debug_impl_glUniform1f;
PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribfv(GLuint arg0, GLenum arg1, GLfloat * arg2) {
    _pre_call_gl_callback("glGetVertexAttribfv", (GLADapiproc) glGetVertexAttribfv, 3, arg0, arg1, arg2);
    glGetVertexAttribfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribfv", (GLADapiproc) glGetVertexAttribfv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBFVPROC glad_debug_glGetVertexAttribfv = glad_debug_impl_glGetVertexAttribfv;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage;
void GLAD_API_PTR glad_debug_impl_glGetCompressedTexImage(GLenum arg0, GLint arg1, void * arg2) {
    _pre_call_gl_callback("glGetCompressedTexImage", (GLADapiproc) glGetCompressedTexImage, 3, arg0, arg1, arg2);
    glGetCompressedTexImage(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetCompressedTexImage", (GLADapiproc) glGetCompressedTexImage, 3, arg0, arg1, arg2);
    
}
PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_debug_glGetCompressedTexImage = glad_debug_impl_glGetCompressedTexImage;
PFNGLUNIFORM1IPROC glad_glUniform1i;
void GLAD_API_PTR glad_debug_impl_glUniform1i(GLint arg0, GLint arg1) {
    _pre_call_gl_callback("glUniform1i", (GLADapiproc) glUniform1i, 2, arg0, arg1);
    glUniform1i(arg0, arg1);
    _post_call_gl_callback(NULL, "glUniform1i", (GLADapiproc) glUniform1i, 2, arg0, arg1);
    
}
PFNGLUNIFORM1IPROC glad_debug_glUniform1i = glad_debug_impl_glUniform1i;
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
void GLAD_API_PTR glad_debug_impl_glGetActiveAttrib(GLuint arg0, GLuint arg1, GLsizei arg2, GLsizei * arg3, GLint * arg4, GLenum * arg5, GLchar * arg6) {
    _pre_call_gl_callback("glGetActiveAttrib", (GLADapiproc) glGetActiveAttrib, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glGetActiveAttrib(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glGetActiveAttrib", (GLADapiproc) glGetActiveAttrib, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLGETACTIVEATTRIBPROC glad_debug_glGetActiveAttrib = glad_debug_impl_glGetActiveAttrib;
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
void GLAD_API_PTR glad_debug_impl_glTexSubImage2D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLsizei arg4, GLsizei arg5, GLenum arg6, GLenum arg7, const void * arg8) {
    _pre_call_gl_callback("glTexSubImage2D", (GLADapiproc) glTexSubImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    glTexSubImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    _post_call_gl_callback(NULL, "glTexSubImage2D", (GLADapiproc) glTexSubImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    
}
PFNGLTEXSUBIMAGE2DPROC glad_debug_glTexSubImage2D = glad_debug_impl_glTexSubImage2D;
PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;
void GLAD_API_PTR glad_debug_impl_glGetUniformiv(GLuint arg0, GLint arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetUniformiv", (GLADapiproc) glGetUniformiv, 3, arg0, arg1, arg2);
    glGetUniformiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetUniformiv", (GLADapiproc) glGetUniformiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETUNIFORMIVPROC glad_debug_glGetUniformiv = glad_debug_impl_glGetUniformiv;
PFNGLLOGICOPPROC glad_glLogicOp;
void GLAD_API_PTR glad_debug_impl_glLogicOp(GLenum arg0) {
    _pre_call_gl_callback("glLogicOp", (GLADapiproc) glLogicOp, 1, arg0);
    glLogicOp(arg0);
    _post_call_gl_callback(NULL, "glLogicOp", (GLADapiproc) glLogicOp, 1, arg0);
    
}
PFNGLLOGICOPPROC glad_debug_glLogicOp = glad_debug_impl_glLogicOp;
PFNGLUNIFORM4UIPROC glad_glUniform4ui;
void GLAD_API_PTR glad_debug_impl_glUniform4ui(GLint arg0, GLuint arg1, GLuint arg2, GLuint arg3, GLuint arg4) {
    _pre_call_gl_callback("glUniform4ui", (GLADapiproc) glUniform4ui, 5, arg0, arg1, arg2, arg3, arg4);
    glUniform4ui(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glUniform4ui", (GLADapiproc) glUniform4ui, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLUNIFORM4UIPROC glad_debug_glUniform4ui = glad_debug_impl_glUniform4ui;
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
void GLAD_API_PTR glad_debug_impl_glBindFramebuffer(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glBindFramebuffer", (GLADapiproc) glBindFramebuffer, 2, arg0, arg1);
    glBindFramebuffer(arg0, arg1);
    _post_call_gl_callback(NULL, "glBindFramebuffer", (GLADapiproc) glBindFramebuffer, 2, arg0, arg1);
    
}
PFNGLBINDFRAMEBUFFERPROC glad_debug_glBindFramebuffer = glad_debug_impl_glBindFramebuffer;
PFNGLCULLFACEPROC glad_glCullFace;
void GLAD_API_PTR glad_debug_impl_glCullFace(GLenum arg0) {
    _pre_call_gl_callback("glCullFace", (GLADapiproc) glCullFace, 1, arg0);
    glCullFace(arg0);
    _post_call_gl_callback(NULL, "glCullFace", (GLADapiproc) glCullFace, 1, arg0);
    
}
PFNGLCULLFACEPROC glad_debug_glCullFace = glad_debug_impl_glCullFace;
PFNGLGETSTRINGIPROC glad_glGetStringi;
const GLubyte * GLAD_API_PTR glad_debug_impl_glGetStringi(GLenum arg0, GLuint arg1) {
    const GLubyte * ret;
    _pre_call_gl_callback("glGetStringi", (GLADapiproc) glGetStringi, 2, arg0, arg1);
    ret = glGetStringi(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetStringi", (GLADapiproc) glGetStringi, 2, arg0, arg1);
    return ret;
}
PFNGLGETSTRINGIPROC glad_debug_glGetStringi = glad_debug_impl_glGetStringi;
PFNGLATTACHSHADERPROC glad_glAttachShader;
void GLAD_API_PTR glad_debug_impl_glAttachShader(GLuint arg0, GLuint arg1) {
    _pre_call_gl_callback("glAttachShader", (GLADapiproc) glAttachShader, 2, arg0, arg1);
    glAttachShader(arg0, arg1);
    _post_call_gl_callback(NULL, "glAttachShader", (GLADapiproc) glAttachShader, 2, arg0, arg1);
    
}
PFNGLATTACHSHADERPROC glad_debug_glAttachShader = glad_debug_impl_glAttachShader;
PFNGLQUERYCOUNTERPROC glad_glQueryCounter;
void GLAD_API_PTR glad_debug_impl_glQueryCounter(GLuint arg0, GLenum arg1) {
    _pre_call_gl_callback("glQueryCounter", (GLADapiproc) glQueryCounter, 2, arg0, arg1);
    glQueryCounter(arg0, arg1);
    _post_call_gl_callback(NULL, "glQueryCounter", (GLADapiproc) glQueryCounter, 2, arg0, arg1);
    
}
PFNGLQUERYCOUNTERPROC glad_debug_glQueryCounter = glad_debug_impl_glQueryCounter;
PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex;
void GLAD_API_PTR glad_debug_impl_glProvokingVertex(GLenum arg0) {
    _pre_call_gl_callback("glProvokingVertex", (GLADapiproc) glProvokingVertex, 1, arg0);
    glProvokingVertex(arg0);
    _post_call_gl_callback(NULL, "glProvokingVertex", (GLADapiproc) glProvokingVertex, 1, arg0);
    
}
PFNGLPROVOKINGVERTEXPROC glad_debug_glProvokingVertex = glad_debug_impl_glProvokingVertex;
PFNGLDRAWELEMENTSPROC glad_glDrawElements;
void GLAD_API_PTR glad_debug_impl_glDrawElements(GLenum arg0, GLsizei arg1, GLenum arg2, const void * arg3) {
    _pre_call_gl_callback("glDrawElements", (GLADapiproc) glDrawElements, 4, arg0, arg1, arg2, arg3);
    glDrawElements(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glDrawElements", (GLADapiproc) glDrawElements, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLDRAWELEMENTSPROC glad_debug_glDrawElements = glad_debug_impl_glDrawElements;
PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4sv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttribI4sv", (GLADapiproc) glVertexAttribI4sv, 2, arg0, arg1);
    glVertexAttribI4sv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4sv", (GLADapiproc) glVertexAttribI4sv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4SVPROC glad_debug_glVertexAttribI4sv = glad_debug_impl_glVertexAttribI4sv;
PFNGLUNIFORM1IVPROC glad_glUniform1iv;
void GLAD_API_PTR glad_debug_impl_glUniform1iv(GLint arg0, GLsizei arg1, const GLint * arg2) {
    _pre_call_gl_callback("glUniform1iv", (GLADapiproc) glUniform1iv, 3, arg0, arg1, arg2);
    glUniform1iv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform1iv", (GLADapiproc) glUniform1iv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM1IVPROC glad_debug_glUniform1iv = glad_debug_impl_glUniform1iv;
PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv;
void GLAD_API_PTR glad_debug_impl_glGetQueryObjectiv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetQueryObjectiv", (GLADapiproc) glGetQueryObjectiv, 3, arg0, arg1, arg2);
    glGetQueryObjectiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetQueryObjectiv", (GLADapiproc) glGetQueryObjectiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETQUERYOBJECTIVPROC glad_debug_glGetQueryObjectiv = glad_debug_impl_glGetQueryObjectiv;
PFNGLREADBUFFERPROC glad_glReadBuffer;
void GLAD_API_PTR glad_debug_impl_glReadBuffer(GLenum arg0) {
    _pre_call_gl_callback("glReadBuffer", (GLADapiproc) glReadBuffer, 1, arg0);
    glReadBuffer(arg0);
    _post_call_gl_callback(NULL, "glReadBuffer", (GLADapiproc) glReadBuffer, 1, arg0);
    
}
PFNGLREADBUFFERPROC glad_debug_glReadBuffer = glad_debug_impl_glReadBuffer;
PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv;
void GLAD_API_PTR glad_debug_impl_glTexParameterIuiv(GLenum arg0, GLenum arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glTexParameterIuiv", (GLADapiproc) glTexParameterIuiv, 3, arg0, arg1, arg2);
    glTexParameterIuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameterIuiv", (GLADapiproc) glTexParameterIuiv, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERIUIVPROC glad_debug_glTexParameterIuiv = glad_debug_impl_glTexParameterIuiv;
PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced;
void GLAD_API_PTR glad_debug_impl_glDrawArraysInstanced(GLenum arg0, GLint arg1, GLsizei arg2, GLsizei arg3) {
    _pre_call_gl_callback("glDrawArraysInstanced", (GLADapiproc) glDrawArraysInstanced, 4, arg0, arg1, arg2, arg3);
    glDrawArraysInstanced(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glDrawArraysInstanced", (GLADapiproc) glDrawArraysInstanced, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLDRAWARRAYSINSTANCEDPROC glad_debug_glDrawArraysInstanced = glad_debug_impl_glDrawArraysInstanced;
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
void GLAD_API_PTR glad_debug_impl_glGenerateMipmap(GLenum arg0) {
    _pre_call_gl_callback("glGenerateMipmap", (GLADapiproc) glGenerateMipmap, 1, arg0);
    glGenerateMipmap(arg0);
    _post_call_gl_callback(NULL, "glGenerateMipmap", (GLADapiproc) glGenerateMipmap, 1, arg0);
    
}
PFNGLGENERATEMIPMAPPROC glad_debug_glGenerateMipmap = glad_debug_impl_glGenerateMipmap;
PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv;
void GLAD_API_PTR glad_debug_impl_glSamplerParameteriv(GLuint arg0, GLenum arg1, const GLint * arg2) {
    _pre_call_gl_callback("glSamplerParameteriv", (GLADapiproc) glSamplerParameteriv, 3, arg0, arg1, arg2);
    glSamplerParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameteriv", (GLADapiproc) glSamplerParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERIVPROC glad_debug_glSamplerParameteriv = glad_debug_impl_glSamplerParameteriv;
PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3f(GLuint arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3) {
    _pre_call_gl_callback("glVertexAttrib3f", (GLADapiproc) glVertexAttrib3f, 4, arg0, arg1, arg2, arg3);
    glVertexAttrib3f(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttrib3f", (GLADapiproc) glVertexAttrib3f, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIB3FPROC glad_debug_glVertexAttrib3f = glad_debug_impl_glVertexAttrib3f;
PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4uiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttrib4uiv", (GLADapiproc) glVertexAttrib4uiv, 2, arg0, arg1);
    glVertexAttrib4uiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4uiv", (GLADapiproc) glVertexAttrib4uiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4UIVPROC glad_debug_glVertexAttrib4uiv = glad_debug_impl_glVertexAttrib4uiv;
PFNGLPOINTPARAMETERIPROC glad_glPointParameteri;
void GLAD_API_PTR glad_debug_impl_glPointParameteri(GLenum arg0, GLint arg1) {
    _pre_call_gl_callback("glPointParameteri", (GLADapiproc) glPointParameteri, 2, arg0, arg1);
    glPointParameteri(arg0, arg1);
    _post_call_gl_callback(NULL, "glPointParameteri", (GLADapiproc) glPointParameteri, 2, arg0, arg1);
    
}
PFNGLPOINTPARAMETERIPROC glad_debug_glPointParameteri = glad_debug_impl_glPointParameteri;
PFNGLBLENDCOLORPROC glad_glBlendColor;
void GLAD_API_PTR glad_debug_impl_glBlendColor(GLfloat arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3) {
    _pre_call_gl_callback("glBlendColor", (GLADapiproc) glBlendColor, 4, arg0, arg1, arg2, arg3);
    glBlendColor(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glBlendColor", (GLADapiproc) glBlendColor, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLBLENDCOLORPROC glad_debug_glBlendColor = glad_debug_impl_glBlendColor;
PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv;
void GLAD_API_PTR glad_debug_impl_glSamplerParameterIuiv(GLuint arg0, GLenum arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glSamplerParameterIuiv", (GLADapiproc) glSamplerParameterIuiv, 3, arg0, arg1, arg2);
    glSamplerParameterIuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameterIuiv", (GLADapiproc) glSamplerParameterIuiv, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERIUIVPROC glad_debug_glSamplerParameterIuiv = glad_debug_impl_glSamplerParameterIuiv;
PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer;
GLboolean GLAD_API_PTR glad_debug_impl_glUnmapBuffer(GLenum arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glUnmapBuffer", (GLADapiproc) glUnmapBuffer, 1, arg0);
    ret = glUnmapBuffer(arg0);
    _post_call_gl_callback((void*) &ret, "glUnmapBuffer", (GLADapiproc) glUnmapBuffer, 1, arg0);
    return ret;
}
PFNGLUNMAPBUFFERPROC glad_debug_glUnmapBuffer = glad_debug_impl_glUnmapBuffer;
PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;
void GLAD_API_PTR glad_debug_impl_glPointParameterf(GLenum arg0, GLfloat arg1) {
    _pre_call_gl_callback("glPointParameterf", (GLADapiproc) glPointParameterf, 2, arg0, arg1);
    glPointParameterf(arg0, arg1);
    _post_call_gl_callback(NULL, "glPointParameterf", (GLADapiproc) glPointParameterf, 2, arg0, arg1);
    
}
PFNGLPOINTPARAMETERFPROC glad_debug_glPointParameterf = glad_debug_impl_glPointParameterf;
PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3s(GLuint arg0, GLshort arg1, GLshort arg2, GLshort arg3) {
    _pre_call_gl_callback("glVertexAttrib3s", (GLADapiproc) glVertexAttrib3s, 4, arg0, arg1, arg2, arg3);
    glVertexAttrib3s(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttrib3s", (GLADapiproc) glVertexAttrib3s, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIB3SPROC glad_debug_glVertexAttrib3s = glad_debug_impl_glVertexAttrib3s;
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
void GLAD_API_PTR glad_debug_impl_glBindRenderbuffer(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glBindRenderbuffer", (GLADapiproc) glBindRenderbuffer, 2, arg0, arg1);
    glBindRenderbuffer(arg0, arg1);
    _post_call_gl_callback(NULL, "glBindRenderbuffer", (GLADapiproc) glBindRenderbuffer, 2, arg0, arg1);
    
}
PFNGLBINDRENDERBUFFERPROC glad_debug_glBindRenderbuffer = glad_debug_impl_glBindRenderbuffer;
PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP4uiv(GLuint arg0, GLenum arg1, GLboolean arg2, const GLuint * arg3) {
    _pre_call_gl_callback("glVertexAttribP4uiv", (GLADapiproc) glVertexAttribP4uiv, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP4uiv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP4uiv", (GLADapiproc) glVertexAttribP4uiv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP4UIVPROC glad_debug_glVertexAttribP4uiv = glad_debug_impl_glVertexAttribP4uiv;
PFNGLISPROGRAMPROC glad_glIsProgram;
GLboolean GLAD_API_PTR glad_debug_impl_glIsProgram(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsProgram", (GLADapiproc) glIsProgram, 1, arg0);
    ret = glIsProgram(arg0);
    _post_call_gl_callback((void*) &ret, "glIsProgram", (GLADapiproc) glIsProgram, 1, arg0);
    return ret;
}
PFNGLISPROGRAMPROC glad_debug_glIsProgram = glad_debug_impl_glIsProgram;
PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4bv(GLuint arg0, const GLbyte * arg1) {
    _pre_call_gl_callback("glVertexAttrib4bv", (GLADapiproc) glVertexAttrib4bv, 2, arg0, arg1);
    glVertexAttrib4bv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4bv", (GLADapiproc) glVertexAttrib4bv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4BVPROC glad_debug_glVertexAttrib4bv = glad_debug_impl_glVertexAttrib4bv;
PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4fv(GLuint arg0, const GLfloat * arg1) {
    _pre_call_gl_callback("glVertexAttrib4fv", (GLADapiproc) glVertexAttrib4fv, 2, arg0, arg1);
    glVertexAttrib4fv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4fv", (GLADapiproc) glVertexAttrib4fv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4FVPROC glad_debug_glVertexAttrib4fv = glad_debug_impl_glVertexAttrib4fv;
PFNGLUNIFORM4IPROC glad_glUniform4i;
void GLAD_API_PTR glad_debug_impl_glUniform4i(GLint arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4) {
    _pre_call_gl_callback("glUniform4i", (GLADapiproc) glUniform4i, 5, arg0, arg1, arg2, arg3, arg4);
    glUniform4i(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glUniform4i", (GLADapiproc) glUniform4i, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLUNIFORM4IPROC glad_debug_glUniform4i = glad_debug_impl_glUniform4i;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
void GLAD_API_PTR glad_debug_impl_glActiveTexture(GLenum arg0) {
    _pre_call_gl_callback("glActiveTexture", (GLADapiproc) glActiveTexture, 1, arg0);
    glActiveTexture(arg0);
    _post_call_gl_callback(NULL, "glActiveTexture", (GLADapiproc) glActiveTexture, 1, arg0);
    
}
PFNGLACTIVETEXTUREPROC glad_debug_glActiveTexture = glad_debug_impl_glActiveTexture;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
void GLAD_API_PTR glad_debug_impl_glEnableVertexAttribArray(GLuint arg0) {
    _pre_call_gl_callback("glEnableVertexAttribArray", (GLADapiproc) glEnableVertexAttribArray, 1, arg0);
    glEnableVertexAttribArray(arg0);
    _post_call_gl_callback(NULL, "glEnableVertexAttribArray", (GLADapiproc) glEnableVertexAttribArray, 1, arg0);
    
}
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_debug_glEnableVertexAttribArray = glad_debug_impl_glEnableVertexAttribArray;
PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2fv(GLuint arg0, const GLfloat * arg1) {
    _pre_call_gl_callback("glVertexAttrib2fv", (GLADapiproc) glVertexAttrib2fv, 2, arg0, arg1);
    glVertexAttrib2fv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib2fv", (GLADapiproc) glVertexAttrib2fv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB2FVPROC glad_debug_glVertexAttrib2fv = glad_debug_impl_glVertexAttrib2fv;
PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI3iv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttribI3iv", (GLADapiproc) glVertexAttribI3iv, 2, arg0, arg1);
    glVertexAttribI3iv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI3iv", (GLADapiproc) glVertexAttribI3iv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI3IVPROC glad_debug_glVertexAttribI3iv = glad_debug_impl_glVertexAttribI3iv;
PFNGLUNIFORM4FPROC glad_glUniform4f;
void GLAD_API_PTR glad_debug_impl_glUniform4f(GLint arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3, GLfloat arg4) {
    _pre_call_gl_callback("glUniform4f", (GLADapiproc) glUniform4f, 5, arg0, arg1, arg2, arg3, arg4);
    glUniform4f(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glUniform4f", (GLADapiproc) glUniform4f, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLUNIFORM4FPROC glad_debug_glUniform4f = glad_debug_impl_glUniform4f;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample;
void GLAD_API_PTR glad_debug_impl_glRenderbufferStorageMultisample(GLenum arg0, GLsizei arg1, GLenum arg2, GLsizei arg3, GLsizei arg4) {
    _pre_call_gl_callback("glRenderbufferStorageMultisample", (GLADapiproc) glRenderbufferStorageMultisample, 5, arg0, arg1, arg2, arg3, arg4);
    glRenderbufferStorageMultisample(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glRenderbufferStorageMultisample", (GLADapiproc) glRenderbufferStorageMultisample, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_debug_glRenderbufferStorageMultisample = glad_debug_impl_glRenderbufferStorageMultisample;
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix3fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix3fv", (GLADapiproc) glUniformMatrix3fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix3fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix3fv", (GLADapiproc) glUniformMatrix3fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX3FVPROC glad_debug_glUniformMatrix3fv = glad_debug_impl_glUniformMatrix3fv;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex;
void GLAD_API_PTR glad_debug_impl_glDrawElementsInstancedBaseVertex(GLenum arg0, GLsizei arg1, GLenum arg2, const void * arg3, GLsizei arg4, GLint arg5) {
    _pre_call_gl_callback("glDrawElementsInstancedBaseVertex", (GLADapiproc) glDrawElementsInstancedBaseVertex, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glDrawElementsInstancedBaseVertex(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glDrawElementsInstancedBaseVertex", (GLADapiproc) glDrawElementsInstancedBaseVertex, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_debug_glDrawElementsInstancedBaseVertex = glad_debug_impl_glDrawElementsInstancedBaseVertex;
PFNGLSTENCILFUNCPROC glad_glStencilFunc;
void GLAD_API_PTR glad_debug_impl_glStencilFunc(GLenum arg0, GLint arg1, GLuint arg2) {
    _pre_call_gl_callback("glStencilFunc", (GLADapiproc) glStencilFunc, 3, arg0, arg1, arg2);
    glStencilFunc(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glStencilFunc", (GLADapiproc) glStencilFunc, 3, arg0, arg1, arg2);
    
}
PFNGLSTENCILFUNCPROC glad_debug_glStencilFunc = glad_debug_impl_glStencilFunc;
PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding;
void GLAD_API_PTR glad_debug_impl_glUniformBlockBinding(GLuint arg0, GLuint arg1, GLuint arg2) {
    _pre_call_gl_callback("glUniformBlockBinding", (GLADapiproc) glUniformBlockBinding, 3, arg0, arg1, arg2);
    glUniformBlockBinding(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniformBlockBinding", (GLADapiproc) glUniformBlockBinding, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORMBLOCKBINDINGPROC glad_debug_glUniformBlockBinding = glad_debug_impl_glUniformBlockBinding;
PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4iv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttribI4iv", (GLADapiproc) glVertexAttribI4iv, 2, arg0, arg1);
    glVertexAttribI4iv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4iv", (GLADapiproc) glVertexAttribI4iv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4IVPROC glad_debug_glVertexAttribI4iv = glad_debug_impl_glVertexAttribI4iv;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
void GLAD_API_PTR glad_debug_impl_glGetShaderInfoLog(GLuint arg0, GLsizei arg1, GLsizei * arg2, GLchar * arg3) {
    _pre_call_gl_callback("glGetShaderInfoLog", (GLADapiproc) glGetShaderInfoLog, 4, arg0, arg1, arg2, arg3);
    glGetShaderInfoLog(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetShaderInfoLog", (GLADapiproc) glGetShaderInfoLog, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETSHADERINFOLOGPROC glad_debug_glGetShaderInfoLog = glad_debug_impl_glGetShaderInfoLog;
PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4i(GLuint arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4) {
    _pre_call_gl_callback("glVertexAttribI4i", (GLADapiproc) glVertexAttribI4i, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttribI4i(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttribI4i", (GLADapiproc) glVertexAttribI4i, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIBI4IPROC glad_debug_glVertexAttribI4i = glad_debug_impl_glVertexAttribI4i;
PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData;
void GLAD_API_PTR glad_debug_impl_glGetBufferSubData(GLenum arg0, GLintptr arg1, GLsizeiptr arg2, void * arg3) {
    _pre_call_gl_callback("glGetBufferSubData", (GLADapiproc) glGetBufferSubData, 4, arg0, arg1, arg2, arg3);
    glGetBufferSubData(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetBufferSubData", (GLADapiproc) glGetBufferSubData, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETBUFFERSUBDATAPROC glad_debug_glGetBufferSubData = glad_debug_impl_glGetBufferSubData;
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
void GLAD_API_PTR glad_debug_impl_glBlendEquationSeparate(GLenum arg0, GLenum arg1) {
    _pre_call_gl_callback("glBlendEquationSeparate", (GLADapiproc) glBlendEquationSeparate, 2, arg0, arg1);
    glBlendEquationSeparate(arg0, arg1);
    _post_call_gl_callback(NULL, "glBlendEquationSeparate", (GLADapiproc) glBlendEquationSeparate, 2, arg0, arg1);
    
}
PFNGLBLENDEQUATIONSEPARATEPROC glad_debug_glBlendEquationSeparate = glad_debug_impl_glBlendEquationSeparate;
PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI1ui(GLuint arg0, GLuint arg1) {
    _pre_call_gl_callback("glVertexAttribI1ui", (GLADapiproc) glVertexAttribI1ui, 2, arg0, arg1);
    glVertexAttribI1ui(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI1ui", (GLADapiproc) glVertexAttribI1ui, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI1UIPROC glad_debug_glVertexAttribI1ui = glad_debug_impl_glVertexAttribI1ui;
PFNGLGENBUFFERSPROC glad_glGenBuffers;
void GLAD_API_PTR glad_debug_impl_glGenBuffers(GLsizei arg0, GLuint * arg1) {
    _pre_call_gl_callback("glGenBuffers", (GLADapiproc) glGenBuffers, 2, arg0, arg1);
    glGenBuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glGenBuffers", (GLADapiproc) glGenBuffers, 2, arg0, arg1);
    
}
PFNGLGENBUFFERSPROC glad_debug_glGenBuffers = glad_debug_impl_glGenBuffers;
PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2sv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttrib2sv", (GLADapiproc) glVertexAttrib2sv, 2, arg0, arg1);
    glVertexAttrib2sv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib2sv", (GLADapiproc) glVertexAttrib2sv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB2SVPROC glad_debug_glVertexAttrib2sv = glad_debug_impl_glVertexAttrib2sv;
PFNGLBLENDFUNCPROC glad_glBlendFunc;
void GLAD_API_PTR glad_debug_impl_glBlendFunc(GLenum arg0, GLenum arg1) {
    _pre_call_gl_callback("glBlendFunc", (GLADapiproc) glBlendFunc, 2, arg0, arg1);
    glBlendFunc(arg0, arg1);
    _post_call_gl_callback(NULL, "glBlendFunc", (GLADapiproc) glBlendFunc, 2, arg0, arg1);
    
}
PFNGLBLENDFUNCPROC glad_debug_glBlendFunc = glad_debug_impl_glBlendFunc;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
GLuint GLAD_API_PTR glad_debug_impl_glCreateProgram(void) {
    GLuint ret;
    _pre_call_gl_callback("glCreateProgram", (GLADapiproc) glCreateProgram, 0);
    ret = glCreateProgram();
    _post_call_gl_callback((void*) &ret, "glCreateProgram", (GLADapiproc) glCreateProgram, 0);
    return ret;
}
PFNGLCREATEPROGRAMPROC glad_debug_glCreateProgram = glad_debug_impl_glCreateProgram;
PFNGLTEXIMAGE3DPROC glad_glTexImage3D;
void GLAD_API_PTR glad_debug_impl_glTexImage3D(GLenum arg0, GLint arg1, GLint arg2, GLsizei arg3, GLsizei arg4, GLsizei arg5, GLint arg6, GLenum arg7, GLenum arg8, const void * arg9) {
    _pre_call_gl_callback("glTexImage3D", (GLADapiproc) glTexImage3D, 10, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    glTexImage3D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    _post_call_gl_callback(NULL, "glTexImage3D", (GLADapiproc) glTexImage3D, 10, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    
}
PFNGLTEXIMAGE3DPROC glad_debug_glTexImage3D = glad_debug_impl_glTexImage3D;
PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;
GLboolean GLAD_API_PTR glad_debug_impl_glIsFramebuffer(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsFramebuffer", (GLADapiproc) glIsFramebuffer, 1, arg0);
    ret = glIsFramebuffer(arg0);
    _post_call_gl_callback((void*) &ret, "glIsFramebuffer", (GLADapiproc) glIsFramebuffer, 1, arg0);
    return ret;
}
PFNGLISFRAMEBUFFERPROC glad_debug_glIsFramebuffer = glad_debug_impl_glIsFramebuffer;
PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex;
void GLAD_API_PTR glad_debug_impl_glPrimitiveRestartIndex(GLuint arg0) {
    _pre_call_gl_callback("glPrimitiveRestartIndex", (GLADapiproc) glPrimitiveRestartIndex, 1, arg0);
    glPrimitiveRestartIndex(arg0);
    _post_call_gl_callback(NULL, "glPrimitiveRestartIndex", (GLADapiproc) glPrimitiveRestartIndex, 1, arg0);
    
}
PFNGLPRIMITIVERESTARTINDEXPROC glad_debug_glPrimitiveRestartIndex = glad_debug_impl_glPrimitiveRestartIndex;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
void GLAD_API_PTR glad_debug_impl_glDeleteBuffers(GLsizei arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glDeleteBuffers", (GLADapiproc) glDeleteBuffers, 2, arg0, arg1);
    glDeleteBuffers(arg0, arg1);
    _post_call_gl_callback(NULL, "glDeleteBuffers", (GLADapiproc) glDeleteBuffers, 2, arg0, arg1);
    
}
PFNGLDELETEBUFFERSPROC glad_debug_glDeleteBuffers = glad_debug_impl_glDeleteBuffers;
PFNGLSCISSORPROC glad_glScissor;
void GLAD_API_PTR glad_debug_impl_glScissor(GLint arg0, GLint arg1, GLsizei arg2, GLsizei arg3) {
    _pre_call_gl_callback("glScissor", (GLADapiproc) glScissor, 4, arg0, arg1, arg2, arg3);
    glScissor(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glScissor", (GLADapiproc) glScissor, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLSCISSORPROC glad_debug_glScissor = glad_debug_impl_glScissor;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
void GLAD_API_PTR glad_debug_impl_glGetBooleanv(GLenum arg0, GLboolean * arg1) {
    _pre_call_gl_callback("glGetBooleanv", (GLADapiproc) glGetBooleanv, 2, arg0, arg1);
    glGetBooleanv(arg0, arg1);
    _post_call_gl_callback(NULL, "glGetBooleanv", (GLADapiproc) glGetBooleanv, 2, arg0, arg1);
    
}
PFNGLGETBOOLEANVPROC glad_debug_glGetBooleanv = glad_debug_impl_glGetBooleanv;
PFNGLUNIFORM3UIVPROC glad_glUniform3uiv;
void GLAD_API_PTR glad_debug_impl_glUniform3uiv(GLint arg0, GLsizei arg1, const GLuint * arg2) {
    _pre_call_gl_callback("glUniform3uiv", (GLADapiproc) glUniform3uiv, 3, arg0, arg1, arg2);
    glUniform3uiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform3uiv", (GLADapiproc) glUniform3uiv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM3UIVPROC glad_debug_glUniform3uiv = glad_debug_impl_glUniform3uiv;
PFNGLCLEARCOLORPROC glad_glClearColor;
void GLAD_API_PTR glad_debug_impl_glClearColor(GLfloat arg0, GLfloat arg1, GLfloat arg2, GLfloat arg3) {
    _pre_call_gl_callback("glClearColor", (GLADapiproc) glClearColor, 4, arg0, arg1, arg2, arg3);
    glClearColor(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glClearColor", (GLADapiproc) glClearColor, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLCLEARCOLORPROC glad_debug_glClearColor = glad_debug_impl_glClearColor;
PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Niv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Niv", (GLADapiproc) glVertexAttrib4Niv, 2, arg0, arg1);
    glVertexAttrib4Niv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Niv", (GLADapiproc) glVertexAttrib4Niv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NIVPROC glad_debug_glVertexAttrib4Niv = glad_debug_impl_glVertexAttrib4Niv;
PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv;
void GLAD_API_PTR glad_debug_impl_glClearBufferiv(GLenum arg0, GLint arg1, const GLint * arg2) {
    _pre_call_gl_callback("glClearBufferiv", (GLADapiproc) glClearBufferiv, 3, arg0, arg1, arg2);
    glClearBufferiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glClearBufferiv", (GLADapiproc) glClearBufferiv, 3, arg0, arg1, arg2);
    
}
PFNGLCLEARBUFFERIVPROC glad_debug_glClearBufferiv = glad_debug_impl_glClearBufferiv;
PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v;
void GLAD_API_PTR glad_debug_impl_glGetBufferParameteri64v(GLenum arg0, GLenum arg1, GLint64 * arg2) {
    _pre_call_gl_callback("glGetBufferParameteri64v", (GLADapiproc) glGetBufferParameteri64v, 3, arg0, arg1, arg2);
    glGetBufferParameteri64v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetBufferParameteri64v", (GLADapiproc) glGetBufferParameteri64v, 3, arg0, arg1, arg2);
    
}
PFNGLGETBUFFERPARAMETERI64VPROC glad_debug_glGetBufferParameteri64v = glad_debug_impl_glGetBufferParameteri64v;
PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI2uiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttribI2uiv", (GLADapiproc) glVertexAttribI2uiv, 2, arg0, arg1);
    glVertexAttribI2uiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI2uiv", (GLADapiproc) glVertexAttribI2uiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI2UIVPROC glad_debug_glVertexAttribI2uiv = glad_debug_impl_glVertexAttribI2uiv;
PFNGLUNIFORM3UIPROC glad_glUniform3ui;
void GLAD_API_PTR glad_debug_impl_glUniform3ui(GLint arg0, GLuint arg1, GLuint arg2, GLuint arg3) {
    _pre_call_gl_callback("glUniform3ui", (GLADapiproc) glUniform3ui, 4, arg0, arg1, arg2, arg3);
    glUniform3ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniform3ui", (GLADapiproc) glUniform3ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORM3UIPROC glad_debug_glUniform3ui = glad_debug_impl_glUniform3ui;
PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4uiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttribI4uiv", (GLADapiproc) glVertexAttribI4uiv, 2, arg0, arg1);
    glVertexAttribI4uiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4uiv", (GLADapiproc) glVertexAttribI4uiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4UIVPROC glad_debug_glVertexAttribI4uiv = glad_debug_impl_glVertexAttribI4uiv;
PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;
void GLAD_API_PTR glad_debug_impl_glPointParameterfv(GLenum arg0, const GLfloat * arg1) {
    _pre_call_gl_callback("glPointParameterfv", (GLADapiproc) glPointParameterfv, 2, arg0, arg1);
    glPointParameterfv(arg0, arg1);
    _post_call_gl_callback(NULL, "glPointParameterfv", (GLADapiproc) glPointParameterfv, 2, arg0, arg1);
    
}
PFNGLPOINTPARAMETERFVPROC glad_debug_glPointParameterfv = glad_debug_impl_glPointParameterfv;
PFNGLUNIFORM2FVPROC glad_glUniform2fv;
void GLAD_API_PTR glad_debug_impl_glUniform2fv(GLint arg0, GLsizei arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glUniform2fv", (GLADapiproc) glUniform2fv, 3, arg0, arg1, arg2);
    glUniform2fv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform2fv", (GLADapiproc) glUniform2fv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM2FVPROC glad_debug_glUniform2fv = glad_debug_impl_glUniform2fv;
PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv;
void GLAD_API_PTR glad_debug_impl_glGetSamplerParameterIuiv(GLuint arg0, GLenum arg1, GLuint * arg2) {
    _pre_call_gl_callback("glGetSamplerParameterIuiv", (GLADapiproc) glGetSamplerParameterIuiv, 3, arg0, arg1, arg2);
    glGetSamplerParameterIuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetSamplerParameterIuiv", (GLADapiproc) glGetSamplerParameterIuiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETSAMPLERPARAMETERIUIVPROC glad_debug_glGetSamplerParameterIuiv = glad_debug_impl_glGetSamplerParameterIuiv;
PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange;
void GLAD_API_PTR glad_debug_impl_glBindBufferRange(GLenum arg0, GLuint arg1, GLuint arg2, GLintptr arg3, GLsizeiptr arg4) {
    _pre_call_gl_callback("glBindBufferRange", (GLADapiproc) glBindBufferRange, 5, arg0, arg1, arg2, arg3, arg4);
    glBindBufferRange(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glBindBufferRange", (GLADapiproc) glBindBufferRange, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLBINDBUFFERRANGEPROC glad_debug_glBindBufferRange = glad_debug_impl_glBindBufferRange;
PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix2x3fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix2x3fv", (GLADapiproc) glUniformMatrix2x3fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix2x3fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix2x3fv", (GLADapiproc) glUniformMatrix2x3fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX2X3FVPROC glad_debug_glUniformMatrix2x3fv = glad_debug_impl_glUniformMatrix2x3fv;
PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv;
void GLAD_API_PTR glad_debug_impl_glGetVertexAttribIuiv(GLuint arg0, GLenum arg1, GLuint * arg2) {
    _pre_call_gl_callback("glGetVertexAttribIuiv", (GLADapiproc) glGetVertexAttribIuiv, 3, arg0, arg1, arg2);
    glGetVertexAttribIuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetVertexAttribIuiv", (GLADapiproc) glGetVertexAttribIuiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETVERTEXATTRIBIUIVPROC glad_debug_glGetVertexAttribIuiv = glad_debug_impl_glGetVertexAttribIuiv;
PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nusv(GLuint arg0, const GLushort * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Nusv", (GLADapiproc) glVertexAttrib4Nusv, 2, arg0, arg1);
    glVertexAttrib4Nusv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nusv", (GLADapiproc) glVertexAttrib4Nusv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NUSVPROC glad_debug_glVertexAttrib4Nusv = glad_debug_impl_glVertexAttrib4Nusv;
PFNGLCOLORMASKPROC glad_glColorMask;
void GLAD_API_PTR glad_debug_impl_glColorMask(GLboolean arg0, GLboolean arg1, GLboolean arg2, GLboolean arg3) {
    _pre_call_gl_callback("glColorMask", (GLADapiproc) glColorMask, 4, arg0, arg1, arg2, arg3);
    glColorMask(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glColorMask", (GLADapiproc) glColorMask, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLCOLORMASKPROC glad_debug_glColorMask = glad_debug_impl_glColorMask;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexSubImage2D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLsizei arg4, GLsizei arg5, GLenum arg6, GLsizei arg7, const void * arg8) {
    _pre_call_gl_callback("glCompressedTexSubImage2D", (GLADapiproc) glCompressedTexSubImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    glCompressedTexSubImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    _post_call_gl_callback(NULL, "glCompressedTexSubImage2D", (GLADapiproc) glCompressedTexSubImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    
}
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_debug_glCompressedTexSubImage2D = glad_debug_impl_glCompressedTexSubImage2D;
PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4bv(GLuint arg0, const GLbyte * arg1) {
    _pre_call_gl_callback("glVertexAttribI4bv", (GLADapiproc) glVertexAttribI4bv, 2, arg0, arg1);
    glVertexAttribI4bv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI4bv", (GLADapiproc) glVertexAttribI4bv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI4BVPROC glad_debug_glVertexAttribI4bv = glad_debug_impl_glVertexAttribI4bv;
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
void GLAD_API_PTR glad_debug_impl_glGetTexParameterfv(GLenum arg0, GLenum arg1, GLfloat * arg2) {
    _pre_call_gl_callback("glGetTexParameterfv", (GLADapiproc) glGetTexParameterfv, 3, arg0, arg1, arg2);
    glGetTexParameterfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetTexParameterfv", (GLADapiproc) glGetTexParameterfv, 3, arg0, arg1, arg2);
    
}
PFNGLGETTEXPARAMETERFVPROC glad_debug_glGetTexParameterfv = glad_debug_impl_glGetTexParameterfv;
PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync;
GLenum GLAD_API_PTR glad_debug_impl_glClientWaitSync(GLsync arg0, GLbitfield arg1, GLuint64 arg2) {
    GLenum ret;
    _pre_call_gl_callback("glClientWaitSync", (GLADapiproc) glClientWaitSync, 3, arg0, arg1, arg2);
    ret = glClientWaitSync(arg0, arg1, arg2);
    _post_call_gl_callback((void*) &ret, "glClientWaitSync", (GLADapiproc) glClientWaitSync, 3, arg0, arg1, arg2);
    return ret;
}
PFNGLCLIENTWAITSYNCPROC glad_debug_glClientWaitSync = glad_debug_impl_glClientWaitSync;
PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI4ui(GLuint arg0, GLuint arg1, GLuint arg2, GLuint arg3, GLuint arg4) {
    _pre_call_gl_callback("glVertexAttribI4ui", (GLADapiproc) glVertexAttribI4ui, 5, arg0, arg1, arg2, arg3, arg4);
    glVertexAttribI4ui(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glVertexAttribI4ui", (GLADapiproc) glVertexAttribI4ui, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLVERTEXATTRIBI4UIPROC glad_debug_glVertexAttribI4ui = glad_debug_impl_glVertexAttribI4ui;
PFNGLDEPTHFUNCPROC glad_glDepthFunc;
void GLAD_API_PTR glad_debug_impl_glDepthFunc(GLenum arg0) {
    _pre_call_gl_callback("glDepthFunc", (GLADapiproc) glDepthFunc, 1, arg0);
    glDepthFunc(arg0);
    _post_call_gl_callback(NULL, "glDepthFunc", (GLADapiproc) glDepthFunc, 1, arg0);
    
}
PFNGLDEPTHFUNCPROC glad_debug_glDepthFunc = glad_debug_impl_glDepthFunc;
PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv;
void GLAD_API_PTR glad_debug_impl_glTexParameterIiv(GLenum arg0, GLenum arg1, const GLint * arg2) {
    _pre_call_gl_callback("glTexParameterIiv", (GLADapiproc) glTexParameterIiv, 3, arg0, arg1, arg2);
    glTexParameterIiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameterIiv", (GLADapiproc) glTexParameterIiv, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERIIVPROC glad_debug_glTexParameterIiv = glad_debug_impl_glTexParameterIiv;
PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
void GLAD_API_PTR glad_debug_impl_glBlendEquation(GLenum arg0) {
    _pre_call_gl_callback("glBlendEquation", (GLADapiproc) glBlendEquation, 1, arg0);
    glBlendEquation(arg0);
    _post_call_gl_callback(NULL, "glBlendEquation", (GLADapiproc) glBlendEquation, 1, arg0);
    
}
PFNGLBLENDEQUATIONPROC glad_debug_glBlendEquation = glad_debug_impl_glBlendEquation;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
GLint GLAD_API_PTR glad_debug_impl_glGetUniformLocation(GLuint arg0, const GLchar * arg1) {
    GLint ret;
    _pre_call_gl_callback("glGetUniformLocation", (GLADapiproc) glGetUniformLocation, 2, arg0, arg1);
    ret = glGetUniformLocation(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetUniformLocation", (GLADapiproc) glGetUniformLocation, 2, arg0, arg1);
    return ret;
}
PFNGLGETUNIFORMLOCATIONPROC glad_debug_glGetUniformLocation = glad_debug_impl_glGetUniformLocation;
PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback;
void GLAD_API_PTR glad_debug_impl_glEndTransformFeedback(void) {
    _pre_call_gl_callback("glEndTransformFeedback", (GLADapiproc) glEndTransformFeedback, 0);
    glEndTransformFeedback();
    _post_call_gl_callback(NULL, "glEndTransformFeedback", (GLADapiproc) glEndTransformFeedback, 0);
    
}
PFNGLENDTRANSFORMFEEDBACKPROC glad_debug_glEndTransformFeedback = glad_debug_impl_glEndTransformFeedback;
PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4usv(GLuint arg0, const GLushort * arg1) {
    _pre_call_gl_callback("glVertexAttrib4usv", (GLADapiproc) glVertexAttrib4usv, 2, arg0, arg1);
    glVertexAttrib4usv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4usv", (GLADapiproc) glVertexAttrib4usv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4USVPROC glad_debug_glVertexAttrib4usv = glad_debug_impl_glVertexAttrib4usv;
PFNGLUNIFORM4FVPROC glad_glUniform4fv;
void GLAD_API_PTR glad_debug_impl_glUniform4fv(GLint arg0, GLsizei arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glUniform4fv", (GLADapiproc) glUniform4fv, 3, arg0, arg1, arg2);
    glUniform4fv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform4fv", (GLADapiproc) glUniform4fv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM4FVPROC glad_debug_glUniform4fv = glad_debug_impl_glUniform4fv;
PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback;
void GLAD_API_PTR glad_debug_impl_glBeginTransformFeedback(GLenum arg0) {
    _pre_call_gl_callback("glBeginTransformFeedback", (GLADapiproc) glBeginTransformFeedback, 1, arg0);
    glBeginTransformFeedback(arg0);
    _post_call_gl_callback(NULL, "glBeginTransformFeedback", (GLADapiproc) glBeginTransformFeedback, 1, arg0);
    
}
PFNGLBEGINTRANSFORMFEEDBACKPROC glad_debug_glBeginTransformFeedback = glad_debug_impl_glBeginTransformFeedback;
PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI1iv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttribI1iv", (GLADapiproc) glVertexAttribI1iv, 2, arg0, arg1);
    glVertexAttribI1iv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI1iv", (GLADapiproc) glVertexAttribI1iv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI1IVPROC glad_debug_glVertexAttribI1iv = glad_debug_impl_glVertexAttribI1iv;
PFNGLISSAMPLERPROC glad_glIsSampler;
GLboolean GLAD_API_PTR glad_debug_impl_glIsSampler(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsSampler", (GLADapiproc) glIsSampler, 1, arg0);
    ret = glIsSampler(arg0);
    _post_call_gl_callback((void*) &ret, "glIsSampler", (GLADapiproc) glIsSampler, 1, arg0);
    return ret;
}
PFNGLISSAMPLERPROC glad_debug_glIsSampler = glad_debug_impl_glIsSampler;
PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor;
void GLAD_API_PTR glad_debug_impl_glVertexAttribDivisor(GLuint arg0, GLuint arg1) {
    _pre_call_gl_callback("glVertexAttribDivisor", (GLADapiproc) glVertexAttribDivisor, 2, arg0, arg1);
    glVertexAttribDivisor(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribDivisor", (GLADapiproc) glVertexAttribDivisor, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBDIVISORPROC glad_debug_glVertexAttribDivisor = glad_debug_impl_glVertexAttribDivisor;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D;
void GLAD_API_PTR glad_debug_impl_glCompressedTexImage1D(GLenum arg0, GLint arg1, GLenum arg2, GLsizei arg3, GLint arg4, GLsizei arg5, const void * arg6) {
    _pre_call_gl_callback("glCompressedTexImage1D", (GLADapiproc) glCompressedTexImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glCompressedTexImage1D(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glCompressedTexImage1D", (GLADapiproc) glCompressedTexImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_debug_glCompressedTexImage1D = glad_debug_impl_glCompressedTexImage1D;
PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D;
void GLAD_API_PTR glad_debug_impl_glCopyTexSubImage1D(GLenum arg0, GLint arg1, GLint arg2, GLint arg3, GLint arg4, GLsizei arg5) {
    _pre_call_gl_callback("glCopyTexSubImage1D", (GLADapiproc) glCopyTexSubImage1D, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glCopyTexSubImage1D(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glCopyTexSubImage1D", (GLADapiproc) glCopyTexSubImage1D, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLCOPYTEXSUBIMAGE1DPROC glad_debug_glCopyTexSubImage1D = glad_debug_impl_glCopyTexSubImage1D;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex;
void GLAD_API_PTR glad_debug_impl_glDrawRangeElementsBaseVertex(GLenum arg0, GLuint arg1, GLuint arg2, GLsizei arg3, GLenum arg4, const void * arg5, GLint arg6) {
    _pre_call_gl_callback("glDrawRangeElementsBaseVertex", (GLADapiproc) glDrawRangeElementsBaseVertex, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glDrawRangeElementsBaseVertex(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glDrawRangeElementsBaseVertex", (GLADapiproc) glDrawRangeElementsBaseVertex, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_debug_glDrawRangeElementsBaseVertex = glad_debug_impl_glDrawRangeElementsBaseVertex;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
GLenum GLAD_API_PTR glad_debug_impl_glCheckFramebufferStatus(GLenum arg0) {
    GLenum ret;
    _pre_call_gl_callback("glCheckFramebufferStatus", (GLADapiproc) glCheckFramebufferStatus, 1, arg0);
    ret = glCheckFramebufferStatus(arg0);
    _post_call_gl_callback((void*) &ret, "glCheckFramebufferStatus", (GLADapiproc) glCheckFramebufferStatus, 1, arg0);
    return ret;
}
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_debug_glCheckFramebufferStatus = glad_debug_impl_glCheckFramebufferStatus;
PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender;
void GLAD_API_PTR glad_debug_impl_glEndConditionalRender(void) {
    _pre_call_gl_callback("glEndConditionalRender", (GLADapiproc) glEndConditionalRender, 0);
    glEndConditionalRender();
    _post_call_gl_callback(NULL, "glEndConditionalRender", (GLADapiproc) glEndConditionalRender, 0);
    
}
PFNGLENDCONDITIONALRENDERPROC glad_debug_glEndConditionalRender = glad_debug_impl_glEndConditionalRender;
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
void GLAD_API_PTR glad_debug_impl_glBindAttribLocation(GLuint arg0, GLuint arg1, const GLchar * arg2) {
    _pre_call_gl_callback("glBindAttribLocation", (GLADapiproc) glBindAttribLocation, 3, arg0, arg1, arg2);
    glBindAttribLocation(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glBindAttribLocation", (GLADapiproc) glBindAttribLocation, 3, arg0, arg1, arg2);
    
}
PFNGLBINDATTRIBLOCATIONPROC glad_debug_glBindAttribLocation = glad_debug_impl_glBindAttribLocation;
PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix4x2fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix4x2fv", (GLADapiproc) glUniformMatrix4x2fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix4x2fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix4x2fv", (GLADapiproc) glUniformMatrix4x2fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX4X2FVPROC glad_debug_glUniformMatrix4x2fv = glad_debug_impl_glUniformMatrix4x2fv;
PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib1dv(GLuint arg0, const GLdouble * arg1) {
    _pre_call_gl_callback("glVertexAttrib1dv", (GLADapiproc) glVertexAttrib1dv, 2, arg0, arg1);
    glVertexAttrib1dv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib1dv", (GLADapiproc) glVertexAttrib1dv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB1DVPROC glad_debug_glVertexAttrib1dv = glad_debug_impl_glVertexAttrib1dv;
PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;
void GLAD_API_PTR glad_debug_impl_glDrawRangeElements(GLenum arg0, GLuint arg1, GLuint arg2, GLsizei arg3, GLenum arg4, const void * arg5) {
    _pre_call_gl_callback("glDrawRangeElements", (GLADapiproc) glDrawRangeElements, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glDrawRangeElements(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glDrawRangeElements", (GLADapiproc) glDrawRangeElements, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLDRAWRANGEELEMENTSPROC glad_debug_glDrawRangeElements = glad_debug_impl_glDrawRangeElements;
PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv;
void GLAD_API_PTR glad_debug_impl_glGetQueryObjectuiv(GLuint arg0, GLenum arg1, GLuint * arg2) {
    _pre_call_gl_callback("glGetQueryObjectuiv", (GLADapiproc) glGetQueryObjectuiv, 3, arg0, arg1, arg2);
    glGetQueryObjectuiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetQueryObjectuiv", (GLADapiproc) glGetQueryObjectuiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETQUERYOBJECTUIVPROC glad_debug_glGetQueryObjectuiv = glad_debug_impl_glGetQueryObjectuiv;
PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase;
void GLAD_API_PTR glad_debug_impl_glBindBufferBase(GLenum arg0, GLuint arg1, GLuint arg2) {
    _pre_call_gl_callback("glBindBufferBase", (GLADapiproc) glBindBufferBase, 3, arg0, arg1, arg2);
    glBindBufferBase(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glBindBufferBase", (GLADapiproc) glBindBufferBase, 3, arg0, arg1, arg2);
    
}
PFNGLBINDBUFFERBASEPROC glad_debug_glBindBufferBase = glad_debug_impl_glBindBufferBase;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
void GLAD_API_PTR glad_debug_impl_glBufferSubData(GLenum arg0, GLintptr arg1, GLsizeiptr arg2, const void * arg3) {
    _pre_call_gl_callback("glBufferSubData", (GLADapiproc) glBufferSubData, 4, arg0, arg1, arg2, arg3);
    glBufferSubData(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glBufferSubData", (GLADapiproc) glBufferSubData, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLBUFFERSUBDATAPROC glad_debug_glBufferSubData = glad_debug_impl_glBufferSubData;
PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4iv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttrib4iv", (GLADapiproc) glVertexAttrib4iv, 2, arg0, arg1);
    glVertexAttrib4iv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4iv", (GLADapiproc) glVertexAttrib4iv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4IVPROC glad_debug_glVertexAttrib4iv = glad_debug_impl_glVertexAttrib4iv;
PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange;
void * GLAD_API_PTR glad_debug_impl_glMapBufferRange(GLenum arg0, GLintptr arg1, GLsizeiptr arg2, GLbitfield arg3) {
    void * ret;
    _pre_call_gl_callback("glMapBufferRange", (GLADapiproc) glMapBufferRange, 4, arg0, arg1, arg2, arg3);
    ret = glMapBufferRange(arg0, arg1, arg2, arg3);
    _post_call_gl_callback((void*) &ret, "glMapBufferRange", (GLADapiproc) glMapBufferRange, 4, arg0, arg1, arg2, arg3);
    return ret;
}
PFNGLMAPBUFFERRANGEPROC glad_debug_glMapBufferRange = glad_debug_impl_glMapBufferRange;
PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture;
void GLAD_API_PTR glad_debug_impl_glFramebufferTexture(GLenum arg0, GLenum arg1, GLuint arg2, GLint arg3) {
    _pre_call_gl_callback("glFramebufferTexture", (GLADapiproc) glFramebufferTexture, 4, arg0, arg1, arg2, arg3);
    glFramebufferTexture(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glFramebufferTexture", (GLADapiproc) glFramebufferTexture, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLFRAMEBUFFERTEXTUREPROC glad_debug_glFramebufferTexture = glad_debug_impl_glFramebufferTexture;
PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays;
void GLAD_API_PTR glad_debug_impl_glMultiDrawArrays(GLenum arg0, const GLint * arg1, const GLsizei * arg2, GLsizei arg3) {
    _pre_call_gl_callback("glMultiDrawArrays", (GLADapiproc) glMultiDrawArrays, 4, arg0, arg1, arg2, arg3);
    glMultiDrawArrays(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glMultiDrawArrays", (GLADapiproc) glMultiDrawArrays, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLMULTIDRAWARRAYSPROC glad_debug_glMultiDrawArrays = glad_debug_impl_glMultiDrawArrays;
PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI2iv(GLuint arg0, const GLint * arg1) {
    _pre_call_gl_callback("glVertexAttribI2iv", (GLADapiproc) glVertexAttribI2iv, 2, arg0, arg1);
    glVertexAttribI2iv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI2iv", (GLADapiproc) glVertexAttribI2iv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI2IVPROC glad_debug_glVertexAttribI2iv = glad_debug_impl_glVertexAttribI2iv;
PFNGLDISABLEIPROC glad_glDisablei;
void GLAD_API_PTR glad_debug_impl_glDisablei(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glDisablei", (GLADapiproc) glDisablei, 2, arg0, arg1);
    glDisablei(arg0, arg1);
    _post_call_gl_callback(NULL, "glDisablei", (GLADapiproc) glDisablei, 2, arg0, arg1);
    
}
PFNGLDISABLEIPROC glad_debug_glDisablei = glad_debug_impl_glDisablei;
PFNGLSHADERSOURCEPROC glad_glShaderSource;
void GLAD_API_PTR glad_debug_impl_glShaderSource(GLuint arg0, GLsizei arg1, const GLchar *const* arg2, const GLint * arg3) {
    _pre_call_gl_callback("glShaderSource", (GLADapiproc) glShaderSource, 4, arg0, arg1, arg2, arg3);
    glShaderSource(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glShaderSource", (GLADapiproc) glShaderSource, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLSHADERSOURCEPROC glad_debug_glShaderSource = glad_debug_impl_glShaderSource;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName;
void GLAD_API_PTR glad_debug_impl_glGetActiveUniformBlockName(GLuint arg0, GLuint arg1, GLsizei arg2, GLsizei * arg3, GLchar * arg4) {
    _pre_call_gl_callback("glGetActiveUniformBlockName", (GLADapiproc) glGetActiveUniformBlockName, 5, arg0, arg1, arg2, arg3, arg4);
    glGetActiveUniformBlockName(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glGetActiveUniformBlockName", (GLADapiproc) glGetActiveUniformBlockName, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_debug_glGetActiveUniformBlockName = glad_debug_impl_glGetActiveUniformBlockName;
PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI3uiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttribI3uiv", (GLADapiproc) glVertexAttribI3uiv, 2, arg0, arg1);
    glVertexAttribI3uiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI3uiv", (GLADapiproc) glVertexAttribI3uiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI3UIVPROC glad_debug_glVertexAttribI3uiv = glad_debug_impl_glVertexAttribI3uiv;
PFNGLGETSYNCIVPROC glad_glGetSynciv;
void GLAD_API_PTR glad_debug_impl_glGetSynciv(GLsync arg0, GLenum arg1, GLsizei arg2, GLsizei * arg3, GLint * arg4) {
    _pre_call_gl_callback("glGetSynciv", (GLADapiproc) glGetSynciv, 5, arg0, arg1, arg2, arg3, arg4);
    glGetSynciv(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glGetSynciv", (GLADapiproc) glGetSynciv, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLGETSYNCIVPROC glad_debug_glGetSynciv = glad_debug_impl_glGetSynciv;
PFNGLBEGINQUERYPROC glad_glBeginQuery;
void GLAD_API_PTR glad_debug_impl_glBeginQuery(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glBeginQuery", (GLADapiproc) glBeginQuery, 2, arg0, arg1);
    glBeginQuery(arg0, arg1);
    _post_call_gl_callback(NULL, "glBeginQuery", (GLADapiproc) glBeginQuery, 2, arg0, arg1);
    
}
PFNGLBEGINQUERYPROC glad_debug_glBeginQuery = glad_debug_impl_glBeginQuery;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix4fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix4fv", (GLADapiproc) glUniformMatrix4fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix4fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix4fv", (GLADapiproc) glUniformMatrix4fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX4FVPROC glad_debug_glUniformMatrix4fv = glad_debug_impl_glUniformMatrix4fv;
PFNGLBINDBUFFERPROC glad_glBindBuffer;
void GLAD_API_PTR glad_debug_impl_glBindBuffer(GLenum arg0, GLuint arg1) {
    _pre_call_gl_callback("glBindBuffer", (GLADapiproc) glBindBuffer, 2, arg0, arg1);
    glBindBuffer(arg0, arg1);
    _post_call_gl_callback(NULL, "glBindBuffer", (GLADapiproc) glBindBuffer, 2, arg0, arg1);
    
}
PFNGLBINDBUFFERPROC glad_debug_glBindBuffer = glad_debug_impl_glBindBuffer;
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix2fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix2fv", (GLADapiproc) glUniformMatrix2fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix2fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix2fv", (GLADapiproc) glUniformMatrix2fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX2FVPROC glad_debug_glUniformMatrix2fv = glad_debug_impl_glUniformMatrix2fv;
PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv;
void GLAD_API_PTR glad_debug_impl_glUniformMatrix2x4fv(GLint arg0, GLsizei arg1, GLboolean arg2, const GLfloat * arg3) {
    _pre_call_gl_callback("glUniformMatrix2x4fv", (GLADapiproc) glUniformMatrix2x4fv, 4, arg0, arg1, arg2, arg3);
    glUniformMatrix2x4fv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glUniformMatrix2x4fv", (GLADapiproc) glUniformMatrix2x4fv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLUNIFORMMATRIX2X4FVPROC glad_debug_glUniformMatrix2x4fv = glad_debug_impl_glUniformMatrix2x4fv;
PFNGLBUFFERDATAPROC glad_glBufferData;
void GLAD_API_PTR glad_debug_impl_glBufferData(GLenum arg0, GLsizeiptr arg1, const void * arg2, GLenum arg3) {
    _pre_call_gl_callback("glBufferData", (GLADapiproc) glBufferData, 4, arg0, arg1, arg2, arg3);
    glBufferData(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glBufferData", (GLADapiproc) glBufferData, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLBUFFERDATAPROC glad_debug_glBufferData = glad_debug_impl_glBufferData;
PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv;
void GLAD_API_PTR glad_debug_impl_glGetTexParameterIiv(GLenum arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetTexParameterIiv", (GLADapiproc) glGetTexParameterIiv, 3, arg0, arg1, arg2);
    glGetTexParameterIiv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetTexParameterIiv", (GLADapiproc) glGetTexParameterIiv, 3, arg0, arg1, arg2);
    
}
PFNGLGETTEXPARAMETERIIVPROC glad_debug_glGetTexParameterIiv = glad_debug_impl_glGetTexParameterIiv;
PFNGLGETERRORPROC glad_glGetError;
GLenum GLAD_API_PTR glad_debug_impl_glGetError(void) {
    GLenum ret;
    _pre_call_gl_callback("glGetError", (GLADapiproc) glGetError, 0);
    ret = glGetError();
    _post_call_gl_callback((void*) &ret, "glGetError", (GLADapiproc) glGetError, 0);
    return ret;
}
PFNGLGETERRORPROC glad_debug_glGetError = glad_debug_impl_glGetError;
PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP2ui(GLuint arg0, GLenum arg1, GLboolean arg2, GLuint arg3) {
    _pre_call_gl_callback("glVertexAttribP2ui", (GLADapiproc) glVertexAttribP2ui, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP2ui(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP2ui", (GLADapiproc) glVertexAttribP2ui, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP2UIPROC glad_debug_glVertexAttribP2ui = glad_debug_impl_glVertexAttribP2ui;
PFNGLGETFLOATVPROC glad_glGetFloatv;
void GLAD_API_PTR glad_debug_impl_glGetFloatv(GLenum arg0, GLfloat * arg1) {
    _pre_call_gl_callback("glGetFloatv", (GLADapiproc) glGetFloatv, 2, arg0, arg1);
    glGetFloatv(arg0, arg1);
    _post_call_gl_callback(NULL, "glGetFloatv", (GLADapiproc) glGetFloatv, 2, arg0, arg1);
    
}
PFNGLGETFLOATVPROC glad_debug_glGetFloatv = glad_debug_impl_glGetFloatv;
PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D;
void GLAD_API_PTR glad_debug_impl_glTexSubImage1D(GLenum arg0, GLint arg1, GLint arg2, GLsizei arg3, GLenum arg4, GLenum arg5, const void * arg6) {
    _pre_call_gl_callback("glTexSubImage1D", (GLADapiproc) glTexSubImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glTexSubImage1D(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glTexSubImage1D", (GLADapiproc) glTexSubImage1D, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLTEXSUBIMAGE1DPROC glad_debug_glTexSubImage1D = glad_debug_impl_glTexSubImage1D;
PFNGLREADPIXELSPROC glad_glReadPixels;
void GLAD_API_PTR glad_debug_impl_glReadPixels(GLint arg0, GLint arg1, GLsizei arg2, GLsizei arg3, GLenum arg4, GLenum arg5, void * arg6) {
    _pre_call_gl_callback("glReadPixels", (GLADapiproc) glReadPixels, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glReadPixels(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glReadPixels", (GLADapiproc) glReadPixels, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLREADPIXELSPROC glad_debug_glReadPixels = glad_debug_impl_glReadPixels;
PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv;
void GLAD_API_PTR glad_debug_impl_glGetTexLevelParameterfv(GLenum arg0, GLint arg1, GLenum arg2, GLfloat * arg3) {
    _pre_call_gl_callback("glGetTexLevelParameterfv", (GLADapiproc) glGetTexLevelParameterfv, 4, arg0, arg1, arg2, arg3);
    glGetTexLevelParameterfv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glGetTexLevelParameterfv", (GLADapiproc) glGetTexLevelParameterfv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLGETTEXLEVELPARAMETERFVPROC glad_debug_glGetTexLevelParameterfv = glad_debug_impl_glGetTexLevelParameterfv;
PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI1i(GLuint arg0, GLint arg1) {
    _pre_call_gl_callback("glVertexAttribI1i", (GLADapiproc) glVertexAttribI1i, 2, arg0, arg1);
    glVertexAttribI1i(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI1i", (GLADapiproc) glVertexAttribI1i, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI1IPROC glad_debug_glVertexAttribI1i = glad_debug_impl_glVertexAttribI1i;
PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribP3uiv(GLuint arg0, GLenum arg1, GLboolean arg2, const GLuint * arg3) {
    _pre_call_gl_callback("glVertexAttribP3uiv", (GLADapiproc) glVertexAttribP3uiv, 4, arg0, arg1, arg2, arg3);
    glVertexAttribP3uiv(arg0, arg1, arg2, arg3);
    _post_call_gl_callback(NULL, "glVertexAttribP3uiv", (GLADapiproc) glVertexAttribP3uiv, 4, arg0, arg1, arg2, arg3);
    
}
PFNGLVERTEXATTRIBP3UIVPROC glad_debug_glVertexAttribP3uiv = glad_debug_impl_glVertexAttribP3uiv;
PFNGLGETINTEGERVPROC glad_glGetIntegerv;
void GLAD_API_PTR glad_debug_impl_glGetIntegerv(GLenum arg0, GLint * arg1) {
    _pre_call_gl_callback("glGetIntegerv", (GLADapiproc) glGetIntegerv, 2, arg0, arg1);
    glGetIntegerv(arg0, arg1);
    _post_call_gl_callback(NULL, "glGetIntegerv", (GLADapiproc) glGetIntegerv, 2, arg0, arg1);
    
}
PFNGLGETINTEGERVPROC glad_debug_glGetIntegerv = glad_debug_impl_glGetIntegerv;
PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv;
void GLAD_API_PTR glad_debug_impl_glGetBufferPointerv(GLenum arg0, GLenum arg1, void ** arg2) {
    _pre_call_gl_callback("glGetBufferPointerv", (GLADapiproc) glGetBufferPointerv, 3, arg0, arg1, arg2);
    glGetBufferPointerv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetBufferPointerv", (GLADapiproc) glGetBufferPointerv, 3, arg0, arg1, arg2);
    
}
PFNGLGETBUFFERPOINTERVPROC glad_debug_glGetBufferPointerv = glad_debug_impl_glGetBufferPointerv;
PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D;
void GLAD_API_PTR glad_debug_impl_glFramebufferTexture3D(GLenum arg0, GLenum arg1, GLenum arg2, GLuint arg3, GLint arg4, GLint arg5) {
    _pre_call_gl_callback("glFramebufferTexture3D", (GLADapiproc) glFramebufferTexture3D, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glFramebufferTexture3D(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glFramebufferTexture3D", (GLADapiproc) glFramebufferTexture3D, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLFRAMEBUFFERTEXTURE3DPROC glad_debug_glFramebufferTexture3D = glad_debug_impl_glFramebufferTexture3D;
PFNGLISQUERYPROC glad_glIsQuery;
GLboolean GLAD_API_PTR glad_debug_impl_glIsQuery(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsQuery", (GLADapiproc) glIsQuery, 1, arg0);
    ret = glIsQuery(arg0);
    _post_call_gl_callback((void*) &ret, "glIsQuery", (GLADapiproc) glIsQuery, 1, arg0);
    return ret;
}
PFNGLISQUERYPROC glad_debug_glIsQuery = glad_debug_impl_glIsQuery;
PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4sv(GLuint arg0, const GLshort * arg1) {
    _pre_call_gl_callback("glVertexAttrib4sv", (GLADapiproc) glVertexAttrib4sv, 2, arg0, arg1);
    glVertexAttrib4sv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4sv", (GLADapiproc) glVertexAttrib4sv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4SVPROC glad_debug_glVertexAttrib4sv = glad_debug_impl_glVertexAttrib4sv;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
void GLAD_API_PTR glad_debug_impl_glTexImage2D(GLenum arg0, GLint arg1, GLint arg2, GLsizei arg3, GLsizei arg4, GLint arg5, GLenum arg6, GLenum arg7, const void * arg8) {
    _pre_call_gl_callback("glTexImage2D", (GLADapiproc) glTexImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    glTexImage2D(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    _post_call_gl_callback(NULL, "glTexImage2D", (GLADapiproc) glTexImage2D, 9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    
}
PFNGLTEXIMAGE2DPROC glad_debug_glTexImage2D = glad_debug_impl_glTexImage2D;
PFNGLSTENCILMASKPROC glad_glStencilMask;
void GLAD_API_PTR glad_debug_impl_glStencilMask(GLuint arg0) {
    _pre_call_gl_callback("glStencilMask", (GLADapiproc) glStencilMask, 1, arg0);
    glStencilMask(arg0);
    _post_call_gl_callback(NULL, "glStencilMask", (GLADapiproc) glStencilMask, 1, arg0);
    
}
PFNGLSTENCILMASKPROC glad_debug_glStencilMask = glad_debug_impl_glStencilMask;
PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv;
void GLAD_API_PTR glad_debug_impl_glSamplerParameterfv(GLuint arg0, GLenum arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glSamplerParameterfv", (GLADapiproc) glSamplerParameterfv, 3, arg0, arg1, arg2);
    glSamplerParameterfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glSamplerParameterfv", (GLADapiproc) glSamplerParameterfv, 3, arg0, arg1, arg2);
    
}
PFNGLSAMPLERPARAMETERFVPROC glad_debug_glSamplerParameterfv = glad_debug_impl_glSamplerParameterfv;
PFNGLISTEXTUREPROC glad_glIsTexture;
GLboolean GLAD_API_PTR glad_debug_impl_glIsTexture(GLuint arg0) {
    GLboolean ret;
    _pre_call_gl_callback("glIsTexture", (GLADapiproc) glIsTexture, 1, arg0);
    ret = glIsTexture(arg0);
    _post_call_gl_callback((void*) &ret, "glIsTexture", (GLADapiproc) glIsTexture, 1, arg0);
    return ret;
}
PFNGLISTEXTUREPROC glad_debug_glIsTexture = glad_debug_impl_glIsTexture;
PFNGLUNIFORM1FVPROC glad_glUniform1fv;
void GLAD_API_PTR glad_debug_impl_glUniform1fv(GLint arg0, GLsizei arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glUniform1fv", (GLADapiproc) glUniform1fv, 3, arg0, arg1, arg2);
    glUniform1fv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glUniform1fv", (GLADapiproc) glUniform1fv, 3, arg0, arg1, arg2);
    
}
PFNGLUNIFORM1FVPROC glad_debug_glUniform1fv = glad_debug_impl_glUniform1fv;
PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib4Nubv(GLuint arg0, const GLubyte * arg1) {
    _pre_call_gl_callback("glVertexAttrib4Nubv", (GLADapiproc) glVertexAttrib4Nubv, 2, arg0, arg1);
    glVertexAttrib4Nubv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib4Nubv", (GLADapiproc) glVertexAttrib4Nubv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB4NUBVPROC glad_debug_glVertexAttrib4Nubv = glad_debug_impl_glVertexAttrib4Nubv;
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
void GLAD_API_PTR glad_debug_impl_glTexParameterfv(GLenum arg0, GLenum arg1, const GLfloat * arg2) {
    _pre_call_gl_callback("glTexParameterfv", (GLADapiproc) glTexParameterfv, 3, arg0, arg1, arg2);
    glTexParameterfv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glTexParameterfv", (GLADapiproc) glTexParameterfv, 3, arg0, arg1, arg2);
    
}
PFNGLTEXPARAMETERFVPROC glad_debug_glTexParameterfv = glad_debug_impl_glTexParameterfv;
PFNGLHINTPROC glad_glHint;
void GLAD_API_PTR glad_debug_impl_glHint(GLenum arg0, GLenum arg1) {
    _pre_call_gl_callback("glHint", (GLADapiproc) glHint, 2, arg0, arg1);
    glHint(arg0, arg1);
    _post_call_gl_callback(NULL, "glHint", (GLADapiproc) glHint, 2, arg0, arg1);
    
}
PFNGLHINTPROC glad_debug_glHint = glad_debug_impl_glHint;
PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv;
void GLAD_API_PTR glad_debug_impl_glGetSamplerParameteriv(GLuint arg0, GLenum arg1, GLint * arg2) {
    _pre_call_gl_callback("glGetSamplerParameteriv", (GLADapiproc) glGetSamplerParameteriv, 3, arg0, arg1, arg2);
    glGetSamplerParameteriv(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetSamplerParameteriv", (GLADapiproc) glGetSamplerParameteriv, 3, arg0, arg1, arg2);
    
}
PFNGLGETSAMPLERPARAMETERIVPROC glad_debug_glGetSamplerParameteriv = glad_debug_impl_glGetSamplerParameteriv;
PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData;
void GLAD_API_PTR glad_debug_impl_glCopyBufferSubData(GLenum arg0, GLenum arg1, GLintptr arg2, GLintptr arg3, GLsizeiptr arg4) {
    _pre_call_gl_callback("glCopyBufferSubData", (GLADapiproc) glCopyBufferSubData, 5, arg0, arg1, arg2, arg3, arg4);
    glCopyBufferSubData(arg0, arg1, arg2, arg3, arg4);
    _post_call_gl_callback(NULL, "glCopyBufferSubData", (GLADapiproc) glCopyBufferSubData, 5, arg0, arg1, arg2, arg3, arg4);
    
}
PFNGLCOPYBUFFERSUBDATAPROC glad_debug_glCopyBufferSubData = glad_debug_impl_glCopyBufferSubData;
PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv;
void GLAD_API_PTR glad_debug_impl_glVertexAttribI1uiv(GLuint arg0, const GLuint * arg1) {
    _pre_call_gl_callback("glVertexAttribI1uiv", (GLADapiproc) glVertexAttribI1uiv, 2, arg0, arg1);
    glVertexAttribI1uiv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttribI1uiv", (GLADapiproc) glVertexAttribI1uiv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIBI1UIVPROC glad_debug_glVertexAttribI1uiv = glad_debug_impl_glVertexAttribI1uiv;
PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2d(GLuint arg0, GLdouble arg1, GLdouble arg2) {
    _pre_call_gl_callback("glVertexAttrib2d", (GLADapiproc) glVertexAttrib2d, 3, arg0, arg1, arg2);
    glVertexAttrib2d(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glVertexAttrib2d", (GLADapiproc) glVertexAttrib2d, 3, arg0, arg1, arg2);
    
}
PFNGLVERTEXATTRIB2DPROC glad_debug_glVertexAttrib2d = glad_debug_impl_glVertexAttrib2d;
PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2f(GLuint arg0, GLfloat arg1, GLfloat arg2) {
    _pre_call_gl_callback("glVertexAttrib2f", (GLADapiproc) glVertexAttrib2f, 3, arg0, arg1, arg2);
    glVertexAttrib2f(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glVertexAttrib2f", (GLADapiproc) glVertexAttrib2f, 3, arg0, arg1, arg2);
    
}
PFNGLVERTEXATTRIB2FPROC glad_debug_glVertexAttrib2f = glad_debug_impl_glVertexAttrib2f;
PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib3dv(GLuint arg0, const GLdouble * arg1) {
    _pre_call_gl_callback("glVertexAttrib3dv", (GLADapiproc) glVertexAttrib3dv, 2, arg0, arg1);
    glVertexAttrib3dv(arg0, arg1);
    _post_call_gl_callback(NULL, "glVertexAttrib3dv", (GLADapiproc) glVertexAttrib3dv, 2, arg0, arg1);
    
}
PFNGLVERTEXATTRIB3DVPROC glad_debug_glVertexAttrib3dv = glad_debug_impl_glVertexAttrib3dv;
PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v;
void GLAD_API_PTR glad_debug_impl_glGetQueryObjectui64v(GLuint arg0, GLenum arg1, GLuint64 * arg2) {
    _pre_call_gl_callback("glGetQueryObjectui64v", (GLADapiproc) glGetQueryObjectui64v, 3, arg0, arg1, arg2);
    glGetQueryObjectui64v(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glGetQueryObjectui64v", (GLADapiproc) glGetQueryObjectui64v, 3, arg0, arg1, arg2);
    
}
PFNGLGETQUERYOBJECTUI64VPROC glad_debug_glGetQueryObjectui64v = glad_debug_impl_glGetQueryObjectui64v;
PFNGLDEPTHMASKPROC glad_glDepthMask;
void GLAD_API_PTR glad_debug_impl_glDepthMask(GLboolean arg0) {
    _pre_call_gl_callback("glDepthMask", (GLADapiproc) glDepthMask, 1, arg0);
    glDepthMask(arg0);
    _post_call_gl_callback(NULL, "glDepthMask", (GLADapiproc) glDepthMask, 1, arg0);
    
}
PFNGLDEPTHMASKPROC glad_debug_glDepthMask = glad_debug_impl_glDepthMask;
PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s;
void GLAD_API_PTR glad_debug_impl_glVertexAttrib2s(GLuint arg0, GLshort arg1, GLshort arg2) {
    _pre_call_gl_callback("glVertexAttrib2s", (GLADapiproc) glVertexAttrib2s, 3, arg0, arg1, arg2);
    glVertexAttrib2s(arg0, arg1, arg2);
    _post_call_gl_callback(NULL, "glVertexAttrib2s", (GLADapiproc) glVertexAttrib2s, 3, arg0, arg1, arg2);
    
}
PFNGLVERTEXATTRIB2SPROC glad_debug_glVertexAttrib2s = glad_debug_impl_glVertexAttrib2s;
PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample;
void GLAD_API_PTR glad_debug_impl_glTexImage3DMultisample(GLenum arg0, GLsizei arg1, GLenum arg2, GLsizei arg3, GLsizei arg4, GLsizei arg5, GLboolean arg6) {
    _pre_call_gl_callback("glTexImage3DMultisample", (GLADapiproc) glTexImage3DMultisample, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glTexImage3DMultisample(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glTexImage3DMultisample", (GLADapiproc) glTexImage3DMultisample, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_debug_glTexImage3DMultisample = glad_debug_impl_glTexImage3DMultisample;
PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex;
GLuint GLAD_API_PTR glad_debug_impl_glGetUniformBlockIndex(GLuint arg0, const GLchar * arg1) {
    GLuint ret;
    _pre_call_gl_callback("glGetUniformBlockIndex", (GLADapiproc) glGetUniformBlockIndex, 2, arg0, arg1);
    ret = glGetUniformBlockIndex(arg0, arg1);
    _post_call_gl_callback((void*) &ret, "glGetUniformBlockIndex", (GLADapiproc) glGetUniformBlockIndex, 2, arg0, arg1);
    return ret;
}
PFNGLGETUNIFORMBLOCKINDEXPROC glad_debug_glGetUniformBlockIndex = glad_debug_impl_glGetUniformBlockIndex;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample;
void GLAD_API_PTR glad_debug_impl_glTexImage2DMultisample(GLenum arg0, GLsizei arg1, GLenum arg2, GLsizei arg3, GLsizei arg4, GLboolean arg5) {
    _pre_call_gl_callback("glTexImage2DMultisample", (GLADapiproc) glTexImage2DMultisample, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    glTexImage2DMultisample(arg0, arg1, arg2, arg3, arg4, arg5);
    _post_call_gl_callback(NULL, "glTexImage2DMultisample", (GLADapiproc) glTexImage2DMultisample, 6, arg0, arg1, arg2, arg3, arg4, arg5);
    
}
PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_debug_glTexImage2DMultisample = glad_debug_impl_glTexImage2DMultisample;
PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;
void GLAD_API_PTR glad_debug_impl_glGetActiveUniform(GLuint arg0, GLuint arg1, GLsizei arg2, GLsizei * arg3, GLint * arg4, GLenum * arg5, GLchar * arg6) {
    _pre_call_gl_callback("glGetActiveUniform", (GLADapiproc) glGetActiveUniform, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    glGetActiveUniform(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    _post_call_gl_callback(NULL, "glGetActiveUniform", (GLADapiproc) glGetActiveUniform, 7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    
}
PFNGLGETACTIVEUNIFORMPROC glad_debug_glGetActiveUniform = glad_debug_impl_glGetActiveUniform;
PFNGLFRONTFACEPROC glad_glFrontFace;
void GLAD_API_PTR glad_debug_impl_glFrontFace(GLenum arg0) {
    _pre_call_gl_callback("glFrontFace", (GLADapiproc) glFrontFace, 1, arg0);
    glFrontFace(arg0);
    _post_call_gl_callback(NULL, "glFrontFace", (GLADapiproc) glFrontFace, 1, arg0);
    
}
PFNGLFRONTFACEPROC glad_debug_glFrontFace = glad_debug_impl_glFrontFace;


static void glad_gl_load_GL_VERSION_1_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_0) return;
    glFlush = (PFNGLFLUSHPROC) load("glFlush", userptr);
    glTexImage2D = (PFNGLTEXIMAGE2DPROC) load("glTexImage2D", userptr);
    glDisable = (PFNGLDISABLEPROC) load("glDisable", userptr);
    glLogicOp = (PFNGLLOGICOPPROC) load("glLogicOp", userptr);
    glStencilMask = (PFNGLSTENCILMASKPROC) load("glStencilMask", userptr);
    glColorMask = (PFNGLCOLORMASKPROC) load("glColorMask", userptr);
    glGetDoublev = (PFNGLGETDOUBLEVPROC) load("glGetDoublev", userptr);
    glHint = (PFNGLHINTPROC) load("glHint", userptr);
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) load("glTexParameterfv", userptr);
    glClearColor = (PFNGLCLEARCOLORPROC) load("glClearColor", userptr);
    glCullFace = (PFNGLCULLFACEPROC) load("glCullFace", userptr);
    glGetString = (PFNGLGETSTRINGPROC) load("glGetString", userptr);
    glEnable = (PFNGLENABLEPROC) load("glEnable", userptr);
    glClear = (PFNGLCLEARPROC) load("glClear", userptr);
    glPointSize = (PFNGLPOINTSIZEPROC) load("glPointSize", userptr);
    glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) load("glGetTexLevelParameteriv", userptr);
    glLineWidth = (PFNGLLINEWIDTHPROC) load("glLineWidth", userptr);
    glFinish = (PFNGLFINISHPROC) load("glFinish", userptr);
    glIsEnabled = (PFNGLISENABLEDPROC) load("glIsEnabled", userptr);
    glStencilOp = (PFNGLSTENCILOPPROC) load("glStencilOp", userptr);
    glReadPixels = (PFNGLREADPIXELSPROC) load("glReadPixels", userptr);
    glDepthRange = (PFNGLDEPTHRANGEPROC) load("glDepthRange", userptr);
    glBlendFunc = (PFNGLBLENDFUNCPROC) load("glBlendFunc", userptr);
    glPolygonMode = (PFNGLPOLYGONMODEPROC) load("glPolygonMode", userptr);
    glViewport = (PFNGLVIEWPORTPROC) load("glViewport", userptr);
    glTexImage1D = (PFNGLTEXIMAGE1DPROC) load("glTexImage1D", userptr);
    glGetError = (PFNGLGETERRORPROC) load("glGetError", userptr);
    glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) load("glTexParameteriv", userptr);
    glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) load("glGetTexParameteriv", userptr);
    glClearStencil = (PFNGLCLEARSTENCILPROC) load("glClearStencil", userptr);
    glDepthMask = (PFNGLDEPTHMASKPROC) load("glDepthMask", userptr);
    glGetFloatv = (PFNGLGETFLOATVPROC) load("glGetFloatv", userptr);
    glGetTexImage = (PFNGLGETTEXIMAGEPROC) load("glGetTexImage", userptr);
    glClearDepth = (PFNGLCLEARDEPTHPROC) load("glClearDepth", userptr);
    glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) load("glGetTexLevelParameterfv", userptr);
    glTexParameterf = (PFNGLTEXPARAMETERFPROC) load("glTexParameterf", userptr);
    glTexParameteri = (PFNGLTEXPARAMETERIPROC) load("glTexParameteri", userptr);
    glFrontFace = (PFNGLFRONTFACEPROC) load("glFrontFace", userptr);
    glReadBuffer = (PFNGLREADBUFFERPROC) load("glReadBuffer", userptr);
    glStencilFunc = (PFNGLSTENCILFUNCPROC) load("glStencilFunc", userptr);
    glDepthFunc = (PFNGLDEPTHFUNCPROC) load("glDepthFunc", userptr);
    glGetIntegerv = (PFNGLGETINTEGERVPROC) load("glGetIntegerv", userptr);
    glScissor = (PFNGLSCISSORPROC) load("glScissor", userptr);
    glGetBooleanv = (PFNGLGETBOOLEANVPROC) load("glGetBooleanv", userptr);
    glPixelStorei = (PFNGLPIXELSTOREIPROC) load("glPixelStorei", userptr);
    glDrawBuffer = (PFNGLDRAWBUFFERPROC) load("glDrawBuffer", userptr);
    glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) load("glGetTexParameterfv", userptr);
    glPixelStoref = (PFNGLPIXELSTOREFPROC) load("glPixelStoref", userptr);
}
static void glad_gl_load_GL_VERSION_1_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_1) return;
    glDeleteTextures = (PFNGLDELETETEXTURESPROC) load("glDeleteTextures", userptr);
    glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load("glCopyTexSubImage2D", userptr);
    glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) load("glCopyTexImage1D", userptr);
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load("glTexSubImage2D", userptr);
    glGenTextures = (PFNGLGENTEXTURESPROC) load("glGenTextures", userptr);
    glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load("glCopyTexImage2D", userptr);
    glIsTexture = (PFNGLISTEXTUREPROC) load("glIsTexture", userptr);
    glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) load("glTexSubImage1D", userptr);
    glDrawElements = (PFNGLDRAWELEMENTSPROC) load("glDrawElements", userptr);
    glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) load("glPolygonOffset", userptr);
    glBindTexture = (PFNGLBINDTEXTUREPROC) load("glBindTexture", userptr);
    glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) load("glCopyTexSubImage1D", userptr);
    glDrawArrays = (PFNGLDRAWARRAYSPROC) load("glDrawArrays", userptr);
}
static void glad_gl_load_GL_VERSION_1_2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_2) return;
    glTexImage3D = (PFNGLTEXIMAGE3DPROC) load("glTexImage3D", userptr);
    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) load("glCopyTexSubImage3D", userptr);
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) load("glDrawRangeElements", userptr);
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) load("glTexSubImage3D", userptr);
}
static void glad_gl_load_GL_VERSION_1_3( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_3) return;
    glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) load("glCompressedTexImage1D", userptr);
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load("glCompressedTexImage2D", userptr);
    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load("glSampleCoverage", userptr);
    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) load("glCompressedTexSubImage3D", userptr);
    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) load("glCompressedTexImage3D", userptr);
    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load("glCompressedTexSubImage2D", userptr);
    glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) load("glCompressedTexSubImage1D", userptr);
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) load("glActiveTexture", userptr);
    glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) load("glGetCompressedTexImage", userptr);
}
static void glad_gl_load_GL_VERSION_1_4( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_4) return;
    glPointParameteri = (PFNGLPOINTPARAMETERIPROC) load("glPointParameteri", userptr);
    glBlendColor = (PFNGLBLENDCOLORPROC) load("glBlendColor", userptr);
    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) load("glBlendFuncSeparate", userptr);
    glPointParameterf = (PFNGLPOINTPARAMETERFPROC) load("glPointParameterf", userptr);
    glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) load("glPointParameterfv", userptr);
    glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) load("glMultiDrawArrays", userptr);
    glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) load("glMultiDrawElements", userptr);
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) load("glBlendEquation", userptr);
    glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) load("glPointParameteriv", userptr);
}
static void glad_gl_load_GL_VERSION_1_5( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_1_5) return;
    glMapBuffer = (PFNGLMAPBUFFERPROC) load("glMapBuffer", userptr);
    glGetQueryiv = (PFNGLGETQUERYIVPROC) load("glGetQueryiv", userptr);
    glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) load("glGetQueryObjectiv", userptr);
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) load("glUnmapBuffer", userptr);
    glBufferData = (PFNGLBUFFERDATAPROC) load("glBufferData", userptr);
    glEndQuery = (PFNGLENDQUERYPROC) load("glEndQuery", userptr);
    glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) load("glGetBufferSubData", userptr);
    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load("glGetBufferParameteriv", userptr);
    glGenBuffers = (PFNGLGENBUFFERSPROC) load("glGenBuffers", userptr);
    glBeginQuery = (PFNGLBEGINQUERYPROC) load("glBeginQuery", userptr);
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) load("glGetBufferPointerv", userptr);
    glBindBuffer = (PFNGLBINDBUFFERPROC) load("glBindBuffer", userptr);
    glGenQueries = (PFNGLGENQUERIESPROC) load("glGenQueries", userptr);
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load("glDeleteBuffers", userptr);
    glDeleteQueries = (PFNGLDELETEQUERIESPROC) load("glDeleteQueries", userptr);
    glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) load("glGetQueryObjectuiv", userptr);
    glIsBuffer = (PFNGLISBUFFERPROC) load("glIsBuffer", userptr);
    glIsQuery = (PFNGLISQUERYPROC) load("glIsQuery", userptr);
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) load("glBufferSubData", userptr);
}
static void glad_gl_load_GL_VERSION_2_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_2_0) return;
    glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) load("glVertexAttrib4Niv", userptr);
    glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) load("glStencilMaskSeparate", userptr);
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) load("glGetVertexAttribPointerv", userptr);
    glLinkProgram = (PFNGLLINKPROGRAMPROC) load("glLinkProgram", userptr);
    glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) load("glVertexAttrib3sv", userptr);
    glDetachShader = (PFNGLDETACHSHADERPROC) load("glDetachShader", userptr);
    glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) load("glVertexAttrib1sv", userptr);
    glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) load("glVertexAttrib4bv", userptr);
    glUniform2fv = (PFNGLUNIFORM2FVPROC) load("glUniform2fv", userptr);
    glCompileShader = (PFNGLCOMPILESHADERPROC) load("glCompileShader", userptr);
    glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) load("glStencilOpSeparate", userptr);
    glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) load("glStencilFuncSeparate", userptr);
    glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) load("glVertexAttrib4f", userptr);
    glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) load("glVertexAttrib4d", userptr);
    glUniform4iv = (PFNGLUNIFORM4IVPROC) load("glUniform4iv", userptr);
    glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) load("glVertexAttrib4s", userptr);
    glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) load("glVertexAttrib4Nusv", userptr);
    glUniform1f = (PFNGLUNIFORM1FPROC) load("glUniform1f", userptr);
    glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) load("glGetVertexAttribfv", userptr);
    glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) load("glVertexAttrib4Nbv", userptr);
    glCreateShader = (PFNGLCREATESHADERPROC) load("glCreateShader", userptr);
    glUniform1i = (PFNGLUNIFORM1IPROC) load("glUniform1i", userptr);
    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) load("glGetActiveAttrib", userptr);
    glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) load("glVertexAttrib1d", userptr);
    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) load("glVertexAttrib1f", userptr);
    glUniform2i = (PFNGLUNIFORM2IPROC) load("glUniform2i", userptr);
    glUniform2f = (PFNGLUNIFORM2FPROC) load("glUniform2f", userptr);
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) load("glGetProgramiv", userptr);
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) load("glVertexAttribPointer", userptr);
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC) load("glDrawBuffers", userptr);
    glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) load("glVertexAttrib1s", userptr);
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) load("glGetUniformLocation", userptr);
    glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) load("glVertexAttrib4usv", userptr);
    glUniform4fv = (PFNGLUNIFORM4FVPROC) load("glUniform4fv", userptr);
    glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) load("glVertexAttrib2dv", userptr);
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) load("glDeleteProgram", userptr);
    glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) load("glVertexAttrib4Nuiv", userptr);
    glAttachShader = (PFNGLATTACHSHADERPROC) load("glAttachShader", userptr);
    glUniform3i = (PFNGLUNIFORM3IPROC) load("glUniform3i", userptr);
    glUniform3f = (PFNGLUNIFORM3FPROC) load("glUniform3f", userptr);
    glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) load("glVertexAttrib4ubv", userptr);
    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) load("glBindAttribLocation", userptr);
    glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) load("glVertexAttrib1dv", userptr);
    glUniform2iv = (PFNGLUNIFORM2IVPROC) load("glUniform2iv", userptr);
    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) load("glVertexAttrib1fv", userptr);
    glUniform1iv = (PFNGLUNIFORM1IVPROC) load("glUniform1iv", userptr);
    glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) load("glGetVertexAttribdv", userptr);
    glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) load("glVertexAttrib3f", userptr);
    glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) load("glVertexAttrib4uiv", userptr);
    glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) load("glVertexAttrib3d", userptr);
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) load("glDisableVertexAttribArray", userptr);
    glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) load("glVertexAttrib3s", userptr);
    glShaderSource = (PFNGLSHADERSOURCEPROC) load("glShaderSource", userptr);
    glIsProgram = (PFNGLISPROGRAMPROC) load("glIsProgram", userptr);
    glGetUniformiv = (PFNGLGETUNIFORMIVPROC) load("glGetUniformiv", userptr);
    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) load("glVertexAttrib4fv", userptr);
    glUniform4i = (PFNGLUNIFORM4IPROC) load("glUniform4i", userptr);
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) load("glEnableVertexAttribArray", userptr);
    glUniform3fv = (PFNGLUNIFORM3FVPROC) load("glUniform3fv", userptr);
    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) load("glVertexAttrib2fv", userptr);
    glUniform4f = (PFNGLUNIFORM4FPROC) load("glUniform4f", userptr);
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) load("glUniformMatrix2fv", userptr);
    glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) load("glVertexAttrib4Nub", userptr);
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) load("glUniformMatrix3fv", userptr);
    glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) load("glGetVertexAttribiv", userptr);
    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) load("glVertexAttrib3fv", userptr);
    glUniform3iv = (PFNGLUNIFORM3IVPROC) load("glUniform3iv", userptr);
    glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) load("glVertexAttrib4iv", userptr);
    glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) load("glGetAttachedShaders", userptr);
    glIsShader = (PFNGLISSHADERPROC) load("glIsShader", userptr);
    glUseProgram = (PFNGLUSEPROGRAMPROC) load("glUseProgram", userptr);
    glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) load("glVertexAttrib4sv", userptr);
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) load("glGetProgramInfoLog", userptr);
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) load("glGetShaderInfoLog", userptr);
    glUniform1fv = (PFNGLUNIFORM1FVPROC) load("glUniform1fv", userptr);
    glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) load("glVertexAttrib4Nubv", userptr);
    glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) load("glBlendEquationSeparate", userptr);
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) load("glGetAttribLocation", userptr);
    glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) load("glVertexAttrib4dv", userptr);
    glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) load("glVertexAttrib2sv", userptr);
    glDeleteShader = (PFNGLDELETESHADERPROC) load("glDeleteShader", userptr);
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) load("glCreateProgram", userptr);
    glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) load("glVertexAttrib4Nsv", userptr);
    glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) load("glVertexAttrib2d", userptr);
    glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) load("glVertexAttrib2f", userptr);
    glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) load("glVertexAttrib3dv", userptr);
    glGetUniformfv = (PFNGLGETUNIFORMFVPROC) load("glGetUniformfv", userptr);
    glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) load("glVertexAttrib2s", userptr);
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) load("glUniformMatrix4fv", userptr);
    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) load("glGetActiveUniform", userptr);
    glGetShaderiv = (PFNGLGETSHADERIVPROC) load("glGetShaderiv", userptr);
    glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) load("glGetShaderSource", userptr);
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) load("glValidateProgram", userptr);
}
static void glad_gl_load_GL_VERSION_2_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_2_1) return;
    glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) load("glUniformMatrix3x2fv", userptr);
    glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) load("glUniformMatrix2x4fv", userptr);
    glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) load("glUniformMatrix4x2fv", userptr);
    glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) load("glUniformMatrix3x4fv", userptr);
    glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) load("glUniformMatrix2x3fv", userptr);
    glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) load("glUniformMatrix4x3fv", userptr);
}
static void glad_gl_load_GL_VERSION_3_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_0) return;
    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) load("glGenRenderbuffers", userptr);
    glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) load("glVertexAttribI2iv", userptr);
    glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) load("glGetRenderbufferParameteriv", userptr);
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) load("glDeleteRenderbuffers", userptr);
    glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) load("glVertexAttribI4ubv", userptr);
    glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) load("glVertexAttribI3ui", userptr);
    glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) load("glVertexAttribI4ui", userptr);
    glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) load("glClearBufferiv", userptr);
    glDisablei = (PFNGLDISABLEIPROC) load("glDisablei", userptr);
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) load("glBindVertexArray", userptr);
    glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) load("glFramebufferTexture3D", userptr);
    glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) load("glFramebufferTextureLayer", userptr);
    glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) load("glTexParameterIiv", userptr);
    glUniform4ui = (PFNGLUNIFORM4UIPROC) load("glUniform4ui", userptr);
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) load("glBindRenderbuffer", userptr);
    glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) load("glVertexAttribI3uiv", userptr);
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load("glBindBufferBase", userptr);
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) load("glBindFramebuffer", userptr);
    glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) load("glVertexAttribI2uiv", userptr);
    glUniform1ui = (PFNGLUNIFORM1UIPROC) load("glUniform1ui", userptr);
    glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) load("glEndTransformFeedback", userptr);
    glUniform3ui = (PFNGLUNIFORM3UIPROC) load("glUniform3ui", userptr);
    glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) load("glFlushMappedBufferRange", userptr);
    glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) load("glVertexAttribI2i", userptr);
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) load("glDeleteFramebuffers", userptr);
    glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) load("glVertexAttribI4uiv", userptr);
    glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) load("glBeginTransformFeedback", userptr);
    glGetStringi = (PFNGLGETSTRINGIPROC) load("glGetStringi", userptr);
    glUniform2uiv = (PFNGLUNIFORM2UIVPROC) load("glUniform2uiv", userptr);
    glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) load("glVertexAttribI1ui", userptr);
    glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) load("glVertexAttribI1iv", userptr);
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) load("glRenderbufferStorage", userptr);
    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) load("glGetIntegeri_v", userptr);
    glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) load("glVertexAttribI4bv", userptr);
    glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) load("glVertexAttribI2ui", userptr);
    glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) load("glGetVertexAttribIuiv", userptr);
    glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) load("glVertexAttribI3iv", userptr);
    glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) load("glGetTransformFeedbackVarying", userptr);
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) load("glFramebufferTexture2D", userptr);
    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) load("glGetFramebufferAttachmentParameteriv", userptr);
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) load("glClearBufferfv", userptr);
    glEnablei = (PFNGLENABLEIPROC) load("glEnablei", userptr);
    glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) load("glIsFramebuffer", userptr);
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) load("glCheckFramebufferStatus", userptr);
    glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) load("glGetFragDataLocation", userptr);
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) load("glBindBufferRange", userptr);
    glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) load("glGetTexParameterIiv", userptr);
    glIsVertexArray = (PFNGLISVERTEXARRAYPROC) load("glIsVertexArray", userptr);
    glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) load("glVertexAttribI4iv", userptr);
    glUniform1uiv = (PFNGLUNIFORM1UIVPROC) load("glUniform1uiv", userptr);
    glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) load("glTransformFeedbackVaryings", userptr);
    glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) load("glBlitFramebuffer", userptr);
    glIsEnabledi = (PFNGLISENABLEDIPROC) load("glIsEnabledi", userptr);
    glClampColor = (PFNGLCLAMPCOLORPROC) load("glClampColor", userptr);
    glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) load("glEndConditionalRender", userptr);
    glColorMaski = (PFNGLCOLORMASKIPROC) load("glColorMaski", userptr);
    glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) load("glGetUniformuiv", userptr);
    glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) load("glVertexAttribI3i", userptr);
    glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) load("glBindFragDataLocation", userptr);
    glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) load("glBeginConditionalRender", userptr);
    glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) load("glClearBufferfi", userptr);
    glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) load("glGetVertexAttribIiv", userptr);
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) load("glGenVertexArrays", userptr);
    glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) load("glVertexAttribI4sv", userptr);
    glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) load("glVertexAttribI1i", userptr);
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) load("glGenFramebuffers", userptr);
    glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) load("glVertexAttribI4usv", userptr);
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) load("glFramebufferRenderbuffer", userptr);
    glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) load("glMapBufferRange", userptr);
    glUniform2ui = (PFNGLUNIFORM2UIPROC) load("glUniform2ui", userptr);
    glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) load("glVertexAttribI1uiv", userptr);
    glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) load("glClearBufferuiv", userptr);
    glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) load("glTexParameterIuiv", userptr);
    glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) load("glGetTexParameterIuiv", userptr);
    glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) load("glIsRenderbuffer", userptr);
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) load("glGenerateMipmap", userptr);
    glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) load("glFramebufferTexture1D", userptr);
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) load("glDeleteVertexArrays", userptr);
    glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) load("glVertexAttribI4i", userptr);
    glUniform3uiv = (PFNGLUNIFORM3UIVPROC) load("glUniform3uiv", userptr);
    glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) load("glRenderbufferStorageMultisample", userptr);
    glUniform4uiv = (PFNGLUNIFORM4UIVPROC) load("glUniform4uiv", userptr);
    glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) load("glGetBooleani_v", userptr);
    glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) load("glVertexAttribIPointer", userptr);
}
static void glad_gl_load_GL_VERSION_3_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_1) return;
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load("glBindBufferBase", userptr);
    glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) load("glGetActiveUniformBlockName", userptr);
    glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) load("glGetActiveUniformsiv", userptr);
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) load("glDrawArraysInstanced", userptr);
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) load("glBindBufferRange", userptr);
    glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) load("glCopyBufferSubData", userptr);
    glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) load("glGetActiveUniformBlockiv", userptr);
    glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) load("glGetActiveUniformName", userptr);
    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) load("glUniformBlockBinding", userptr);
    glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) load("glGetUniformIndices", userptr);
    glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) load("glPrimitiveRestartIndex", userptr);
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) load("glDrawElementsInstanced", userptr);
    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) load("glGetIntegeri_v", userptr);
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) load("glGetUniformBlockIndex", userptr);
    glTexBuffer = (PFNGLTEXBUFFERPROC) load("glTexBuffer", userptr);
}
static void glad_gl_load_GL_VERSION_3_2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_2) return;
    glIsSync = (PFNGLISSYNCPROC) load("glIsSync", userptr);
    glGetSynciv = (PFNGLGETSYNCIVPROC) load("glGetSynciv", userptr);
    glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) load("glTexImage2DMultisample", userptr);
    glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) load("glClientWaitSync", userptr);
    glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) load("glMultiDrawElementsBaseVertex", userptr);
    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) load("glGetInteger64i_v", userptr);
    glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) load("glProvokingVertex", userptr);
    glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) load("glFramebufferTexture", userptr);
    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) load("glGetBufferParameteri64v", userptr);
    glGetInteger64v = (PFNGLGETINTEGER64VPROC) load("glGetInteger64v", userptr);
    glDeleteSync = (PFNGLDELETESYNCPROC) load("glDeleteSync", userptr);
    glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) load("glDrawElementsInstancedBaseVertex", userptr);
    glFenceSync = (PFNGLFENCESYNCPROC) load("glFenceSync", userptr);
    glWaitSync = (PFNGLWAITSYNCPROC) load("glWaitSync", userptr);
    glSampleMaski = (PFNGLSAMPLEMASKIPROC) load("glSampleMaski", userptr);
    glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) load("glTexImage3DMultisample", userptr);
    glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) load("glDrawElementsBaseVertex", userptr);
    glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) load("glGetMultisamplefv", userptr);
    glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) load("glDrawRangeElementsBaseVertex", userptr);
}
static void glad_gl_load_GL_VERSION_3_3( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_3_3) return;
    glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) load("glSamplerParameterIuiv", userptr);
    glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) load("glGetSamplerParameterfv", userptr);
    glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) load("glSamplerParameterfv", userptr);
    glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC) load("glVertexAttribP1uiv", userptr);
    glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) load("glGetSamplerParameterIuiv", userptr);
    glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC) load("glVertexAttribP4uiv", userptr);
    glDeleteSamplers = (PFNGLDELETESAMPLERSPROC) load("glDeleteSamplers", userptr);
    glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC) load("glVertexAttribP2uiv", userptr);
    glBindSampler = (PFNGLBINDSAMPLERPROC) load("glBindSampler", userptr);
    glIsSampler = (PFNGLISSAMPLERPROC) load("glIsSampler", userptr);
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) load("glVertexAttribDivisor", userptr);
    glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC) load("glVertexAttribP2ui", userptr);
    glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC) load("glVertexAttribP1ui", userptr);
    glQueryCounter = (PFNGLQUERYCOUNTERPROC) load("glQueryCounter", userptr);
    glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC) load("glVertexAttribP3ui", userptr);
    glGenSamplers = (PFNGLGENSAMPLERSPROC) load("glGenSamplers", userptr);
    glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC) load("glGetQueryObjectui64v", userptr);
    glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) load("glBindFragDataLocationIndexed", userptr);
    glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) load("glSamplerParameterIiv", userptr);
    glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC) load("glGetQueryObjecti64v", userptr);
    glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) load("glSamplerParameteri", userptr);
    glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC) load("glVertexAttribP3uiv", userptr);
    glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) load("glSamplerParameterf", userptr);
    glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) load("glGetSamplerParameterIiv", userptr);
    glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC) load("glGetFragDataIndex", userptr);
    glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC) load("glVertexAttribP4ui", userptr);
    glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) load("glGetSamplerParameteriv", userptr);
    glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) load("glSamplerParameteriv", userptr);
}



#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define GLAD_GL_IS_SOME_NEW_VERSION 1
#else
#define GLAD_GL_IS_SOME_NEW_VERSION 0
#endif

static int glad_gl_get_extensions( int version, const char **out_exts, unsigned int *out_num_exts_i, char ***out_exts_i) {
#if GLAD_GL_IS_SOME_NEW_VERSION
    if(GLAD_VERSION_MAJOR(version) < 3) {
#else
    (void) version;
    (void) out_num_exts_i;
    (void) out_exts_i;
#endif
        if (glGetString == NULL) {
            return 0;
        }
        *out_exts = (const char *)glGetString(GL_EXTENSIONS);
#if GLAD_GL_IS_SOME_NEW_VERSION
    } else {
        unsigned int index = 0;
        unsigned int num_exts_i = 0;
        char **exts_i = NULL;
        if (glGetStringi == NULL || glGetIntegerv == NULL) {
            return 0;
        }
        glGetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts_i);
        if (num_exts_i > 0) {
            exts_i = (char **) malloc(num_exts_i * (sizeof *exts_i));
        }
        if (exts_i == NULL) {
            return 0;
        }
        for(index = 0; index < num_exts_i; index++) {
            const char *gl_str_tmp = (const char*) glGetStringi(GL_EXTENSIONS, index);
            size_t len = strlen(gl_str_tmp) + 1;

            char *local_str = (char*) malloc(len * sizeof(char));
            if(local_str != NULL) {
                GLAD_IMPL_UTIL_STRNCPY(local_str, gl_str_tmp, len);
            }

            exts_i[index] = local_str;
        }

        *out_num_exts_i = num_exts_i;
        *out_exts_i = exts_i;
    }
#endif
    return 1;
}
static void glad_gl_free_extensions(char **exts_i, unsigned int num_exts_i) {
    if (exts_i != NULL) {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            free((void *) (exts_i[index]));
        }
        free((void *)exts_i);
        exts_i = NULL;
    }
}
static int glad_gl_has_extension(int version, const char *exts, unsigned int num_exts_i, char **exts_i, const char *ext) {
    if(GLAD_VERSION_MAJOR(version) < 3 || !GLAD_GL_IS_SOME_NEW_VERSION) {
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
            return 0;
        }
        while(1) {
            loc = strstr(extensions, ext);
            if(loc == NULL) {
                return 0;
            }
            terminator = loc + strlen(ext);
            if((loc == extensions || *(loc - 1) == ' ') &&
                (*terminator == ' ' || *terminator == '\0')) {
                return 1;
            }
            extensions = terminator;
        }
    } else {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            const char *e = exts_i[index];
            if(strcmp(e, ext) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(const char* name, void *userptr) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gl( int version) {
    const char *exts = NULL;
    unsigned int num_exts_i = 0;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(version, &exts, &num_exts_i, &exts_i)) return 0;

    (void) glad_gl_has_extension;

    glad_gl_free_extensions(exts_i, num_exts_i);

    return 1;
}

static int glad_gl_find_core_gl(void) {
    int i, major, minor;
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        NULL
    };
    version = (const char*) glGetString(GL_VERSION);
    if (!version) return 0;
    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

    GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

    GLAD_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    GLAD_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    GLAD_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    GLAD_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    GLAD_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
    GLAD_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
    GLAD_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
    GLAD_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
    GLAD_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
    GLAD_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
    GLAD_GL_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
    GLAD_GL_VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLUserPtr( GLADuserptrloadfunc load, void *userptr) {
    int version;

    glGetString = (PFNGLGETSTRINGPROC) load("glGetString", userptr);
    if(glGetString == NULL) return 0;
    if(glGetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gl();

    glad_gl_load_GL_VERSION_1_0(load, userptr);
    glad_gl_load_GL_VERSION_1_1(load, userptr);
    glad_gl_load_GL_VERSION_1_2(load, userptr);
    glad_gl_load_GL_VERSION_1_3(load, userptr);
    glad_gl_load_GL_VERSION_1_4(load, userptr);
    glad_gl_load_GL_VERSION_1_5(load, userptr);
    glad_gl_load_GL_VERSION_2_0(load, userptr);
    glad_gl_load_GL_VERSION_2_1(load, userptr);
    glad_gl_load_GL_VERSION_3_0(load, userptr);
    glad_gl_load_GL_VERSION_3_1(load, userptr);
    glad_gl_load_GL_VERSION_3_2(load, userptr);
    glad_gl_load_GL_VERSION_3_3(load, userptr);

    if (!glad_gl_find_extensions_gl(version)) return 0;



    return version;
}


int gladLoadGL( GLADloadfunc load) {
    return gladLoadGLUserPtr( glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}




#ifdef GLAD_GL

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */

typedef void* (GLAD_API_PTR *GLADglprocaddrfunc)(const char*);
struct _glad_gl_userptr {
    void *gl_handle;
    GLADglprocaddrfunc gl_get_proc_address_ptr;
};

static GLADapiproc glad_gl_get_proc(const char *name, void *vuserptr) {
    struct _glad_gl_userptr userptr = *(struct _glad_gl_userptr*) vuserptr;
    GLADapiproc result = NULL;

#ifndef __APPLE__
    if(userptr.gl_get_proc_address_ptr != NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.gl_get_proc_address_ptr(name);
    }
#endif
    if(result == NULL) {
        result = glad_dlsym_handle(userptr.gl_handle, name);
    }

    return result;
}

int gladLoaderLoadGL(void) {
#ifdef __APPLE__
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"opengl32.dll"};
#else
    static const char *NAMES[] = {
#if defined __CYGWIN__
        "libGL-1.so",
#endif
        "libGL.so.1",
        "libGL.so"
    };
#endif

    int version = 0;
    void *handle;
    struct _glad_gl_userptr userptr;

    handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    if (handle) {
        userptr.gl_handle = handle;
#ifdef __APPLE__
        userptr.gl_get_proc_address_ptr = NULL;
#elif GLAD_PLATFORM_WIN32
        userptr.gl_get_proc_address_ptr =
            (GLADglprocaddrfunc) glad_dlsym_handle(handle, "wglGetProcAddress");
#else
        userptr.gl_get_proc_address_ptr =
            (GLADglprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");
#endif
        version = gladLoadGLUserPtr(glad_gl_get_proc, &userptr);

        glad_close_dlopen_handle(handle);
    }

    return version;
}


#endif /* GLAD_GL */
