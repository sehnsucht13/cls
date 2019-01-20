#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "FileFilters.h"

struct dirent **dirFile;
int numOfFiles;


void printColor(char *str, int colorNumber){
    printf("\033[1;38;5;%dm %s\n", colorNumber, str);
}

void printDirFilesNoRec(const char *dirName, int (*f) (const struct dirent *entry)){
    numOfFiles = scandir(dirName, &dirFile, f, NULL);
    int currIndex;
    if (numOfFiles >=0){
        for(currIndex = 0; currIndex < numOfFiles; currIndex++){
            if(dirFile[currIndex]->d_type == DT_DIR){
                printColor(dirFile[currIndex]->d_name, 52);
            }
            else{
                printColor(dirFile[currIndex]->d_name, 197);
            }
        }
    }
    else{
        printf("Error occured");
    }
}

void printFilesStat(const char *dirName, int (*f) (const struct dirent *entry)){
  numOfFiles = scandir(dirName, &dirFile, f, NULL);
  int currIndex;
  // Holds the stat for the current file
  struct stat file_stat;
  int status;
  char *destString;
  if (numOfFiles >= 0){
	for(currIndex = 0; currIndex < numOfFiles; currIndex++){
	  destString = malloc(strlen(dirName) + 1 + strlen(dirFile[currIndex]->d_name));
	  strcat(destString, dirName);
	  strcat(destString, "/");
	  strcat(destString, dirFile[currIndex]->d_name);
	  status = stat(destString, &file_stat);
	  if(status != -1){
		printf("Here is the atime: %s\n", ctime(&file_stat.st_atime));
	  }
	  printf("destSTring: %s\n", destString);
	  free(destString);
	}
  }
}

void listCurrDir(){
    char *currWorkDir = getcwd(NULL, 0);
    if(currWorkDir != NULL){
    /* printDirFilesNoRec(currWorkDir, NULL); */
	  printFilesStat(currWorkDir, NULL);
    }
    else{
        printf("Error occured while displaying current directory\n");
    }
}

void listDir(const char *dirName){
    printFilesStat(dirName, NULL);
}


int main(int argc, char const *argv[])
{
    if(argc == 1){
        listCurrDir();
    }
    else{
        listDir(argv[1]);
    }
    return 0;
}

