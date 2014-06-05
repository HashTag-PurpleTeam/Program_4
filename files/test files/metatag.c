#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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
	file_des = open(filename, O_RDWR);
	fp = fopen(filename, "r+");

	metadata = argv[2];
	
	metawrite(file_des, metadata, sizeof(metadata));
	return 0;
}
