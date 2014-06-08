#include <lib.h>
#include <unistd.h>

PUBLIC int metaread (int file_des)
{
	message m;
	
	m.m1_i1=file_des;
	
	return(_syscall(VFS_PROC_NR, METAREAD, &m));
}
