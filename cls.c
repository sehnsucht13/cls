#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "FileFilters.h"


void printColor(char *str, int colorNumber){
    printf("\033[1;38;5;%dm %s\n", colorNumber, str);
}

char *concatFilePaths(const char *base, char *new) {
  int baseLen = strlen(base);
  int newLen = strlen(new);
  char *newPath = malloc((baseLen + newLen) * sizeof(char));
  newPath[0] = '\0';
  strcat(newPath, base);
  strcat(newPath, new);
  strcat(newPath, "/");
  return newPath;
}

void printDirFilesRec(const char *dirName, int (*f)(const struct dirent *entry)) {
  char *newDirPath;
struct dirent **dFile;
  int files = scandir(dirName, &dFile, f, NULL);
  printf("Here is the path %s\n", dirName);
  if (files >= 0) {
    for (int i = 0; i < files; ++i) {
      if (dFile[i]->d_type == DT_DIR){
		/* printf("Here is the folder name %s\n", dirFile[i]->d_name); */
		newDirPath = concatFilePaths(dirName, dFile[i]->d_name);
		printDirFilesRec(newDirPath, f);
      }
	  else {
		printf("Here is a file %s\n", dFile[i]->d_name);
      }
    }
  }
}


void printDirFilesNoRec(const char *dirName, int (*f) (const struct dirent *entry)){
    struct dirent **dirFile;
    int numOfFiles = scandir(dirName, &dirFile, f, NULL);
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
  struct dirent **dirFile;
  int numOfFiles = scandir(dirName, &dirFile, f, NULL);
  int currIndex;
  // Holds the stat for the current file
  struct stat file_stat;
  int status;
  char *destString;
  if (numOfFiles >= 0){
	for(currIndex = 0; currIndex < numOfFiles; currIndex++){
	  destString = malloc(strlen(dirName) + strlen(dirFile[currIndex]->d_name));
	  strcat(destString, dirName);
	  strcat(destString, dirFile[currIndex]->d_name);
	  status = stat(destString, &file_stat);
	  if(status != -1){
		printf("Here is the atime: %s\n", ctime(&file_stat.st_atime));
	  }
	  free(destString);
	}
  }
}

void listCurrDir(){
    char *currWorkDir = getcwd(NULL, 0);
    if(currWorkDir != NULL){
    printDirFilesNoRec(currWorkDir, NULL);
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
	  printDirFilesRec(argv[1], displayAlmostAll);
    }
    return 0;
}

