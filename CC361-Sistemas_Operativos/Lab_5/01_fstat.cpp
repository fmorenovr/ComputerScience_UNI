#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
  struct stat info;
  if(fstat(STDIN_FILENO, &info) < 0){
    perror("Error obteniendo info de standar input");
    return -1;
  }
  cout << "Standard input pertenece a " << info.st_uid << endl;
  cout << "fue modificada últimamente el " << ctime(&info.st_mtime);
  if(S_ISREG(info.st_mode)){
    cout << "Tiene tamaño de " << info.st_size << "-byte." << endl;
  } else {
    cout << "No es un archivo regular." << endl;
  }
  return 0;
}

