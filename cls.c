#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

DIR *dirStream;
struct dirent **dirFile;
int numOfFiles;

int displayDotFiles(const struct dirent *entry){
    char *sDot = ".";
    char *dDot = "..";

}
void listDir(char *dirName){
    numOfFiles = scandir(dirName, &dirFile, NULL, NULL);
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
    listDir(currWorkDir);

}

int main(int argc, char const *argv[])
{
    listCurrDir();
    return 0;
}

