#include <dirent.h>

int displayAlmostAll(const struct dirent *entry);
int displayAll(const struct dirent *entry);
int displayDirsOnly(const struct dirent *entry);
int displayFileOnly(const struct dirent *entry);
int displaySymLinks(const struct dirent *entry);
int displayPatternMatch(const struct dirent *entry);
