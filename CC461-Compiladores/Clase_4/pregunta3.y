%{
#include<stdio.h>
#include<string.h>
#include <math.h>
#define YYSTYPE double /* double type for YACC stack */
char lexema[255];
void yyerror(char *);
int reservedWord(char lexema[]);
%}

%token ID IGUAL NUM TYPE LIB BEGIN END PROGRAM VAR NAME

//PROGRAMA: lib "Programa" "Ejemplo" PUNTCOM cadenaVar "Inicio" varDefine "Fin" | ;

//cadenaVar: cadenaVar "Variables" "Real" vars PUNTCOM | ;

//vars: vars COM ID | ID ;

//lib: lib "libreria" "#" ID "#" PUNTCOM | ;

//             vars PUNTCOM instruction          |

%%

instruction: ID '=' expr ';' instruction |
             library instruction               |
             PROGRAM NAME ';' instruction  |
             VAR TYPE vars ';' instruction |
             BEGIN instruction |
             END instruction |
             evalExpr instruction |
             ;

// importar librerias
library: LIB '#' ID '#' ;

evalExpr: expr ';' { printf("VALOR %g\n",$1);}
;

// declaracion de variables x,y,z;
vars: vars ',' ID |
      ID ;

// expresiones matematicas con [ +,-,*,/,^,(,) ]
expr: expr '+' term   {$$ = $1 + $3;}|
      expr '-' term {$$ = $1 - $3;}|
      term {$$ = $1;};

term: term '*' term2 {$$ = $1 * $3;}|
      term '/' term2  {$$ = $1 / $3;}|
      term2 {$$ = $1;};

term2: term2 '^' term3 {$$ = pow($1,$3);}|
       term3 {$$ = $1;};

term3: '(' expr ')' {$$ = $2;}|
       '-' '(' expr ')' {$$ = -$3;}|
       dig;
   
dig: dig2       |
     '+' dig2 |
     '-' dig2;

dig2: NUM | ID;

%%

void yyerror(char *mgs){
	printf("error: %s", mgs);
}

int reservedWord(char lexema[]){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
	if(strcasecmp(lexema,"libreria")==0) return LIB;
	if(strcasecmp(lexema,"Inicio")==0) return BEGIN;
	if(strcasecmp(lexema,"Fin")==0) return END;
	if(strcasecmp(lexema,"Programa")==0) return PROGRAM;
	if(strcasecmp(lexema,"Ejemplo")==0) return NAME;
	if(strcasecmp(lexema,"Variables")==0) return VAR;
	if(strcasecmp(lexema,"Real")==0 || strcasecmp(lexema,"Entero")==0) return TYPE;
  return ID;
}

int yylex(){
	char c; // recolecta cadenas
	double t; // evalua los resultados
	int i;
	
	while(1){
		c = getchar();
		if(c=='\n'){
      printf("yvs:> ");
      continue;
    }
    // saltea espacios en blanco */
		if(isspace(c)) continue;
		if(c== '\t') continue;
		
		/* evalua numeros */
		if(isdigit(c)){
			int i=0;
			lexema[i++]=c;
			c=getchar();
			if(c=='.'){        //parte decimal despues de la coma
			  lexema[i++]=c;
				c=getchar();
				if(isdigit(c)){
				    do{
				        lexema[i++]=c;
				        c=getchar();
			        }while(isdigit(c));
			        
			        if(c!='E'){
			            ungetc(c,stdin);
                		lexema[i]=0;
			            return NUM;
			        }
			        else{               //si encuentra al E
			            lexema[i++]=c;
				        c=getchar();
				        if(c=='-' || c== '+'){
				            lexema[i++] = c;
				            c=getchar();
				        }
				        if(isdigit(c)){
        				    do{
        				        lexema[i++]=c;
        				        c=getchar();
        			        }while(isdigit(c));
                            if(isalpha(c)) return c;
                            else ungetc(c,stdin);
                			lexema[i]=0;
			                return NUM;        			        
                        }				        
			        }
				}
			}
			else if(c=='E'){
			    lexema[i++]=c;
				c=getchar();
				if(isdigit(c)){
        		    do{
        		        lexema[i++]=c;
        		        c=getchar();
        		    }while(isdigit(c));
                    if(isalpha(c)) return c;
                    else ungetc(c,stdin);
                    lexema[i]=0;
			        return NUM;        			        
                }
			}
			else if(isdigit(c)){
			    do{
				    lexema[i++]=c;
				    c=getchar();
    			}while(isdigit(c));
    			if(isalpha(c)) return c;
    			else ungetc(c,stdin);
    			lexema[i]=0;
    			return NUM;
       		}
			else ungetc(c,stdin);
			lexema[i]=0;
			return NUM;
		}
		
		/* evalua caracteres */
		if(isalpha(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isalnum(c));
      ungetc(c,stdin);
      lexema[i] = '\0';
      return reservedWord(lexema);
    }
		return c;
	}
}

int main(){
  printf("YoVerSil, version 1.0 (default, March 2016, 12:15)\n");
  printf("Develop by Felipe A. Moreno\n");
  printf("[bison (GNU bison) 3.0.2]\n");
  printf("yvs:> ");
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
	return 0;
}
