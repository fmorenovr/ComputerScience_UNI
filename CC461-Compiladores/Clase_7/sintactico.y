%{

/******************** 
  Declaraciones en C
**********************/

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  extern int yylex(void);
  extern char *yytext;
  extern int linea;
  extern FILE *yyin;
  void yyerror(char *s);
%}

/************************
  Declaraciones de Bison
*************************/

/*  Especifica la coleccion completa de tipos de datos para poder usar 
   varios tipos de datos en los terminales y no terminales*/
%union
{
  float real;
}
/* Indica la produccion con la que inicia nuestra gramatica*/
%start Exp_l

/* Especificacion de termines, podemos especificar tambien su tipo  */
%token <real> NUMERO
%token MAS
%token MENOS
%token IGUAL
%token PTOCOMA
%token POR
%token DIV
%token PAA
%token PAC

/* No Terminales, que tambien podemos especificar su tipo */
%type <real> Exp
%type <real> Calc
%type <real> Exp_l
/*  Definimos las precedencias de menor a mayor */
%left MAS MENOS
%left POR DIV

%%
/**********************
  Reglas Gramaticales
***********************/


Exp_l:		Exp_l Calc   
			|Calc
			;
Calc	 :  Exp PTOCOMA {printf ("%4.1f\n",$1)}		  
		  ;
/* con el simbolo de $$ asignamos el valor semantico de toda
  la accion de la derecha y se la asignamos al no terminal de
   la izquierda, en la siguiente regla, se la asigna a Exp.
	Para poder acceder al valor de los terminales y no terminales del lado
   derecho usamos el simbolo $ y le concatenamos un numero que representa
   la posicion en la que se encuentra es decir si tenemos

  A --> B NUMERO C

  Si queremos usar le valor que tiene el no terminal B usamos $1, si queremos
  usar el valor que tiene NUMERO usamos $2 y asi sucesivamente.


*/
Exp : 		NUMERO {$$=$1;}
			|Exp MAS Exp {$$=$1+$3;}
			|Exp MENOS Exp {$$=$1-$3;}
			|Exp POR Exp {$$=$1*$3;}
			|Exp DIV Exp {$$=$1/$3;} 
			|PAA Exp PAC {$$=$2;}
			;
%%
/********************
  Codigo C Adicional
**********************/
void yyerror(char *s)
{
  printf("Error sintactico %s",s);
}

int main(int argc,char **argv)
{
  if (argc>1)
	yyin=fopen(argv[1],"rt");
  else
	yyin=stdin;

  yyparse();
  return 0;
}