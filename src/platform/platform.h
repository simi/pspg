/*-------------------------------------------------------------------------
 *
 * platform.h
 *	  Cross-platform compatibility layer
 *
 *-------------------------------------------------------------------------
 */

#ifndef PSPG_PLATFORM_H
#define PSPG_PLATFORM_H

/* Standard includes that work everywhere */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #define PATH_SEPARATOR '\\'
  #define PATH_SEPARATOR_STR "\\"
#else
  #include <sys/types.h>
  #include <unistd.h>
  #define PATH_SEPARATOR '/'
  #define PATH_SEPARATOR_STR "/"
#endif

char *platform_strndup(const char *s, size_t n);
char *platform_basename(char *path);
char *platform_dirname(char *path);
int platform_usleep(unsigned int usec);

#ifdef _WIN32
ssize_t platform_getline(char **lineptr, size_t *n, FILE *stream);
#else
#define platform_getline getline
#endif

#if defined(__has_attribute)
  #if __has_attribute(noreturn)
    #define PSPG_NORETURN __attribute__ ((noreturn))
  #else
    #define PSPG_NORETURN
  #endif
#elif defined(__GNUC__)
  #define PSPG_NORETURN __attribute__ ((noreturn))
#elif defined(_MSC_VER)
  #define PSPG_NORETURN __declspec(noreturn)
#else
  #define PSPG_NORETURN
#endif

#ifndef UNUSED
  #define UNUSED(expr) do { (void)(expr); } while (0)
#endif

#endif /* PSPG_PLATFORM_H */
