#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>

using namespace std;

int main(){
 
 int key, xor_encrypt;
 string cadena;
 
 cout << "Introduzca la llave para encriptar (1-255): ";
 cin >> key;

 ifstream fichero("mensaje.txt",ifstream::in);
 ofstream cifrado("mensaje_encriptado.txt",ofstream::out);
 
 while(getline(fichero,cadena)){
  
  for(int i=0; i<cadena.length(); i++){
    xor_encrypt = (int)(cadena[i])^(key); //Aplicamos XOR a cada caracter con la "key" que introdujimos convirtiendolo a su valor en ascii (int)
    cifrado << (char) xor_encrypt;  //Escribimos en el archivo el resultado del xor pero convirtiendolo en char. 
  }
  cifrado << endl; //Escribimos un salto de linea
 }
 return 0;
}
