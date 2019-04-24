#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>

int main(int argc, char **argv){

   //Get number of lines to read from file
   int numLines;

   if(argc >= 2){
      numLines = atoi(argv[1] + 1); //remove "-" from "-n"
      //printf("numLines: %d\n", numLines);
   }

   //Get file
   char file[256];

   if(argc == 3){
      //Get file from commandline
      strncpy(file, argv[2], 100);
      //printf("file: %s\n", file);
   }
   else{
      printf("Input file needed\n");
      return 1;
   }
   
   //Get file stats
   struct stat fileStat;
   if(stat(file, &fileStat) < 0){
      printf("Input file error\n");
      return 1;
	}
	
   const int fileSize = fileStat.st_size;

   //Open file
   int fd = open(file, O_RDONLY);
   
   //Define max line size and buffer to read into from file
   static const long maxLen = 9999 + 1;
   char buff[maxLen + 1];
	
   lseek(fd, -maxLen, SEEK_END);
   ssize_t len = read(fd, buff, maxLen);
   buff[len] = '\0';
   
   //Find last line
   char *lastLine = strrchr(buff, '\n') + 1;
   char *tail = lastLine;
   int count = numLines;
		
   //Move backward count from end of file
   while(count != -1){
      tail--;
      //printf("tail:%c\n", tail[0]);

      if (tail[0] == '\n') count--;
   }
   
   tail++; //remove extra newline char

   //Print last numLines of files
   printf("Last %d lines in file:\n%s", numLines, tail);
   
   close(fd);

   return 0;
}