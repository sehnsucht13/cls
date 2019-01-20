#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

DIR *dirStream;
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

void listDirFiles(char *dirName, int (*f) (const struct dirent *entry)){
    numOfFiles = scandir(dirName, &dirFile, f, NULL);
    if (numOfFiles >=0){
        int currIndex = 0;
        for(currIndex; currIndex < numOfFiles; currIndex++){
            printf("%s\n", dirFile[currIndex]->d_name);
        }
    }
    else{
        printf("Error occured");
    }
}

void listCurrDir(){
    printf("Listing current directory\n");
    char *currWorkDir = getcwd(NULL, 0);
    listDirFiles(currWorkDir, NULL);
}

int main(int argc, char const *argv[])
{
    listCurrDir();
    return 0;
}

