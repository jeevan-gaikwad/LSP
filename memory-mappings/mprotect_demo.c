#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

typedef int (*sample_fn_t)(void);

int main(int argc,char *argv[]){
	char code[]={0x55,0x48,0x89,0xe5,0xb8,0x0d,0x00,0x00,0x00,0x5d,0xc3};		
	sample_fn_t fn;
	int ret=-1,error_code;

	void *mapped_addr=mmap(NULL,PAGE_SIZE,PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
	if(mapped_addr==MAP_FAILED){
		printf("mmap failed\n");
		exit(EXIT_FAILURE);
	}else
		printf("mmap success\n");

	void *ret_val_addr=memcpy(mapped_addr,(void*)code,sizeof(code));
	if(ret_val_addr!=NULL){
		printf("memcpy success!\n");
	}else{
		printf("mcpy failed! Cause:%s\n",strerror(error_code));
		exit(EXIT_FAILURE);
	}
	
	//on memcpy success, ret_val_addr and mapped_addr should be same
	ret=mprotect(mapped_addr,PAGE_SIZE,PROT_EXEC|PROT_READ);	
	if(ret==0){
		printf("mprotect success!\n");
	}else{
		printf("mprotect failed! Cause:%s\n",strerror(error_code));
		exit(EXIT_FAILURE);
	}
	
	fn=(sample_fn_t)mapped_addr;
	printf("Function called with ret val:%d\n",(*fn)());

	exit(EXIT_SUCCESS);
}

