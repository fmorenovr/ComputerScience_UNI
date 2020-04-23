//Realizado por Gustavo Adolfo Chavarria Mercado
//UNAN-LEON Nicaragua.
 
#include <stdio.h>
#include <time.h> //Libreria que contiene las funciones de tiempo del sistema.
 
int main()
{
 
int i,j,k,m,l,cont;				 //variables para correr ciclos
int dia,mes,anio,semana,moduloMes,febrero,total_mes;//Variables para almacenar el tiempo de la estructura tm.
int seleccion=1;					//Variable para un ciclo de respuestas.
i=j=k=m=l=cont=0; 				//Inicializo todas las variables a 0.
 
time_t sisTime; 	//time_t es un typedef, asigno una varible de este tipo (sisTime);
struct tm *tiempo;	//Creo un puntero a la estructura tm, (ya definida en time.h).
 
time(&sisTime);		//time obtiene el tiempo del sistema y se lo pasa a la direccion de sisTime.
tiempo=localtime(&sisTime);
//Convierte los valores de sisTime a compatibles con la estructura tm y luego asigno ese valor a tiempo.
 
//Una estructura tm, esta compuesta por datos de tipo int (vean la seccion de time.h)
 
dia=tiempo->tm_mday;		//accedo al valor de dia de la estructura tm y se la asigno a dia
mes=tiempo->tm_mon;		//accedo a mes de la estrutura tm y se la asigno a mes
anio=(tiempo->tm_year)+1900;	//year es un contador a partir de 1900.
 
system ("clear");//system ("cls") en windows, es para limpiar la pantalla.
 
printf("\t=============================>CALENDARIO<=============================\n\n");//rotulo
printf("Hoy es: %d/%d/%d \n\n\n",dia,mes+1,anio);//imprime las variables, mes+1?, es por que cuenta los meses desde 0
 
//seleccion esta inicializada en 1, asi que entrara una vez, luego mas abajo se pide si desea
//volver a entrar a ciclo.
 
while(seleccion != 0)
{
//Bisiesto.
//Debemos determinar si el anio es bisiesto para luego realizar las agrupaciones
 
if ((anio%4==0) && (anio%100!=0) || anio%400==0)
febrero=29;
else
febrero=28;
 
//Agrupacion de mes.
//Los meses se caracterizan por tener 28,29,30,31 dias...entonces hacemos una agrupacion.
 
switch (mes)
{
case 3: case 5: case 8: case 10: 
total_mes=30; 
break; 
case 1: 
total_mes=febrero; 
break; 
case 0: case 2: case 4: case 6: case 7: case 9: case 11: 
total_mes=31; 
break; 
}
 
//Asignar nombre del mes
//En esta parte se imprime la cabecera del calendario mes, y anio.
 
switch (mes)
{
case 0:printf("\t\tENERO\t%d",anio);break;
case 1:printf("\t\tFEBRERO\t%d",anio);break;
case 2:printf("\t\tMARZO\t%d",anio);break;
case 3:printf("\t\tABRIL\t%d",anio);break;
case 4:printf("\t\tMAYO\t%d",anio);break;
case 5:printf("\t\tJUNIO\t%d",anio);break;
case 6:printf("\t\tJULIO\t%d",anio);break;
case 7:printf("\t\tAGOSTO\t%d",anio);break;
case 8:printf("\t\tSEPTIEMBRE\t%d",anio);break;
case 9:printf("\t\tOCTUBRE\t%d",anio);break;
case 10:printf("\t\tNOVIEMBRE\t%d",anio);break;
case 11:printf("\t\tDICIEMBRE\t%d",anio);break;
}
 
//Modulo Mes...
//En wikipedia ya hay una tabla, para evitar mas calculos la voy a usar.
//Esto trata de sacarle el modulo 7 a los limites de cada mes, hasta llegar al mes que se cuenta.
 
if (febrero==29) //ya calcule el anio bisisesto, asi que no volvere a hacerlo.
{
	switch (mes)
	{
		case 0:moduloMes=0;break;
		case 1:moduloMes=3;break;
		case 2:moduloMes=4;break;
		case 3:moduloMes=0;break;
		case 4:moduloMes=2;break;
		case 5:moduloMes=5;break;
		case 6:moduloMes=0;break;
		case 7:moduloMes=3;break;
		case 8:moduloMes=6;break;
		case 9:moduloMes=1;break;
		case 10:moduloMes=4;break;
		case 11:moduloMes=6;break;
	}
 
}else
{
	switch (mes)
	{
		case 0:moduloMes=0;break;
		case 1:moduloMes=3;break;
		case 2:moduloMes=3;break;
		case 3:moduloMes=6;break;
		case 4:moduloMes=1;break;
		case 5:moduloMes=4;break;
		case 6:moduloMes=6;break;
		case 7:moduloMes=2;break;
		case 8:moduloMes=5;break;
		case 9:moduloMes=0;break;
		case 10:moduloMes=3;break;
		case 11:moduloMes=5;break;
	}
}
//Calculo del primer dia de la semana.
//Este algoritmo esta en la wikipedia, lo modificamos para que calcule el primer dia del mes
//En [http://es.wikipedia.org/wiki/Algoritmo_para_calcular_el_dia_de_la_semana este algoritmo]
//Remplacen dia por 1,(el primer dia del mes).
 
semana=((anio-1)%7+ ((anio-1)/4 -(3*((anio-1)/100+1)/4))%7+moduloMes+1%7)%7;
 
//Impresion de dias
printf("\nDo\tLu\tMar\tMier\tJue\tVier\tSab\n");
 
 
		for(m=0;m<semana;m++)//dar espacios para que el primer dia calce.
		printf("\t");
 
		for(i=1;i<=total_mes;i++)//imprimir dias correspondientes al mes.
		{
			if(i==8-semana||i==15-semana||i==22-semana||i==29-semana || i== 36-semana)
				printf("\n%d\t",i);
			else	
				printf("%d\t",i);
		}
// los i==8-semana... y los otros es para que la condicional cada 7 dias imprima un \n es decir
// baje de linea y prosiga imprimiendo el calendario en un cuadrado...
 
printf("\n\nDesea Buscar otra Fecha? \n\t1=SI 0=NO\t>>> ");
scanf("%d",&seleccion);
 
while (seleccion<0 || seleccion>1)
{
printf("ERROR, Ingrese 1/0\n");
printf("Desea Buscar otra Fecha? \n\t1=SI 0=NO\t>>> ");
scanf("%d",&seleccion);
}
 
if (seleccion == 1)
{
printf("\nIngrese Mes: ");
scanf("%d",&mes);
 
mes-=1;
// Al inicio agregamos +1 al mes, ya que contábamos los meses de 0-11,
// esta vez estamos contando de 1-12, por lo que le restamos uno.
// Asi cuando el ciclo empiece de nuevo sumara 1, dejando el mes en el valor que deseamos.
 
printf ("Ingrese Anio: ");
scanf("%d",&anio);
 
system("clear");//limpia pantalla (borra anterior calendario)
printf("\t=============================>CALENDARIO<=============================\n\n");
 
}
}//llave del while principal
 
}//llave del main.
 
//Este codigo corre perfectamente en Linux
//Probado y Compilado en Ubuntu, con GCC.
//Para su compatibilidad en Windows, solo es necesario cambiar los system ("clear"), por cls.
