#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

PUBLIC int metawrite2(int file_des, char *metadata, size_t nbytes, int 
  inode_nr, dev_t dev){
	message m;
	char* word = metadata;

	m.m4_l1 = file_des;
	m.m4_l2 = (long) word;
	m.m4_l3 = nbytes;
	m.m4_l4 = inode_nr;
	m.m4_l5 = dev;
	
	printf("in metawrite2 lib func\n");
	return(_syscall(MFS_PROC_NR, 0, &m));	
}
