#include <sys/stat.h>
#include <stdio.h>

// int stat(const char *restrict pathname, struct stat *restrict statbuf);
// As funções stat retornam informação sobre um arquivo, salvando essa info no buffer "statbuf"
// lstat() é idêntico a stat, exceto que se "pathname" for um link simbólico, são retornadas infos sobre o próprio link
// fstat() é idêntico a stat, exceto que o arquivo cujas infos serão retornadas é indicado por um file descriptor


int	main(void)
{
	struct stat	buffer;
	int		ret;

	ret = stat("./diretorio/test.txt", &buffer); // retorna 0 em caso de sucesso, -1 em falha
	printf("test.txt - type/mode: %d size: %d\n", buffer.st_mode, buffer.st_size);
	ret = stat("./diretorio/arquivo1", &buffer);
	printf("arquivo1 - type/mode: %d size: %d\n", buffer.st_mode, buffer.st_size);
	return (0);
}

// struct stat {
    // dev_t     st_dev;         /* ID of device containing file */
    // ino_t     st_ino;         /* Inode number */
    // mode_t    st_mode;        /* File type and mode */
    // nlink_t   st_nlink;       /* Number of hard links */
    // uid_t     st_uid;         /* User ID of owner */
    // gid_t     st_gid;         /* Group ID of owner */
    // dev_t     st_rdev;        /* Device ID (if special file) */
    // off_t     st_size;        /* Total size, in bytes */
    // blksize_t st_blksize;     /* Block size for filesystem I/O */
    // // blkcnt_t  st_blocks;      /* Number of 512B blocks allocated 
    // /* Since Linux 2.6, the kernel supports nanosecond
    //    precision for the following timestamp fields.
    // //    For the details before Linux 2.6, see NOTES. 
    // struct timespec st_atim;  /* Time of last access */
    // struct timespec st_mtim;  /* Time of last modification */
    // // struct timespec st_ctim;  /* Time of last status change 
// };