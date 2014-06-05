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
	file_des = open(filename, O_RDWR);
	
	metaread(file_des);
	/*printf("Metadata = %s\n", metadata);*/
	return 0;	
}
