#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct dirent **dirFile;
int numOfFiles;

int displayUpperDirs(const struct dirent *entry){
    char *sDot = ".";
    char *dDot = "..";
    if(strcmp(sDot, entry->d_name) == 0 || strcmp(dDot, entry->d_name) == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int displayAllFiles(const struct dirent *entry){
    return 1;
}

void printColor(char *str, int colorNumber){
    printf("\033[1;38;5;%dm %s\n", colorNumber, str);
}

void printDirFiles(char *dirName, int (*f) (const struct dirent *entry), int recursive){
    numOfFiles = scandir(dirName, &dirFile, f, NULL);
    int currIndex = 0;
    if (numOfFiles >=0 && recursive == 0){
        for(currIndex; currIndex < numOfFiles; currIndex++){
                printColor(dirFile[currIndex]->d_name, 197);
        }
    }
    else{
        printf("Error occured");
    }
}

void listCurrDir(){
    char *currWorkDir = getcwd(NULL, 0);
    if(currWorkDir != NULL){
    printDirFiles(currWorkDir, NULL, 0);
    }
    else{
        printf("Error occured while displaying current directory\n");
    }
}

void listDir(const char *dirName){
    printDirFiles(dirName, NULL, 0);
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

