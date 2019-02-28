#ifndef ARG_H_
#define ARG_H_

#ifdef __cplusplus
extern "C" {
#endif

char **CommandLineToArgvA(const char *CmdLine, int *_argc);

#ifdef __cplusplus
}
#endif

#endif
