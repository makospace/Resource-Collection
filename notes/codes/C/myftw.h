#ifndef __MYFTW_H__
#define __MYFTW_H__
#include "apue.h"
static int                  /* we return whatever func() returns */
myftw(char *pathname, Myfunc *func);
#endif