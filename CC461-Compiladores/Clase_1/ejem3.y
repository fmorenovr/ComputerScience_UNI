%{
#include <stdio.h>
#include <string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID DOSPUNTOS IGUAL NUM

%%


instruccion: ID ':' '=' NUM;
instruccion: ID ':' '=' NUM '\n';
instruccion: ;

%%

void yyerror(char *mgs){
	printf("error:%s ",mgs);
}

int yylex(){
	char c;
	while(1){
		c=getchar();
		if(c=='\n') continue;
		if(c==' ') continue;
		
		if(isalpha(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalpha(c));
			ungetc(c,stdin);
			lexema[i]==0;
			return ID;
		}
		if(isdigit(c)){
			int i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]==0;
			return NUM;
		}
		return c;
	}
}
int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida\n");
	return 0;
}
