#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv){

   //Check if showStats
   bool showStats = false;

   if(argc >= 2){
      if (strcmp("-1", argv[1]) == 0){
         showStats = true;
         printf("showStats\n");
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
      if (!showStats){
         printf ("%s\t\t", readmyDir->d_name);
      }
      //Print cwd stats if showStats   
      else {
         printf("\n");

         struct stat fileStat;
         if(stat(readmyDir->d_name, &fileStat) < 0){
            printf("stat() error\n");
            return 1;
         }
         //Print info from struct
         printf("  File: %s\n", readmyDir->d_name);
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
         printf(")\t\n");
      }
   }

   printf ("\n");
   closedir (myDir);

   return 0;
}