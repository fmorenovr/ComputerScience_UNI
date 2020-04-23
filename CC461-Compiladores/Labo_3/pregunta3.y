%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char lexema[60];
void yyerror(char *msg);
typedef struct{char nombre[60];double valor;int token;int tokenaux;}tipoTS;
tipoTS TablaSim[100];
int nSim = 0;
typedef struct{int op;int a1;int a2;int a3;}tipoCodigo;
int cx = -1;
tipoCodigo TCodigo[100];
void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp = 0;
int GenVarTemp();
%}

%token PROGRAMA ID INICIO FIN NUM VARIABLE ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR POTENCIA COMPARARIGUAL COMPARARDESIGUAL PARENTESIS COMPARARMENOR COMPARARMAYOR COMPARARMENORIGUAL COMPARARMAYORIGUAL
%%

S: PROGRAMA ID ';' listadeclaracion INICIO listaInstr FIN '.';
listadeclaracion: ;
listaInstr: instr listaInstr | ;
instr: ID{$$=localizaSimb(lexema,ID);} '=' expr{generaCodigo(ASIGNAR,$2,$4,'-');}';';
expr: expr '+' term{int i = GenVarTemp(); generaCodigo(SUMAR,i,$1,$3); $$=i;};
expr: expr '-' term{int i = GenVarTemp(); generaCodigo(RESTAR,i,$1,$3); $$=i;};
expr: term;
term: term '*' term2{int i = GenVarTemp(); generaCodigo(MULTIPLICAR,i,$1,$3); $$=i;};
term: term '/' term2{int i = GenVarTemp(); generaCodigo(DIVIDIR,i,$1,$3); $$=i;};
term: term2;
term2: term2 '^' term3{int i = GenVarTemp(); generaCodigo(POTENCIA,i,$1,$3); $$=i;};
term2: term3;
term3: term3 '<' '>' fact {int i = GenVarTemp(); generaCodigo(COMPARARDESIGUAL,i,$1,$4); $$=i;};
term3: term3 '<' '>' term4 {int i = GenVarTemp(); generaCodigo(COMPARARDESIGUAL,i,$1,$4); $$=i;};
term3: term3 '=' '=' fact {int i = GenVarTemp(); generaCodigo(COMPARARIGUAL,i,$1,$4); $$=i;};
term3: term3 '=' '=' term4 {int i = GenVarTemp(); generaCodigo(COMPARARIGUAL,i,$1,$4); $$=i;};
term3: term3 '<'  fact {int i = GenVarTemp(); generaCodigo(COMPARARMENOR,i,$1,$3); $$=i;};
term3: term3 '<'  term4 {int i = GenVarTemp(); generaCodigo(COMPARARMENOR,i,$1,$3); $$=i;};
term3: term3 '<' '=' fact {int i = GenVarTemp(); generaCodigo(COMPARARMENORIGUAL,i,$1,$4); $$=i;};
term3: term3 '<' '=' term4 {int i = GenVarTemp(); generaCodigo(COMPARARMENORIGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' fact {int i = GenVarTemp(); generaCodigo(COMPARARMAYORIGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' term4 {int i = GenVarTemp(); generaCodigo(COMPARARMAYORIGUAL,i,$1,$4); $$=i;};
term3: term3 '>' fact {int i = GenVarTemp(); generaCodigo(COMPARARMAYOR,i,$1,$3); $$=i;};
term3: term3 '>' term4 {int i = GenVarTemp(); generaCodigo(COMPARARMAYOR,i,$1,$3); $$=i;};
term3: fact;
term3: term4;
term4: '(' expr ')'{int i = GenVarTemp(); generaCodigo(PARENTESIS,i,$2,$2); $$=i;};
fact: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);};

%%
int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,ID);
}

void generaCodigo(int op, int a1, int a2, int a3){
  cx++;
  TCodigo[cx].op = op;
  TCodigo[cx].a1 = a1;
  TCodigo[cx].a2 = a2;
  TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok){
  int i;
  for(i=0; i<nSim; i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token = tok;
  if(tok==ID) TablaSim[nSim].valor = 0.0;
  if(tok==NUM) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim - 1;
}

void imprimeTablaSim(){
  int i;
  for(i=0; i<nSim; i++){
    if(TablaSim[i].tokenaux==COMPARARDESIGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==COMPARARIGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==COMPARARMAYOR){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==COMPARARMENOR){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==COMPARARMAYORIGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==COMPARARMENORIGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    printf("%d nombre = %s tok = %d valor = %lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for(i=0; i<=cx; i++){
    
    printf("%d a1 = %d a2 = %d a3 = %d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void interpretaCodigo(){
  int i,a1,a2,a3,op,j,temp;
  for(i=0; i<=cx; i++){
    op = TCodigo[i].op;
    a1 = TCodigo[i].a1;
    a2 = TCodigo[i].a2;
    a3 = TCodigo[i].a3;
    if(op==ASIGNAR){
      TablaSim[a1].valor = TablaSim[a2].valor;
    }
    if(op==SUMAR){
      TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
    }
    if(op==RESTAR){
      TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
    }
    if(op==MULTIPLICAR){
      TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
    }
    if(op==DIVIDIR){
      TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
    }
    if(op==POTENCIA){
        if (TablaSim[a3].valor>1){
            temp = 1;
            for(j=1; j<=TablaSim[a3].valor; j++){
                temp = temp*TablaSim[a2].valor;
            }
            TablaSim[a1].valor = temp;
        }
        else{
            TablaSim[a1].valor = temp*TablaSim[a2].valor;
        }
    }
    if(op==COMPARARDESIGUAL){
        TablaSim[a1].tokenaux=COMPARARDESIGUAL;
        if(TablaSim[a2].valor!=TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==COMPARARIGUAL){
        TablaSim[a1].tokenaux=COMPARARIGUAL;
        if(TablaSim[a2].valor==TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==COMPARARMAYOR){
        TablaSim[a1].tokenaux=COMPARARMAYOR;
        if(TablaSim[a2].valor>TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==COMPARARMENOR){
        TablaSim[a1].tokenaux=COMPARARMENOR;
	 if(TablaSim[a2].valor<TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==COMPARARMAYORIGUAL){
        TablaSim[a1].tokenaux=COMPARARMAYORIGUAL;
	 if(TablaSim[a2].valor>=TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==COMPARARMENORIGUAL){
        TablaSim[a1].tokenaux=COMPARARMENORIGUAL;
	 if(TablaSim[a2].valor<=TablaSim[a3].valor){
            TablaSim[a1].valor = 1;
        }
        else{
            TablaSim[a1].valor = 0;
        }
    }
    if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;
  }
}

void yyerror(char *msg){
  printf("ERROR: %s\n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcasecmp(lexema,"Programa")==0) return PROGRAMA;
  if(strcasecmp(lexema,"Inicio")==0) return INICIO;
  if(strcasecmp(lexema,"Fin")==0) return FIN;
  return ID;
}

int yylex(){
  char c; int i;
  while(1){
    c = getchar();
    if(c==' ') continue;
    if(c=='\t') continue;
    if(c=='\n') continue;
    if(isdigit(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isdigit(c));
      ungetc(c,stdin);
      lexema[i] = '\0';
      //lexema[i] = 0;
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
      //lexema[i] = 0;
      return EsPalabraReservada(lexema);
    }
    return c;
  }
}

int main(){
  if(!yyparse()) printf("La cadena es valida\n");
  else printf("La cadena es INVALIDA\n");
  printf("Tabla de Simbolos:\n"); imprimeTablaSim();
  printf("Tabla de Codigos\n"); imprimeTablaCod();
  interpretaCodigo();
  printf("Nueva tabla:\n"); imprimeTablaSim();
}
