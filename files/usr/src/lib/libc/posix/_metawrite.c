#include <lib.h>
#include <unistd.h>

PUBLIC int metawrite (int file_des, char *metadata, size_t nbytes)
{
	message m;

	m.m1_i1=file_des;
	m.m1_p1= (char *) metadata;
	m.m1_i2=nbytes;
	
	return(_syscall(VFS_PROC_NR,METAWRITE,&m));
}
