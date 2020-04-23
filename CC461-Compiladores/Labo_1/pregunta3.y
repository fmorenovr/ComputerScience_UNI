%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTCOM MAS MENOS MULT DIV POW PLEFT PRIGHT TYPE LIB BEGIN END PROGRAM VAR NAME

//PROGRAMA: lib "Programa" "Ejemplo" PUNTCOM cadenaVar "Inicio" varDefine "Fin" | ;

//cadenaVar: cadenaVar "Variables" "Real" vars PUNTCOM | ;

//vars: vars COM ID | ID ;

//lib: lib "libreria" "#" ID "#" PUNTCOM | ;

//             vars PUNTCOM instruction          |

%%

programa: instruction |  ;

instruction: ID IGUAL expr PUNTCOM instruction |
             expr PUNTCOM instruction          |
             library instruction               |
             PROGRAM NAME PUNTCOM instruction  |
             VAR TYPE vars PUNTCOM instruction |
             BEGIN instruction |
             END instruction |
             ;

// importar librerias
library: library LIB '#' ID '#' | ;


// declaracion de variables x,y,z;
vars: vars ',' ID |
      ID ;

// expresiones matematicas con [ +,-,*,/,^,(,) ]
expr: expr MAS term   |
      expr MENOS term |
      term;

term: term MULT term2 |
      term DIV term2  |
      term2;

term2: term2 POW term3 |
       term3;

term3: PLEFT expr PRIGHT       |
       MENOS PLEFT expr PRIGHT |
       dig;
   
dig: dig2       |
     MENOS dig2 |
     MAS dig2;

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
	char c;
	int i;
	while(1){
		c = getchar();
		if(c=='\n'){
      printf("miauw:> ");
      continue;
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
