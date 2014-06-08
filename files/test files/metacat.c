#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char **argv)
{
	char* filename;
	char* metadata;
	int file_des;	

	if(argc != 2){
		fprintf(stderr, "ERROR: incorrect arguments\n");
		exit(1);	
	}
	
	filename = argv[1];	
	/* set file descriptor */
	file_des = open(filename, O_RDWR);
	
	metaread(file_des);
	return 0;	
}
