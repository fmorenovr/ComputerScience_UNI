%{
#include<stdio.h>
#include<string.h>
#include <math.h>
#define YYSTYPE double /* double type for YACC stack */
char lexema[255];
void yyerror(char *);
int reservedWord(char lexema[]);
%}

%token ID IGUAL NUM PUNTCOM
%token MAS MENOS MULT DIV POW PLEFT PRIGHT NEWLINE
%token TYPE LIB BEGIN END PROGRAM VAR NAME
//PROGRAMA: lib "Programa" "Ejemplo" PUNTCOM cadenaVar "Inicio" varDefine "Fin" | ;

//cadenaVar: cadenaVar "Variables" "Real" vars PUNTCOM | ;

//vars: vars COM ID | ID ;

//lib: lib "libreria" "#" ID "#" PUNTCOM | ;

//             vars PUNTCOM instruction          |

// library: importar librerias

// vars: declaracion de la lista de variables x,y,meow ;

// expr: expresiones matematicas con [ +,-,*,/,^,(,) ]

%%
instruction: %empty                             |
             instruction library                |
             instruction PROGRAM NAME PUNTCOM   |
             instruction VAR TYPE vars PUNTCOM  |
             instruction BEGIN                  |
             instruction END                    |
             instruction evalExpr               |
             instruction NEWLINE                
;
library: LIB '#' ID '#' ;
vars: vars ',' ID | ID
;
evalExpr: expr  { printf("=> %g\n",$1); }
;
expr: expr MAS term   {$$ = $1 + $3;}|
      expr MENOS term {$$ = $1 - $3;}|
      term {$$ = $1;}
;
term: term MULT term2 {$$ = $1 * $3;}|
      term DIV term2  {$$ = $1 / $3;}|
      term2 {$$ = $1;}
;
term2: term2 POW term3 {$$ = pow($1,$3);}|
       term3 {$$ = $1;}
;
term3: PLEFT expr PRIGHT {$$ = $2;}       |
       MENOS PLEFT expr PRIGHT {$$ = -$3;}|
       dig {$$=$1;}
;   
dig: dig1    {$$=$1;} |
     MAS dig1 {$$=$1;}|
     MENOS dig1 {$$=-$1;}
;
dig1: NUM {$$=$1;} | ID{$$=$1;};
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
	if(strcasecmp(lexema,"exit")==0) return 0;
  return ID;
}

int yylex(){
	char c;
	int i;
	double value;
	while(1){  // el interprete no se detiene
		c = getchar();
		if(c=='\n'){
      printf("yvs::> ");
      return NEWLINE;
    }
		if(isspace(c)) continue;
		if(c==';') return PUNTCOM;
		if(c=='=') return IGUAL;
		if(c=='+') return MAS;
		if(c=='-') return MENOS;
		if(c=='*') return MULT;
		if(c=='/') return DIV;
		if(c=='(') return PLEFT;
		if(c==')') return PRIGHT;
		if(c=='^') return POW;
		
		/* Cuando es sin math.h */
		/*
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
        }
			}
			else if(isdigit(c)){
		    do{
		      lexema[i++]=c;
			    c=getchar();
  			}while(isdigit(c));
  			if(isalpha(c)) return c;
  			else ungetc(c,stdin);
      }
			else ungetc(c,stdin);
			lexema[i]=0;
  	//	scanf("%lf", &t);
	  //	yylval = t;
			return NUM;
		}
		*/
		
		/* analiza cualquier numero */
		if(c=='.' || isdigit(c)){
		  ungetc(c, stdin);
		  scanf("%lf", &value);
		  yylval = value; //pasando valor a la pila
		  return NUM;
	  }
	
		/* analiza cadenas */
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
  printf("\nYoVerSil, version 1.0 (default, March 2016, 12:15)\n");
  printf("Develop by Felipe A. Moreno\n\n");
  printf("yvs::> ");
  if(!yyparse())  printf("\nThanks for using YoVerSil !!\n\n");
	else printf("\ncadena invalida\n");
	return 0;
}
