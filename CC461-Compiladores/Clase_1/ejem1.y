%{
#include <stdio.h>
#include <string.h>
char lexema[255];
void yyerror(char *);
%}

%token ID

%% // cadenas a ingresar
instruccion: instruccion ID;
instruccion: ;
%%

void yyerror(char *mgs){
	printf("error: %s",mgs);
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
			}while(isalnum(c));
			
			ungetc(c,stdin);
			lexema[i]==0;
			printf("%i",ID); // esta definido
			return ID;
		}
		
		printf("%c",c); // esta definido
		return c;
	}
}
int main(){
	if(!yyparse()) printf("cadena valida\n");
	else printf("cadena invalida");
	return 0;
}
