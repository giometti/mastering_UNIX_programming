#include <dlfcn.h>

typedef void (*func_t)(char *text, size_t n);

extern void mod_crypt(char *text, size_t n);
extern void mod_decrypt(char *text, size_t n);
