%{

#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double /* double type for YACC stack */
void yyerror(char *);
%}

%token NUMBER ID
%%
instr: prog instr | ;
prog: expr ';' { printf("VALOR %g\n",$1);};
prog: ;

expr: expr '+' term { $$ = $1 + $3;} | term;
term: term '*' factor {$$ = $1 * $3;} 	| factor;
factor: NUMBER|ID;

%%

void yyerror(char *mgs){
	printf("error: %s",mgs);
}
int yylex(void){
	double t;
	int c;
	while((c=getchar())==' ');
	while(1){
	  if(c=='.' || isdigit(c)){
		  ungetc(c, stdin);
		  scanf("%lf",&t);
		  yylval=t;//pasando valor a la pila
		  return NUMBER;
	  }
	}
	return c;
}
int main(void){
	return yyparse();
}
