/* WARNING: this file contains pre-release extensions
 *
 * The function prototypes hereby presented have not been
 * ratified by the Khronos group, and are subject to change
 * without notification
 *
 * Here be dragons
 */

#ifndef __GL_MESA_PRERELEASE_H__
#define __GL_MESA_PRERELEASE_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

#define GL_HANDLE_TYPE_OPAQUE_FD_KHR 0x9586 /* TODO GET CORRECT VALUE */

typedef void (APIENTRYP PFN_glGenMemoryObjectsKHR) (GLsizei n, GLuint *memoryObjects);
typedef void (APIENTRYP PFN_glDeleteMemoryObjectsKHR) (GLsizei n, const GLuint *memoryObjects);

typedef void (APIENTRYP PFN_glTexStorageMem2DKHR) (GLenum target,
                GLsizei levels,
                GLenum internalformat,
                GLsizei width,
                GLsizei height,
                GLuint memory,
                GLuint64 offset);

typedef void (APIENTRYP PFN_glImportMemoryFdKHR) (GLuint memory,
			GLuint64 size,
			GLenum handleType,
			int fd);

#ifdef __cplusplus
}
#endif

#endif //__GL_MESA_PRERELEASE_H__
