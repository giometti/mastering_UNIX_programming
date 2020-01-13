#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#ifdef __linux__
#include <sys/sysmacros.h>
#endif

int main(int argc, char *argv[])
{
	struct stat buf;
	int ret;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return -1;
	}

	ret = lstat(argv[1], &buf);
	if (ret < 0) {
		perror("lstat");
		return -1;
	}

	printf("File name:                %s\n", argv[1]);

#ifdef major
        printf("ID of containing device:  [%lx,%lx]\n",
		(long) major(buf.st_dev), (long) minor(buf.st_dev));
#endif

	printf("File type:                ");
        switch (buf.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");
        }

#ifdef major
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		printf("special file major/minor: [%lu,%lu]\n",
			(long) major(buf.st_rdev),
			(long) minor(buf.st_rdev));
#endif

        printf("I-node number:            %ld\n", (long) buf.st_ino);
        printf("Mode:                     %lo (octal)\n",
					(unsigned long) buf.st_mode);
        printf("Link count:               %ld\n", (long) buf.st_nlink);
        printf("Ownership:                UID=%ld GID=%ld\n",
		(long) buf.st_uid, (long) buf.st_gid);
	printf("Preferred I/O block size: %ld bytes\n",
					(long) buf.st_blksize);
	printf("File size:                %lld bytes\n",
					(long long) buf.st_size);
	printf("Blocks allocated:         %lld\n",
					(long long) buf.st_blocks);

	printf("Last status change:       %s", ctime(&buf.st_ctime));
	printf("Last file access:         %s", ctime(&buf.st_atime));
	printf("Last file modification:   %s", ctime(&buf.st_mtime));

	return 0;
}
