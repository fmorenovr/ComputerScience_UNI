%{
// incluimos las librerias
#include<stdio.h>
#include<string.h>
char lexema[64];
void yyerror(char *);
%}

%token VAR IGUAL NUM PUNTCOM DOSPUNTS MAS MENOS MULTI DIV
/*
  VAR es el token que identificaa una variable en general (x, var1, etc ... )
  IGUAL es el token del caracter =
  PUNTCOM es el token del caracter ;
  DOSPUNTS es el token del caracter :
  MAS es el token del caracter +
  MENOS es el token del caracter -
  MULTI es el token del caracter *
  DIV es el token del caracter /
  NUM es el token para identificar un numero
*/

%%

// la cadena varDefine acepta 
varDefine: varDefine VAR DOSPUNTS IGUAL expr PUNTCOM | ;
// expansion izquierda
expr: expr MAS expr1 | expr MENOS expr1 | expr1;
expr1: expr1 MULTI NUM | NUM ;

/*
expr: expr exprWeight2 MAS exprWeight2 |
      expr exprWeight1 MAS exprWeight1 |
      expr exprWeight2 MAS exprWeight1 |
      expr exprWeight1 MAS exprWeight2 |

      expr exprWeight2 MENOS exprWeight2 |
      expr exprWeight1 MENOS exprWeight1 |
      expr exprWeight2 MENOS exprWeight1 |
      expr exprWeight1 MENOS exprWeight2 |

      expr exprWeight2 MULTI exprWeight2 |
      expr exprWeight1 MULTI exprWeight1 |
      expr exprWeight2 MULTI exprWeight1 |
      expr exprWeight1 MULTI exprWeight2 |

      expr exprWeight2 DIV exprWeight2 |
      expr exprWeight1 DIV exprWeight1 |
      expr exprWeight2 DIV exprWeight1 |
      expr exprWeight1 DIV exprWeight2 |
      
      NUM ;

// la cadena expresion peso 1 acepta () + 1, () - 1, ()*2, 2;
exprWeight1: expr MAS NUM |
             expr MENOS NUM |
             NUM ;

// la cadena expresion peso 2 acepta () + 1, () - 1, ()*2, 2;
exprWeight2: expr DIV NUM |
             expr MULTI NUM |
             NUM ;
*/

%%

void yyerror(char *mgs){
  printf("error:%s",mgs);
}

int yylex(){
  char c;
  while(1){
    c=getchar();
    // reconoce las cadenas ingresadas
    if(c=='\n'){
//      printf("miauw:> ");
      continue;
    }
    if(isspace(c)) continue;
    if(c==':') return DOSPUNTS;
    if(c==';') return PUNTCOM;
    if(c=='=') return IGUAL;
    if(c=='*') return MULTI;
    if(c=='/') return DIV;
    if(c=='+') return MAS;
    if(c=='-') return MENOS;
    
    if(isalpha(c)){ // verifica si es caracter
      int i=0;
      do{
        lexema[i++]=c;
        c=getchar();
      } while(isalnum(c));
      ungetc(c,stdin); // devuelve el caracter a la entrada estandar
      lexema[i]=0;
      return VAR; // devuelve el token
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
//  printf("miauw:> ");
  if(!yyparse())
    printf("cadena valida \n");
  else
    printf("cadena invalida\n");
  return 0;
}
