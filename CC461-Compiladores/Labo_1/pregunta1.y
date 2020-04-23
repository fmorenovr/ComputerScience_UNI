%{
#include<stdio.h>
#include<string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID IGUAL NUM PUNTCOM MAS MENOS MULT DIV POW PLEFT PRIGHT

%%

varDefine: ID IGUAL expr PUNTCOM varDefine | ;

expr: expr MAS expr   |
      expr MENOS expr |
      term;

term: term MULT term |
      term DIV term  |
      term2;

term2: term2 POW term2 |
       term3;

term3: PLEFT expr PRIGHT       |
       MENOS PLEFT expr PRIGHT |
       dig;
   
dig: dig2       |
     MENOS dig2 |
     MAS dig2;

dig2: NUM;

%%

void yyerror(char *mgs){
	printf("error: %s", mgs);
}

int yylex(){
	char c;
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
		
		if(isalpha(c)){ // verifica si es caracter
      int i=0;
      do{
        lexema[i++]=c;
        c=getchar();
      } while(isalnum(c));
      ungetc(c,stdin); // devuelve el caracter a la entrada estandar
      lexema[i]=0;
      return ID; // devuelve el token
    }
    
    if(isdigit(c)){ //verifica si es numero entero
      int i=0;
      do{
        lexema[i++]=c;
        c=getchar();
      } while(isdigit(c));
      ungetc(c,stdin); // devuelve el caracter a la entrada estandar
      lexema[i]=0;
      return NUM; // devuelve el token
    }
    return c;
	}
}

int main(){
  printf("YoVerSil, version 1.0 (default, March 2016, 12:15)\n");
  printf("Develop by Felipe A. Moreno\n");
  printf("[bison (GNU bison) 3.0.2]\n");
  printf("yvs:> ");
	if(!yyparse()) printf(" cadena valida\n");
	else printf(" cadena invalida\n");
	return 0;
}
