#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

PUBLIC int metaread2(int file_des, int inode_nr, dev_t dev)
{
	message m;
	
	m.m4_l1 = file_des;
	m.m4_l2 = inode_nr;
	m.m4_l3 = dev;
	
	return(_syscall(MFS_PROC_NR, 29, &m));
}
