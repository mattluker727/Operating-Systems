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

void search(char cwd[256]);

int main(int argc, char **argv){

   //Get cwd
   char cwd[256];

   if(argc == 2){
      //Get cwd from commandline
      strncpy(cwd, argv[1], 100);
      printf("cwd: %s\n", cwd);
   }
   else{
      //Use current dir as cwd
      if (getcwd(cwd, sizeof(cwd)) == NULL)
         printf("getcwd() error");
      else
         printf("cwd: %s\n", cwd);
   }

   //Initial ls and search on root folder
   search(cwd);

   printf("\nEnd of cwd: %s\n", cwd);
   return 0;
}

void search(char newWD[256]){

   //Open and read newWD
   DIR *myDir;
   struct dirent *readmyDir;

   myDir = opendir (newWD);
   if (myDir == NULL) {
      printf ("Can't open '%s'\n", newWD);
   }
   
   //Print ls
   while ((readmyDir = readdir(myDir)) != NULL) {
      //check if file is dir
      struct stat fileStat;

      char newCWD[256] = "";
      strcat(newCWD,  newWD);
      strcat(newCWD,  "/");
      strcat(newCWD,  readmyDir->d_name);
      
      if(stat(newCWD, &fileStat) < 0)    //change this line
        continue;
      
      if(!strcmp(readmyDir->d_name, "..") || !strcmp(readmyDir->d_name, ".")){
         continue;
      }
      
      // switch (fileStat.st_mode & S_IFMT) {
      //    case S_IFDIR:  printf("directory\n");               break;
      //    case S_IFREG:  printf("regular file\n");            break;
      //    default:       printf("unknown?\n");                break;
      // }
      
      if (!S_ISREG(fileStat.st_mode)){
         printf ("\n\nFound dir: '%s'\n", readmyDir->d_name);

         search(newCWD);
         printf ("End of dir: '%s'\n\n", readmyDir->d_name);
      }
      else{
         printf ("%s\t\t", readmyDir->d_name);
      }
   }

   closedir (myDir);
}