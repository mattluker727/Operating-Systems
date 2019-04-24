#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv){

   //Check if showStats
   bool showStats = false;

   if(argc >= 2){
      if (strcmp("-l", argv[1]) == 0){
         showStats = true;
      }
   }
	
   //Get cwd
   char cwd[256];

   if(argc == 3){
      //Get cwd from commandline
      strncpy(cwd, argv[2], 100);
      printf("cwd: %s\n", cwd);
   }
   else{
      //Use current dir as cwd
      if (getcwd(cwd, sizeof(cwd)) == NULL)
         printf("getcwd() error");
      else
         printf("cwd: %s\n", cwd);
   }

   //Open and read cwd
   DIR *myDir;
   struct dirent *readmyDir;
   
   myDir = opendir (cwd);
   if (myDir == NULL) {
      printf ("Can't open '%s'\n", cwd);
      return 1;
   }
   
   //Print ls
   while ((readmyDir = readdir(myDir)) != NULL) {
			
      char newCWD[256] = "";
      strcat(newCWD,  cwd);
      strcat(newCWD,  "/");
      strcat(newCWD,  readmyDir->d_name);
			
      if (!showStats){
         printf ("%s\t\t", readmyDir->d_name);
      }
      //Print cwd stats if showStats   
      else {
         struct stat fileStat;

         //skip if file is dir
         if(stat(newCWD, &fileStat) < 0){
            continue;
         }

         //Print info from struct
         printf("\n");
         
         printf("  File: %s\n", readmyDir->d_name);
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

         printf("Device: /%d\t",fileStat.st_dev);
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
         
         printf("\nAccess: %s", ctime(&fileStat.st_atime));
         printf("Modify: %s", ctime(&fileStat.st_mtime));
         printf("Change: %s", ctime(&fileStat.st_ctime));

      }
   }

   printf ("\n");
   closedir (myDir);
   
   return 0;
}