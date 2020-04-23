%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char lexema[60];
void yyerror(char *msg);
typedef struct{
  char nombre[60];
  double valor;
  int marca;
  char boolean[15];
  int token;
}tipoTS;
tipoTS TablaSim[100];
int nSim=0;
typedef struct{
  int op,a1,a2,a3;
}tipoCodigo;
int cx=-1;
tipoCodigo TCodigo[100];
void generaCodigo(int, int, int, int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp=0;
int GenVarTemp();
%}

%token PROGRAMA ID INICIO FIN NUM VARIABLE ASIGNAR SUMAR RESTA MULTI DIV POT MAYO

%%

S : PROGRAMA ID ';' listadeclaracion INICIO listaInstr FIN '.';
listadeclaracion: ;
listaInstr: instr listaInstr | ;

instr: ID {$$=localizaSimb(lexema,ID);} ':' '=' expr {generaCodigo(ASIGNAR, $2,$5,'-');} ';' ;
expr: term '>' term {int i=GenVarTemp(); generaCodigo(MAYO,i,$1,$3); $$=i;};
expr: expr '+' term {int i=GenVarTemp(); generaCodigo(SUMAR,i,$1,$3); $$=i;};
expr: expr '-' term {int i=GenVarTemp(); generaCodigo(RESTA,i,$1,$3); $$=i;};
expr: term;
term: term '*' fact {int i=GenVarTemp(); generaCodigo(MULTI,i,$1,$3); $$=i;};
term: term '/' fact {int i=GenVarTemp(); generaCodigo(DIV,i,$1,$3); $$=i;};
term: fact2;
fact2: fact2 '^' fact {int i=GenVarTemp(); generaCodigo(POT,i,$1,$3); $$=i;};
fact2: fact ;
fact: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);};

%%

int GenVarTemp(){
  char t[60];
  sprintf(t, "_T%d", nVarTemp++);
  return localizaSimb(t,ID);
}

void generaCodigo(int op, int a1,int a2,int a3){
  cx++;
  TCodigo[cx].op = op;
  TCodigo[cx].a1 = a1;
  TCodigo[cx].a2 = a2;
  TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok){
  int i;
  for(i=0;i<nSim;i++){
    if(!strcasecmp(TablaSim[i].nombre,nom)) return i;
  }
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token = tok;
  TablaSim[nSim].marca = 0;
  if(tok==ID) TablaSim[nSim].valor=0.0;
  if(tok==NUM) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim-1;
}

void imprimeTablaSim(){
  int i;
  for(i=0;i<nSim;i++){
    if(TablaSim[i].marca==0)
    printf("%d nombre=%s tok=%d valor=%lf\n",i,TablaSim[i].nombre, TablaSim[i].token, TablaSim[i].valor);
    else
    printf("%d nombre=%s tok=%d valor=%s\n",i,TablaSim[i].nombre, TablaSim[i].token, TablaSim[i].boolean);
  }
}

void imprimeTablaCod(){
  int i;
  for(i=0;i<=cx;i++){
    printf("%d a1=%d a2=%d a3=%d\n",TCodigo[i].op, TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void ejecuta(){
  printf("Ejecutando las operaciones\n");
 int i,j;
  for(i=0;i<=cx;i++){
	if(TCodigo[i].op==SUMAR){
		TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor+TablaSim[TCodigo[i].a3].valor;
	}
	if(TCodigo[i].op==ASIGNAR){
		if(TablaSim[TCodigo[i].a2].marca==0)
			TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor;
		else{
			TablaSim[TCodigo[i].a1].marca=1;
			strcpy(TablaSim[TCodigo[i].a1].boolean,TablaSim[TCodigo[i].a2].boolean);
		}
	}
	if(TCodigo[i].op==RESTA){
		TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor-TablaSim[TCodigo[i].a3].valor;
	}
	if(TCodigo[i].op==MULTI){
		TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor*TablaSim[TCodigo[i].a3].valor;
	}
	if(TCodigo[i].op==DIV){
		TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor/TablaSim[TCodigo[i].a3].valor;
	}
	if(TCodigo[i].op==POT){
		double x=1.0;
		for( j=0;j<TablaSim[TCodigo[i].a3].valor;j++){
			x=x*TablaSim[TCodigo[i].a2].valor;
		}
		TablaSim[TCodigo[i].a1].valor=x;
	}
	if(TCodigo[i].op==MAYO){
//		TablaSim[TCodigo[i].a1].valor=TablaSim[TCodigo[i].a2].valor > TablaSim[TCodigo[i].a3].valor;
		TablaSim[TCodigo[i].a1].marca=1;
		if(TablaSim[TCodigo[i].a2].valor > TablaSim[TCodigo[i].a3].valor) {		
			strcpy(TablaSim[TCodigo[i].a1].boolean,"VERDADERO");}
		else
			strcpy(TablaSim[TCodigo[i].a1].boolean,"FALSO");
	}


  }
  printf("Fin de las operaciones\n");
}

void yyerror(char *msg){
  printf("ERROR:%s\n",msg);
}


int EsPalabraReservada(char lexema[]){
  if(strcasecmp(lexema,"Program")==0) return PROGRAMA;
  if(strcasecmp(lexema,"Begin")==0) return INICIO;
  if(strcasecmp(lexema,"End")==0) return FIN;
  if(strcasecmp(lexema,"Var")==0) return VARIABLE;
  return ID;
}

int yylex(){
  char c; int i;
  while(1){
    c=getchar();
    if(c==' ') continue;
    if(c=='\t') continue;
    if(c=='\n') continue;
    if(isdigit(c)){
      i=0;
      do{
        lexema[i++]=c;
        c=getchar();
      }while(isdigit(c));
      ungetc(c,stdin);
      lexema[i]='\0';
      return NUM;
    }
    if(isalpha(c)){
      i=0;
      do{
        lexema[i++]=c;
        c=getchar();
      }while(isalnum(c));
      ungetc(c,stdin);
      lexema[i]='\0';
      return EsPalabraReservada(lexema);
    }
    return c;
      
    
  }
}


int main(){
  if(!yyparse()) printf("La cadena es valida\n");
  else printf("La cadena es invalida\n");
  printf("tabla de simbolos\n");
  imprimeTablaSim();
  printf("tabla de codigos\n");
  imprimeTablaCod();
  ejecuta();
//  printf("tabla de simbolos otra vez\n");
//  imprimeTablaSim();
}
