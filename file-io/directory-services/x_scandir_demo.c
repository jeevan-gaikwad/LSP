#include<stdio.h>
#include<stdlib.h>
//#include<opt.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include"x_scandir.h"

#define TRUE 1
#define FALSE 0
#define EQUAL 0
#define NON_ZERO 1
#define ZERO 0

int  c_extn_filter(const struct dirent *dir_entry);
int  file_name_length_comparator(const struct dirent ** dirent1,const struct dirent ** dirent2);
void print_usage(char *program_name);
void display_entries(struct dirent **namelist,int no_of_entries);
void cleanup(struct dirent **namelist,int no_of_entries);

char *file_extension=NULL;

int main(int argc, char* argv[])
{
	struct dirent **namelist=NULL;
	int no_of_entries=0,i;

	if(argc!=3){
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	file_extension=argv[1];
	char *directory_name=argv[2];

	no_of_entries=get_directory_entries(directory_name,&namelist);	

	display_entries(namelist,no_of_entries);

	//cleanup
	cleanup(namelist,no_of_entries);	
	exit(EXIT_SUCCESS);
}
int get_directory_entries(const char *directory_name,struct dirent ***namelist){

	int no_of_entries=x_scandir(directory_name,namelist,c_extn_filter,file_name_length_comparator);

	if(no_of_entries==-1){
		fprintf(stderr,"failed to read %s for files with extenison %s\n",directory_name,file_extension);
		exit(EXIT_FAILURE);
	}
	if(no_of_entries==0){
		fprintf(stderr,"File(s) with extenison %s not found in the specified directory\n",file_extension);
		exit(EXIT_FAILURE);
	}
	
	return no_of_entries;
}

int c_extn_filter(const struct dirent *dir_entry){
	
	char const *file_name=dir_entry->d_name;
	int file_extn_length=strlen(file_extension);
	if(strncmp(file_extension,&file_name[strlen(file_name)-file_extn_length],file_extn_length)==EQUAL){
		return NON_ZERO;
	}else
		return ZERO;
}

int file_name_length_comparator(const struct dirent ** dirent1,const struct dirent ** dirent2){

	int f_name_len1=strlen((*dirent1)->d_name);
	int f_name_len2=strlen((*dirent2)->d_name);

	if(f_name_len1 > f_name_len2)
		return 1;
	else if(f_name_len1 < f_name_len2)
		return -1;
	else
		return 0;

}

void print_usage(char *program_name)
{
	printf("Usage: %s <file extension> <directory name>\n",program_name);
}

void display_entries( struct dirent **namelist,int no_of_entries){
	int i;
	for(i=0;i<no_of_entries;i++){
		printf("%s\n",namelist[i]->d_name);
	}
}

void cleanup(struct dirent **namelist,int no_of_entries){
	int i;
	/*
	for(i=0;i<no_of_entries;i++){
		free(namelist[i]);
	}
	*/
	free(namelist);
}
