#include <stdio.h>
#include <string.h>
// #include "head.h"
int main()
{
    char a[10] = "12345";
	char *b = ".";

    strcpy(a,"123");
	printf("%s\n", a); 
	printf("%s\n", b);

	return 0;
}