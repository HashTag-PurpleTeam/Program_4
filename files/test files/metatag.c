#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main (int argc, char **argv)
{
	char *filename, *metadata;
	int file_des;
	FILE *fp;

	if(argc!=3){
		fprintf(stderr, "ERROR: incorrect arguments\n");
		exit(1);
	}

	filename = argv[1];
	fp = fopen(filename, "r");
	if(fp == NULL) {
		fp = fopen(filename, "w+b");
	}
	fclose(fp);
	
	file_des = open(filename, O_RDWR);
	metadata = argv[2];
	
	metawrite(file_des, metadata, strlen(metadata));
	return 0;
}
