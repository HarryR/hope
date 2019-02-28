#ifndef ARG_C_
#define ARG_C_


#ifndef ARG_H_
#include "arg.h"
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <stdlib.h>
#include <string.h>
#endif


char **CommandLineToArgvA(const char *CmdLine, int *_argc) {
  char **argv;
  char *_argv;
  unsigned long len;
  unsigned long argc;
  char a;
  unsigned long i, j;

  int in_QM;
  int in_TEXT;
  int in_SPACE;

  len = strlen(CmdLine);
  i = ((len + 2) / 2) * sizeof(void*) + sizeof(void*);

  argv = (char**)malloc(i + (len + 2) * sizeof(char));

  _argv = (char*)(((unsigned char *)argv) + i);

  argc = 0;
  argv[argc] = _argv;
  in_QM = 0;
  in_TEXT = 0;
  in_SPACE = 1;
  i = 0;
  j = 0;

  while ( (a = CmdLine[i]) ) {
    if (in_QM) {
      if (a == '\"') {
        in_QM = 0;
      } else {
        _argv[j] = a;
        j++;
      }
    } else {
      switch (a) {
      case '\"':
        in_QM = 1;
        in_TEXT = 1;
        if (in_SPACE) {
          argv[argc] = _argv + j;
          argc++;
        }
        in_SPACE = 0;
        break;
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        if (in_TEXT) {
          _argv[j] = '\0';
          j++;
        }
        in_TEXT = 0;
        in_SPACE = 1;
        break;
      default:
        in_TEXT = 1;
        if (in_SPACE) {
          argv[argc] = _argv + j;
          argc++;
        }
        _argv[j] = a;
        j++;
        in_SPACE = 0;
        break;
      }
    }
    i++;
  }
  _argv[j] = '\0';
  argv[argc] = 0;

  (*_argc) = argc;
  return argv;
}


// ARG_C_
#endif
