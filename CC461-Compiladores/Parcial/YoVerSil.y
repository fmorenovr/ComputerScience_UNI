%{
#include<stdio.h>
#include<string.h>
#include<math.h>
#define YYSTYPE double
char lexema[255];
int linea = 1;
int printLine=0;
void yyerror(char *);
int reservedWord(char [],int);
%}

%token ID NUM
%token SUMA RESTA MULTI DIV POT
%token PAR1 PAR2 LLAVE1 LLAVE2 PUNTOCOMA COMA
%token CLASE PUBLICA PRIVADA RETORNA PRINCIPAL
%token ENTERO FLOTANTE BOOL DOBLE CARACTER CADENA VACIO
%token SI SINO MENOR MAYOR IGUAL VERDADERO FALSO AND OR
%token METODO NUEVA
%token MIENTRAS PARA

%start program

%%
program: clases program      |
         funcionMain program |
         evalExpr program    |
         %empty
;
clases: CLASE publico ID LLAVE1 lineas LLAVE2
;
lineas: publico declaraciones lineas |
        metodos lineas               |
        funciones lineas             |
        %empty
;
funcionMain: publico tipo PRINCIPAL PAR1 PAR2 LLAVE1 lineas LLAVE2
;
metodos: publico tipo ID PAR1 variables PAR2 LLAVE1 instruciones retorna LLAVE2
;
funciones: tipo ID PAR1 variables PAR2 LLAVE1 instruciones retorna LLAVE2
;
llamaMetodo: ID PAR1 declaraVariable PAR2
;
declaraVariable: declaraVar |
                 %empty
;
declaraVar: ID COMA declaraVar |
            ID
;
variables: vars   |
           %empty
;
vars: tipo ID COMA variables |
      tipo ID
;
declaraciones:  tipo ID PUNTOCOMA                           |
                tipo ID IGUAL var operacion var PUNTOCOMA  |
                tipo ID IGUAL NUEVA ID PAR1 PAR2 PUNTOCOMA  |
                tipo ID IGUAL var ':' llamaMetodo PUNTOCOMA
;
retorna: RETORNA ID PUNTOCOMA
;
asigna: var IGUAL var operacion var PUNTOCOMA     |
        var IGUAL var ':' llamaMetodo PUNTOCOMA
;

condicional: SI PAR1 silogismo PAR2 LLAVE1 instruciones LLAVE2 |
             SI PAR1 silogismo PAR2 LLAVE1 instruciones LLAVE2 SINO LLAVE1 instruciones LLAVE2
;
silogismo: expresion AND silogismo |
           expresion OR silogismo  |
           expresion
;
expresion: var comparacion var |
           var
;
comparacion: MAYOR IGUAL |
             MENOR IGUAL |
             IGUAL IGUAL |
             MENOR       |
             MAYOR       |
             MENOR MAYOR
;
bucle: MIENTRAS PAR1 silogismo PAR2 LLAVE1 instruciones LLAVE2
;
instruciones: declaraciones instruciones |
              asigna instruciones        |
              condicional instruciones   |
              bucle instruciones         |
              %empty
;
publico: PUBLICA |
         PRIVADA
;
tipo: ENTERO   |
      FLOTANTE |
      BOOL     |
      DOBLE    |
      CARACTER |
      CADENA   |
      VACIO    |
      ID
;
var: NUM                         |
     ID                          |
     bool                        |
     METODO PAR1 variables2 PAR2
;
bool: VERDADERO |
      FALSO
;
variables2: var COMA variables2  |
            %empty
;
operacion: SUMA  |
           RESTA |
           MULTI |
           DIV   |
           POT   |
           IGUAL
;
evalExpr: expr PUNTOCOMA { printf("=> %g\n",$1); }
;
expr: expr SUMA term   {$$ = $1 + $3;}|
      expr RESTA term {$$ = $1 - $3;}|
      term {$$ = $1;}
;
term: term MULTI term2 {$$ = $1 * $3;}|
      term DIV term2  {$$ = $1 / $3;}|
      term2 {$$ = $1;}
;
term2: term2 POT term3 {$$ = pow($1,$3);}|
       term3 {$$ = $1;}
;
term3: PAR1 expr PAR2 {$$ = $2;}       |
       RESTA PAR1 expr PAR2 {$$ = -$3;}|
       dig {$$=$1;}
;   
dig: dig1    {$$=$1;} |
     SUMA dig1 {$$=$1;}|
     RESTA dig1 {$$=-$1;}
;
dig1: NUM {$$=$1;}
;
%%

void yyerror(char *mgs){
	printf("\n---> error de cadena: %s en la linea: %i\n",mgs,linea);
}

int reservedWord(char lexema[],int s){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcasecmp(lexema,"principal") ==0 )return PRINCIPAL;
  if(strcasecmp(lexema,"clase") ==0 )return CLASE;
  if(strcasecmp(lexema,"publica") ==0 )return PUBLICA;
  if(strcasecmp(lexema,"privada") ==0 )return PRIVADA;
  if(strcasecmp(lexema,"Entero") ==0 )return ENTERO;
  if(strcasecmp(lexema,"Flotante") ==0 )return FLOTANTE;
  if(strcasecmp(lexema,"Booleano") ==0 )return BOOL;
  if(strcasecmp(lexema,"Doble") ==0 )return DOBLE;
  if(strcasecmp(lexema,"Caracter") ==0 )return CARACTER;
  if(strcasecmp(lexema,"Cadena") ==0 )return CADENA;
  if(strcasecmp(lexema,"vacio") ==0 )return VACIO;
  if(strcasecmp(lexema,"nueva") ==0 )return NUEVA;
  if(strcasecmp(lexema,"para")==0) return PARA;
  if(strcasecmp(lexema,"si") ==0 )return SI;
  if(strcasecmp(lexema,"sino")==0) return SINO;
	if(strcasecmp(lexema,"and")==0) return AND;
	if(strcasecmp(lexema,"or")==0) return OR;
  if(strcasecmp(lexema,"retorna") ==0 )return RETORNA;
  if(strcasecmp(lexema,"mientras") ==0 )return MIENTRAS;
  if(strcasecmp(lexema,"verdadero") ==0 )return VERDADERO;
  if(strcasecmp(lexema,"falso") ==0 )return FALSO;
  if(s>0) return METODO;
  return ID;
}

int yylex(){
  char c;
	double value;
  while(1){
	  c=getchar();
    if(c=='\n'){ linea+=1;printf("yvs:%i:> ",linea); continue;}
    if(c==' ') continue;
    if(c=='+') return SUMA;
    if(c=='-') return RESTA;
    if(c=='*') return MULTI;
    if(c=='/') return DIV;
    if(c=='^') return POT;
    if(c=='(') return PAR1;
    if(c==')') return PAR2;	
    if(c=='{') return LLAVE1;
    if(c=='}') return LLAVE2;
    if(c==';') return PUNTOCOMA;
    if(c==',') return COMA;
    if(c=='=') return IGUAL;
    if(c=='<') return MENOR;
    if(c=='>') return MAYOR;
	  if(isdigit(c)){
	    ungetc(c, stdin);
	    scanf("%lf", &value);
	    yylval = value; //pasando valor a la pila
	    return NUM;
	  }
	  if(isalpha(c)){
      int i=0, s=0;
      do{
    		lexema[i++]=c;
			  if(c=='.') s=1;
			  c=getchar();
		  } while(isalnum(c) || c=='.');
      ungetc(c,stdin);
      lexema[i]=0;
      return reservedWord(lexema,s);
	  }
	  return c;
  }
}

int main(){
  printf("YoVerSil, version 1.0 (default, Mayo 5 2016, 12:15)\n");
  printf("Desarrollado por Moreno Vera Felipe Adrian\n\n");
  printf("yvs:1:>");
  if(!yyparse()) printf("\nGracias por usar YoVerSil !!\n\n");
	else printf("\ncadena invalida\n");
	return 0;
}
