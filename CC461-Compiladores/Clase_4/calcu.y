%{
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#define YYSTYPE double /*double type for YACC stack */
void yyerror(char *);
%}

%token NUM ID ENTER

%%
prog: ID ':' '=' expr ';' prog {printf("=> %g\n", $4);} | ENTER prog | expr ';' prog {printf("=> %g\n", $1);}  | ;

expr : expr '+' term { $$ = $1 + $3;}
	| expr '-' term { $$ = $1 - $3;}
	| term {$$=$1;}
	;

term : term '*' subterm {$$ = $1*$3;}
	| term '/' subterm {$$ = $1/$3;}
	| subterm {$$=$1;}
	;

subterm: subterm '^' ssterm { $$ = pow($1, $3);}
		| subterm '#' ssterm { $$ = sqrt($3);}
		| ssterm {$$=$1;}
		;

ssterm : '(' expr ')' {$$ = $2;}
		| factor {$$=$1;}
		;
factor: ID {$$=$1;}
	| NUM {$$=$1;}
	;

%%

void yyerror(char *msg){
	printf("error: %s", msg);
}

int yylex(void){
	double t;
	int c;
	while((c=getchar())==' ');
	
	if(c=='\n') return ENTER;
	
	if(c=='.' || isdigit(c)){
		ungetc(c, stdin);
		scanf("%lf", &t); yylval = t; //pasando valor a la pila
		return NUM;
	}
	
	if(isalpha(c)){
      //i = 0;
      do{
       // lexema[i++] = c;
        c = getchar();
      }while(isalnum(c));
      ungetc(c,stdin);
      //lexema[i] = '\0';
      return ID;
    }
	
	return c;
}

int main(void){
	return yyparse();
}


