#include "FileFilters.h"
#include <string.h>
#include <dirent.h>

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

int displayFileOnly(const struct dirent *entry){
  if(entry->d_type == DT_REG){
	return 1;
  }
  else{
	return 0;
  }
}

int displaySymLinks(const struct dirent *entry){
  if(entry->d_type == DT_LNK){
	return 1;
  }
  else{
	return 0;
  }
}
