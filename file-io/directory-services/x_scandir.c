#include<stdio.h>
#include<stdlib.h>
#include"x_scandir.h"
#define ERROR -1
int x_scandir(const char * dirp,struct dirent ***namelist,
			int (*filter)(const struct dirent *),
			int (*compar)(const struct dirent **dirent1, const struct dirent** dirent2)){

	if(dirp==NULL)
		return -1;

	int ret=0,count=0,i;
	struct dirent **list=NULL;
	struct dirent *dir_entry=NULL;

	DIR *dirptr=opendir(dirp);
	if(dirptr==NULL)
		return ERROR;
	while((dir_entry=readdir(dirptr))!=NULL){
		    //Check whether to add the entry in namelist or not based on filer function
			if(filter!=NULL){
				ret=(*filter)(dir_entry);
				if(ret==0)
					continue;  //Skip adding in the list
			}
			//Add the entry if filter is not NULL and ret is non-zero
			list=(struct dirent**)realloc((void*)list,++count*sizeof(struct dirent*));
			list[count-1]=dir_entry;
	}
	//Sort the list if comparator is provided
	if(compar!=NULL){
		qsort(list,count,sizeof(struct dirent*),(__compar_fn_t)compar);
	}	
	
	*namelist=list;
	closedir(dirptr);
	return count;
}
