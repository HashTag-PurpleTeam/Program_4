#include "fs.h"
#include <assert.h>
#include <minix/vfsif.h>
#include "inode.h"
#include <stdio.h>
/*CHANGE*/
#include <lib.h>
#include <unistd.h>
#include <stdlib.h>
#include "buf.h"
#include "super.h"
/*END CHANGE*/

/*==================== fs_metawrite =================*/
PUBLIC int fs_metawrite()
{
	int file_des;
	char *metadata;
	size_t num_bytes;
	cp_grant_id_t gid;
	int inode_nr;
	dev_t dev;
	struct inode *ino;
	short scale;
	block_t b;
	struct super_block *sb;
	struct buf *buffer;
	int x, r;
	
	printf("in fs_metawrite (mfs)\n");
	
	gid = fs_m_in.REQ_GRANT;
	inode_nr = fs_m_in.REQ_INODE_NR;
	num_bytes = fs_m_in.REQ_NBYTES;

	ino = find_inode(fs_dev, (ino_t) inode_nr);
	scale = ino->i_sp->s_log_zone_size;
	
	if(ino->i_zone[9] == NO_ZONE) {
		printf("in if no_zone\n");
		ino->i_zone[9] = alloc_zone(ino->i_dev, ino->i_zone[9]);
		b = (block_t) ino->i_zone[9] << scale;
		printf("before get_block\n");
		buffer = get_block(ino->i_dev, b, NORMAL);
		zero_block(buffer);
	} else {
		b = (block_t) ino->i_zone[9] << scale;
		buffer = get_block(ino->i_dev, b, NORMAL);
	}

	printf("before safecopyfrom\n");
	r = sys_safecopyfrom(VFS_PROC_NR, gid, 0, 
		(vir_bytes) buffer->b_data, num_bytes, D);

	buffer->b_dirt = DIRTY;

	printf("METADATA: %s\n", buffer->b_data);

	/*
	file_des = fs_m_in.m4_l1;
	metadata = (char *) fs_m_in.m4_l2;
	num_bytes = fs_m_in.m4_l3;
	inode_nr = fs_m_in.m4_l4;
	dev = fs_m_in.m4_l5;
	
	
	strcpy(buffer->b_data, metadata);
	printf("file metadata: %s\n", buffer->b_data);
	
	*/
	
	return OK;
}

/*======================= fs_metaread  ====================*/
PUBLIC int fs_metaread()
{
	int file_des;
	int inode_nr;
	dev_t dev;
	struct inode *ino;	
	short scale;
	block_t b;
	struct buf *buffer;	

	file_des = fs_m_in.m4_l1;
	inode_nr = fs_m_in.m4_l2;
	dev = fs_m_in.m4_l3;

	ino = find_inode(dev, inode_nr);
	scale = ino->i_sp->s_log_zone_size;

	if(ino->i_zone[9] != NO_ZONE) {
		b = (block_t) ino->i_zone[9] << scale;
		buffer = get_block(ino->i_dev, b, NORMAL);
	}
	
	printf("METADATA: %s\n", buffer->b_data);
	return OK;
}

/*===========================================================================*
 *				fs_sync					     *
 *===========================================================================*/
PUBLIC int fs_sync()
{
/* Perform the sync() system call.  Flush all the tables. 
 * The order in which the various tables are flushed is critical.  The
 * blocks must be flushed last, since rw_inode() leaves its results in
 * the block cache.
 */
  struct inode *rip;
  struct buf *bp;

  assert(nr_bufs > 0);
  assert(buf);

  /* Write all the dirty inodes to the disk. */
  for(rip = &inode[0]; rip < &inode[NR_INODES]; rip++)
	  if(rip->i_count > 0 && rip->i_dirt == DIRTY) rw_inode(rip, WRITING);

  /* Write all the dirty blocks to the disk, one drive at a time. */
  for(bp = &buf[0]; bp < &buf[nr_bufs]; bp++)
	  if(bp->b_dev != NO_DEV && bp->b_dirt == DIRTY) 
		  flushall(bp->b_dev);

  return(OK);		/* sync() can't fail */
}


/*===========================================================================*
 *				fs_flush				     *
 *===========================================================================*/
PUBLIC int fs_flush()
{
/* Flush the blocks of a device from the cache after writing any dirty blocks
 * to disk.
 */
  dev_t dev = (dev_t) fs_m_in.REQ_DEV;
  if(dev == fs_dev) return(EBUSY);
 
  flushall(dev);
  invalidate(dev);
  
  return(OK);
}

PUBLIC int say_hello()
{
	printf("\HELLO, RYAN!!!\n");
	return(OK);
}

