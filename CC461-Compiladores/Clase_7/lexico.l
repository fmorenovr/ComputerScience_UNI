/***************** 
  Definiciones
	Se colocan las cabeceras, variables y expresiones regulares

********************/


%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "sintactico.tab.h"
  int linea=0;
%}
/*
Creamos todas las expresiones regulares

Creamos la definicion llamada DIGITO, podemos acceder esta definicion
usando {DIGITO}*/
DIGITO [0-9]
NUMERO {DIGITO}+("."{DIGITO}+)?


%%
 /***************
   Reglas
 *****************/


 /* Creamos las reglas que reconoceran las cadenas que acepte
  nuestro scanner y retornaremos el token a bison con la
  funcion return. */
{NUMERO} {yylval.real=atof(yytext); return(NUMERO);}
"=" 	{return(IGUAL);}
"+" 	{return(MAS);}
"-" 	{return(MENOS);}
";" 	{return(PTOCOMA);}
"*" 	{return(POR);}
"/" 	{return(DIV);}
"(" 	{return(PAA);}
")" 	{return(PAC);}
"\n" 	{linea++;}
[\t\r\f] {}
" "		{}
 /* Si en nuestra entrada tiene algun caracter que no pertenece a 
   las reglas anteriores, se genera un error lexico */

.		{printf("Error lexico en linea %d",linea);}
%%
/* 
Codigo de Usuario

Aqui podemos realizar otras funciones, como por ejemplo ingresar
simbolos a nuestra tabal de simbolos o cualquier otra accione
del usuario.  
Todo lo que el usuario coloque en esta seccion se copiara al
archvi lex.yy.c tal y como esta.
*/