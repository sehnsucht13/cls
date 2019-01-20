#include "FileFilters.h"
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>

char *filterPattern = "*.c";

// Display all files without . or ..
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

// Display all files including . and ..
int displayAll(const struct dirent *entry){
    return 1;
}

// Display directories only
int displayDirsOnly(const struct dirent *entry){
    if(entry->d_type == DT_DIR){
        return 1;
    }
    else{
        return 0;
    }
}

// Display files only(If the file system in use supports it)
int displayFileOnly(const struct dirent *entry){
  if(entry->d_type == DT_REG){
	return 1;
  }
  else{
	return 0;
  }
}

// Display files which are sym linked
int displaySymLinks(const struct dirent *entry){
  if(entry->d_type == DT_LNK){
	return 1;
  }
  else{
	return 0;
  }
}
