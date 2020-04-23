/*
================================================================================
                        Declaraciones de C
================================================================================
*/
%{
  #include"yvs_gramm_rules.h"
  extern int console;
  int num_linea=1;
  int palabraReservada(char*);
  void llerror(char*);
%}
/*
================================================================================
                        Patrones del lenguaje
================================================================================
  |--------------------------------------------------------------------|
  | metachar |	description                                            |
  |----------+---------------------------------------------------------|
  |    +     | previous expression can match one or more times         |
  |----------+---------------------------------------------------------|
  |    *     | previous expression can match zero or more times        |
  |----------+---------------------------------------------------------|
  |    ?     | previous expression can match zero or one time          |
  |----------+---------------------------------------------------------|
  |    .     | can match any character except the carriage return '\n' |
  |--------------------------------------------------------------------|
*/
BLANK    ([ \t])+
DIGITO   ([0-9])
LETRA    ([a-z])
LETRAS   ([A-Z])
ID       ({LETRAS}*{LETRA}+{DIGITO}*{LETRAS}*{LETRA}*{DIGITO}*)
OBJETO   ({LETRAS}+{LETRA}*{DIGITO}*)
NUMBER   ({DIGITO}+([Ee]{DIGITO})?|{DIGITO}+(\.{DIGITO}+)?)
EOL      (\n)
OTHER    ([\.\:])
/*
================================================================================
                        Expresiones Regulares
================================================================================
*/
/* Se definen las expresiones usando los tokens del lenguaje */
/* Realiza una accion cuando encuentra las expresiones o patrones siguientes */
/*{ID}  {yylval.id = (char *) strdup(yytext);return(IDENTIFIER);}*/
%%
{BLANK}       {;}
{NUMBER}      {if(console==1){ yylval.fval=atof(yytext); return NUM;}
               else{ return NUMBER;}}
{ID}          {return palabraReservada(yytext);}
{EOL}         {num_linea+=1; if(console==1){ printf("yvs:%d:> ",num_linea);}}
{OTHER}       {return yytext[0];}
"+"           {return MAS;}
"-"           {return MENOS;}
"*"           {return MULTI;}
"/"           {return DIV;}
"^"           {return POT;}
"("           {return PAR1;}
")"           {return PAR2;}
"{"           {return LLAVE1;}
"}"           {return LLAVE2;}
";"           {return PUNTOCOMA;}
","           {return COMA;}
"="           {return ASIGNAR;}
"=="          {return IGUAL;}
"<"           {return MENOR;}
">"           {return MAYOR;}
">="          {return MAYORIGUAL;}
"<="          {return MENORIGUAL;}
"<>"|"!="     {return DIFERENTE;}
.             {llerror("lexical error");}
%%
/*
================================================================================
                        Rutinas para el Scanner
================================================================================
*/
void llerror(char* msg){
  printf("\n===> Error Lexico en la linea %d\n\n",num_linea);
  exit(-1);
}
int palabraReservada(char* lexema){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcasecmp(lexema,"Principal")==0){
    return PRINCIPAL;
  }
  if(strcasecmp(lexema,"Clase")==0){
    return CLASE;
  }
  if(strcasecmp(lexema,"Publica")==0){
    return PUBLICA;
  }
  if(strcasecmp(lexema,"Privada")==0){
    return PRIVADA;
  }
  if(strcasecmp(lexema,"Entero")==0){
    return ENTERO;
  }
  if(strcasecmp(lexema,"Flotante")==0){
    return FLOTANTE;
  }
  if(strcasecmp(lexema,"Booleano")==0){
    return BOOL;
  }
  if(strcasecmp(lexema,"Doble")==0){
    return DOBLE;
  }
  if(strcasecmp(lexema,"Caracter")==0){
    return CARACTER;
  }
  if(strcasecmp(lexema,"Cadena")==0){
    return CADENA;
  }
  if(strcasecmp(lexema,"Vacio")==0){
    return VACIO;
  }
  if(strcasecmp(lexema,"Nueva")==0){
    return NUEVA;
  }
  if(strcasecmp(lexema,"Para")==0){
    return PARA;
  }
  if(strcasecmp(lexema,"Mientras")==0){
    return MIENTRAS;
  }
  if(strcasecmp(lexema,"Si")==0){
    return SI;
  }
  if(strcasecmp(lexema,"Sino")==0){
    return SINO;
  }
  if(strcasecmp(lexema,"Retorna")==0){
    return RETORNA;
  }
  if(strcasecmp(lexema,"Verdadero")==0){
    return VERDADERO;
  }
  if(strcasecmp(lexema,"Falso")==0){
    return FALSO;
  }
  if(strcasecmp(lexema,"YY")==0){
    return YY;
  }
  if(strcasecmp(lexema,"OO")==0){
    return OO;
  }
  yylval.strval = (char *) strdup(yytext);
  return ID;
}
/* se ejecuta al final del analisis (despues del yyparser) */
int yywrap(void){
  return 1;
}
/*
================================================================================
                        Fin del Scanner
================================================================================
*/
