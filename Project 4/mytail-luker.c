#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

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
   printf("Blocks: %d\t\n",fileStat.st_blocks);

   printf("Inode: %d\t",fileStat.st_ino);
   printf("Links: %d\n",fileStat.st_nlink);
   
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

   return 0;
}