#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
 
int main () {
  struct dirent *dp;
  const char* dir_path=".";

  DIR *dir = opendir(dir_path);
  while ((dp=readdir(dir)) != NULL) {
    printf("%s\n", dp->d_name);
  }
  closedir(dir);
  return 0;
}
 
