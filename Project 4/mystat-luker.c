#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>

int main(int argc, char **argv){

   if(argc != 2){
      printf("Input file needed\n");
   }

   struct stat fileStat;
   if(stat(argv[1], &fileStat) < 0)    
      return 1;
 
   //Print info from struct
   printf("  File: %s\n", argv[1]);
   printf("  Size: %d\t\t",fileStat.st_size);
   printf("Blocks: %d\t",fileStat.st_blocks);
   printf("IO Block: %d\t",fileStat.st_blksize);

   switch (fileStat.st_mode & S_IFMT) {
   case S_IFBLK:  printf("block device\n");            break;
   case S_IFCHR:  printf("character device\n");        break;
   case S_IFDIR:  printf("directory\n");               break;
   case S_IFIFO:  printf("FIFO/pipe\n");               break;
   case S_IFLNK:  printf("symlink\n");                 break;
   case S_IFREG:  printf("regular file\n");            break;
   case S_IFSOCK: printf("socket\n");                  break;
   default:       printf("unknown?\n");                break;
   }

   //printf("Device: [%lx,%lx]/%d\t",
   //(long) major(fileStat.st_dev), (long) minor(fileStat.st_dev), fileStat.st_dev);
   printf("Device: /%d\t",fileStat.st_dev);
   printf("Inode: %d\t",fileStat.st_ino);
   printf("Links: %d\n",fileStat.st_nlink);
   
   //printf("Mode: %d\n",fileStat.st_mode);
   // printf("Mode: %d\n",fileStat.st_);

   printf("Permissions:\t(");
   printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
   printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
   printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
   printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
   printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
   printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
   printf(")\t");

   struct group *grp;
   struct passwd *pwd;
   
   grp = getgrgid(fileStat.st_gid);
   pwd = getpwuid(fileStat.st_uid);

   //printf("Uid: ( %d/\t%s)\t",fileStat.st_uid, pwd->pw_name);
   //printf("Gid: ( %d/\t%s)\n",fileStat.st_gid, grp->gr_name);
   
   printf("\nAccess: %s", ctime(&fileStat.st_atime));
   printf("Modify: %s", ctime(&fileStat.st_mtime));
   printf("Change: %s", ctime(&fileStat.st_ctime));

   printf("\n");

   //printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

   return 0;
}
