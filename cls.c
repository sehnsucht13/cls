#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct dirent **dirFile;
int numOfFiles;

int displayAlmostAll(const struct dirent *entry){
    char *sDot = ".";
    char *dDot = "..";
    if(strcmp(sDot, entry->d_name) == 0 || strcmp(dDot, entry->d_name) == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int displayAll(const struct dirent *entry){
    return 1;
}

int displayDirsOnly(const struct dirent *entry){
    if(entry->d_type == DT_DIR){
        return 1;
    }
    else{
        return 0;
    }
}

void printColor(char *str, int colorNumber){
    printf("\033[1;38;5;%dm %s\n", colorNumber, str);
}

void printDirFiles(const char *dirName, int (*f) (const struct dirent *entry), int recursive){
    numOfFiles = scandir(dirName, &dirFile, f, NULL);
    int currIndex = 0;
    if (numOfFiles >=0){
        for(currIndex; currIndex < numOfFiles; currIndex++){
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
    printDirFiles(dirName, NULL , 0);
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

