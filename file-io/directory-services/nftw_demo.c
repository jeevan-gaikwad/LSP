#define _XOPEN_SOURCE 500
#include<ftw.h>
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<errno.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

void print_usage(char *program_name);
void print_version();
int file_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

char recursive_flag=FALSE;

int main(int argc, char *argv[]){
	char *program_name=argv[0];
	int optind=0;
	int ret,flags=0;
	char option_specified=FALSE;
	char *directory_name=NULL;
	
	if(argc<2){
	    directory_name=(char*)calloc(1,10);
	    strcpy(directory_name,".");
		//directory_name=".";
	}

	static struct option long_options[]={
		{"version"  ,no_argument,NULL,'v'},
		{"help"     ,no_argument,NULL,'h'},
		{"recursive",no_argument,NULL,'r'},
		{0          ,0          ,0   ,0  }
	};
	
	while((ret=getopt_long(argc,argv,"hvr:",long_options,&optind))!=-1){
		//option_specified=TRUE;
		switch(ret){
			case 'h':
					print_usage(program_name);
					exit(EXIT_SUCCESS);
					break;
			case 'v':
					print_version();
					exit(EXIT_SUCCESS);
					break;
			case 'r':
					recursive_flag=TRUE;
					directory_name=optarg;
					break;
			default:
					fprintf(stderr,"Invalid option %c\n",ret);
					print_usage(program_name);
					exit(EXIT_FAILURE);
		}
	}

	if(recursive_flag==FALSE&&directory_name==NULL){
		directory_name=argv[1];
	}
		printf("Directory:%s\n",directory_name);
		flags|=FTW_ACTIONRETVAL;
	if(nftw(directory_name,file_callback,20,flags)==-1){
		fprintf(stderr,"nftw failed. Error:%s",strerror(errno));
	}

	exit(EXIT_SUCCESS);
}
void print_usage(char *program_name){
	printf("Usage: %s -h/--help :For options available with %s\n \
			-v/--version :For program version info\n\
			-r/--recursive :To display file list of all subdirectories\n\
			<directory name> default is current directory\n", program_name,program_name); 
	
}

void print_version(){
	printf("v0.1\n");
}

int file_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
    
	if(typeflag==FTW_D && recursive_flag==TRUE){
		printf("FC: DIR %s\n",fpath);
	}
	else if(typeflag==FTW_D&& strcmp(fpath,".")!=0) //Except current directory, skip other directories if -r is absent
	    return FTW_SKIP_SUBTREE;
	else
		printf("FC: %s\n",fpath);

	return FTW_CONTINUE;
}
