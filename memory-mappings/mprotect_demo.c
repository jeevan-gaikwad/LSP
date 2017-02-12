#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
typedef int (*sample_fn_t)(void);

int main(int argc,char *argv[]){
	char code[]={0x55,0x48,0x89,0xe5,0xb8,0x0a,0x00,0x00,0x00,0x5d,0xc3};		
	char a='A';
	char b='B';
	char *ptr=&a;
	sample_fn_t fn;
	int ret=-1,error_code;
	unsigned long int pg_base_addr=(unsigned long int)(code)- 0xFFFFFFFFFFFFF000;
	printf("Ptr addrs:%p\n&b:%p \nPage base addr:%p code[1]:%p\n",ptr,&b,(void*)pg_base_addr,(void*)&code[1]);
	
	ret=mprotect((void *)code,PAGE_SIZE,PROT_EXEC|PROT_READ);
	error_code=errno;
	if(ret==0){
		printf("mprotect success!\n");
	}else{
		printf("mprotect failed! Cause:%s\n",strerror(error_code));
		exit(EXIT_FAILURE);
	}
	
	fn=(sample_fn_t)code;
	(*fn)();
	exit(EXIT_SUCCESS);
}

