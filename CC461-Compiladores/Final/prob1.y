%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
char lexema[60];
int yylex();
void yyerror(char *msg);
typedef struct{
   char nombre[60];
   double valor;
   int token;
   int tokenaux;
}tipoTS;
tipoTS TablaSim[100];
int nSim = 0;
typedef struct{
   int op;
   int a1;
   int a2;
   int a3;
}tipoCodigo;
int cx = -1;
tipoCodigo TCodigo[100];
void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();
int nVarTemp = 0;
int bucleW,bucleF;
int GenVarTemp();
void InterpretaCodigo();
int linea = 0;
%}

%token ID FIN INICIO PROGRAMA NUM VARIABLE ASIGNAR
%token RAIZ SUMAR RESTAR MULTIPLICAR DIVIDIR POTENCIA PARENTESIS 
%token  SI SINO SINOSI SALTARF1 SALTARF2 MIENTRAS IMPRIMIR PARA BUCLE HASTA
%token MAYOR MENOR IGUAL MAYOR_IGUAL MENOR_IGUAL NOIGUAL
%token OPSUMAR OPRESTAR OPMULTIPLICAR DESDE
%%

comienzo: INICIO PROGRAMA ID listaInstruccion FIN;
bloque: listaInstruccion FIN  |  instruccion bloque;
listaInstruccion: instruccion listaInstruccion | ;
instruccion: IMPRIMIR ID ';' {generaCodigo(IMPRIMIR,$2,'-','-');};
instruccion: VARIABLE vrble ';' | ID {$$=localizaSimb(lexema,ID);} '=' cond{generaCodigo(ASIGNAR,$2,$4,'-');} ';';
vrble: ID {$$=localizaSimb(lexema,ID);} '=' cond{generaCodigo(ASIGNAR,$2,$4,'-');} terminal vrble|;
terminal: ','|;
//$$ Almacena de valor de retorno de la produccion
instruccion: SI cond {generaCodigo(SALTARF1,$2,'?','-');$$=cx;} INICIO bloque {generaCodigo(SALTARF2,'?','-','-');$$=cx;}{TCodigo[$3].a2=cx+1;} otro {TCodigo[$5].a1=cx+1;};
otro: SINO INICIO bloque | SINOSI cond {generaCodigo(SALTARF1,$2,'?','-');$$=cx;} INICIO bloque {generaCodigo(SALTARF2,'?','-','-');$$=cx;}{TCodigo[$3].a2=cx+1;} otro {TCodigo[$6].a1=cx+1;} | ;

instruccion: MIENTRAS {bucleW=cx;} cond {generaCodigo(SALTARF1,$3,'?','-');$3=cx;} INICIO bloque {generaCodigo(BUCLE,bucleW,'-','-');}{TCodigo[$5].a3=cx;}{TCodigo[$7].a1=cx+1;};

instruccion: PARA ID HASTA {bucleF=cx;} cond {generaCodigo(SALTARF1,$5,'?','-');$5=cx;} INICIO bloque {generaCodigo(BUCLE,bucleF,'-','-');}{TCodigo[$7].a3=cx;}{TCodigo[$9].a1=cx+1;};

instruccion: OPSUMAR DESDE ID HASTA ID {bucleF=cx;}{generaCodigo(SALTARF1,$3,$5,'-');$5=cx;} INICIO bloque {generaCodigo(BUCLE,bucleF,'-','-');}{TCodigo[$8].a3=cx;}{TCodigo[$10].a1=cx+1;};

cond: cond '+' term{int i = GenVarTemp(); generaCodigo(SUMAR,i,$1,$3); $$=i;};
cond: cond '-' term{int i = GenVarTemp(); generaCodigo(RESTAR,i,$1,$3); $$=i;};
cond: term;
term: term '*' term2{int i = GenVarTemp(); generaCodigo(MULTIPLICAR,i,$1,$3); $$=i;};
term: term '/' term2{int i = GenVarTemp(); generaCodigo(DIVIDIR,i,$1,$3); $$=i;};
term: term2;
term2: term2 '^' term3{int i = GenVarTemp(); generaCodigo(POTENCIA,i,$1,$3); $$=i;};
term2: term2 '%' term3{int i = GenVarTemp(); generaCodigo(RAIZ,i,$1,$3); $$=i;};
term2: term3;
term3: term3 '<' '>' fact {int i = GenVarTemp(); generaCodigo(NOIGUAL,i,$1,$4); $$=i;};
term3: term3 '<' '>' term4 {int i = GenVarTemp(); generaCodigo(NOIGUAL,i,$1,$4); $$=i;};
term3: term3 '=' '=' fact {int i = GenVarTemp(); generaCodigo(IGUAL,i,$1,$4); $$=i;};
term3: term3 '=' '=' term4 {int i = GenVarTemp(); generaCodigo(IGUAL,i,$1,$4); $$=i;};
term3: term3 '<'  fact {int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
term3: term3 '<'  term4 {int i = GenVarTemp(); generaCodigo(MENOR,i,$1,$3); $$=i;};
term3: term3 '<' '=' fact {int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '<' '=' term4 {int i = GenVarTemp(); generaCodigo(MENOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' fact {int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '>' '=' term4 {int i = GenVarTemp(); generaCodigo(MAYOR_IGUAL,i,$1,$4); $$=i;};
term3: term3 '>' fact {int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
term3: term3 '>' term4 {int i = GenVarTemp(); generaCodigo(MAYOR,i,$1,$3); $$=i;};
term3: fact;
term3: term4;
term4: '(' cond ')'{int i = GenVarTemp(); generaCodigo(PARENTESIS,i,$2,$2); $$=i;};
fact: NUM{$$=localizaSimb(lexema,NUM);} | ID{$$=localizaSimb(lexema,ID);};

%%
void InterpretaCodigo(){
  int i,a1,a2,a3,op;
  for(i=0; i<=cx; i++){
    op = TCodigo[i].op;
    a1 = TCodigo[i].a1;
    a2 = TCodigo[i].a2;
    a3 = TCodigo[i].a3;

    if(op==MAYOR){
         if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==MENOR){
         if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==MAYOR_IGUAL){
         if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==MENOR_IGUAL){
         if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==IGUAL){
         if(TablaSim[a2].valor==TablaSim[a3].valor)TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==NOIGUAL){
         if(TablaSim[a2].valor!=TablaSim[a3].valor)TablaSim[a1].valor=0;
         else
            TablaSim[a1].valor=1;
    }
    if(op==SUMAR) TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
    if(op==RESTAR) TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
    if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
    if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
    if(op==POTENCIA) TablaSim[a1].valor = pow(TablaSim[a2].valor,TablaSim[a3].valor);
    if(op==SALTARF1){
         if(TablaSim[a1].valor==0) i=a2-1;
    }
    if(op==SALTARF2) i=a1-1;
    if(op==BUCLE) i=a1;
    if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;
    if(op==ASIGNAR) TablaSim[a1].valor = TablaSim[a2].valor;
    if(op==IMPRIMIR) printf("%lf\n",TablaSim[a1].valor);
  }
}

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
    if(TablaSim[i].tokenaux==NOIGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==IGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==MAYOR){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==MENOR){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==MAYOR_IGUAL){
      if(TablaSim[i].valor==1.0)
        printf("%d nombre = %s tok = %d valor = verdadero\n",i,TablaSim[i].nombre,TablaSim[i].token);
      else
        printf("%d nombre = %s tok = %d valor = falso\n",i,TablaSim[i].nombre,TablaSim[i].token);
    }
    if(TablaSim[i].tokenaux==MENOR_IGUAL){
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
    printf("%d\ta1 = %d\ta2 = %d\ta3 = %d\n",TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void yyerror(char *msg){
  printf("ERROR: %s\n",msg);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcasecmp(lexema,"programa")==0) return PROGRAMA;
  if(strcasecmp(lexema,"Var")==0) return VARIABLE;
  if(strcasecmp(lexema,"si")==0) return SI;
  if(strcasecmp(lexema,"sinosi")==0) return SINOSI;
  if(strcasecmp(lexema,"sino")==0) return SINO;
  if(strcasecmp(lexema,"mientras")==0) return MIENTRAS;
  if(strcasecmp(lexema,"para")==0) return PARA;
  if(strcasecmp(lexema,"hasta")==0) return HASTA; 
  if(strcasecmp(lexema,"imprimir")==0) return IMPRIMIR;
  if(strcasecmp(lexema,"sumar")==0) return OPSUMAR;
  if(strcasecmp(lexema,"restar")==0) return OPRESTAR;
  if(strcasecmp(lexema,"multiplicar")==0) return OPMULTIPLICAR;
  if(strcasecmp(lexema,"desde")==0) return DESDE;
  return ID;
}

int yylex(){
  char c; int i;
  while(1){
    c = getchar();
    if(c==' ') continue;
    if(c=='\t') continue;
    if(c=='\n') {
      printf("linea %d\n",++linea);
      continue;
    }
    if(c=='[') return INICIO;
    if(c==']') return FIN;
    if(isdigit(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isdigit(c));
      ungetc(c,stdin);
      lexema[i] = '\0';
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
      return EsPalabraReservada(lexema);
    }
    return c;
  }
}

int main(){
  if(!yyparse()) printf("La cadena es VALIDA\n");
  else printf("La cadena es INVALIDA\n");
  printf("Tabla de Simbolos:\n"); imprimeTablaSim();
  printf("Tabla de Codigos\n"); imprimeTablaCod();
  InterpretaCodigo();
  printf("Nueva tabla: despues de interpretar\n"); imprimeTablaSim();
  printf("Valor bucleW: %d\n",bucleW);
  printf("Valor bucleF: %d\n",bucleF);
}
