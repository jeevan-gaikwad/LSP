#ifndef _X_SCANDIR
#define _X_SCANDIR
#include<dirent.h>

int x_scandir(const char * dirp,struct dirent ***namelist,
			int (*filter)(const struct dirent *),
			int (*compar)(const struct dirent **, const struct dirent**));
#endif
