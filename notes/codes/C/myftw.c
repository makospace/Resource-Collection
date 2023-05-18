#include "myftw.h"

static int                  /* we return whatever func() returns */
myftw(char *pathname, Myfunc *func)
{
    int len;
    fullpath = path_alloc(&len);    /* malloc's for PATH_MAX+1 bytes */
                            /* ({Prog pathalloc}) */
    strncpy(fullpath, pathname, len);       /* protect against */
    fullpath[len-1] = 0;                /* buffer overrun */
 
    return(dopath(func));
}
 