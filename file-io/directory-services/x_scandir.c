#include<stdio.h>
#include<stdlib.h>
#include"x_scandir.h"
#define ERROR -1
int x_scandir(const char * dirp,struct dirent ***namelist,
			int (*filter)(const struct dirent *),
			int (*compar)(const struct dirent **dirent1, const struct dirent** dirent2)){

	int ret=0,count=0;
	DIR *dirptr=opendir(dirp);
	struct dirent **list=NULL;
	if(dirptr==NULL)
		return ERROR;
	struct dirent *dir_entry=NULL;
	while((dir_entry=readdir(dirptr))!=NULL){
			list=(struct dirent**)realloc((void*)list,++count*sizeof(struct dirent*));
			list[count-1]=dir_entry;
	}
	*namelist=list;
	closedir(dirptr);
	return count;
}
