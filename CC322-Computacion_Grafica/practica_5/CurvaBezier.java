package GraficoBernstein;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class CurvaBezier {
	
	private static BufferedReader br = new BufferedReader(
			new InputStreamReader(System.in));
	private static boolean continuar=true;
	
	public static int factorial(int n){
        
        if(n==0)
            return 1;
        else
           return n*factorial(n-1);
    }
     
	public static void factorialN() throws NumberFormatException, IOException{
		System.out.println("Ingrese Numero");
		int n=Integer.parseInt(br.readLine());
		if(n>0){
		int fact=factorial(n);
		System.out.println("El factorial de "+n+" es "+fact);
		System.out.println("Desea continuar?(s/n)");
		char cont=br.readLine().charAt(0);
		if(cont=='s')continuar=true;
		else continuar=false;
		}
		else {
			System.out.println("el numero no puede ser menor a 0");
			System.out.println("el numero debe ser Natural");
			factorialN();
		}
	}
	
	public static int combinatorio(int n,int k){
		return (factorial(n)/(factorial(k)*factorial(n-k)));
		 
		
	}
	
	public static void combinatorioN() throws NumberFormatException, IOException {
		System.out.println("Ingrese Numero");
		int n=Integer.parseInt(br.readLine());
		System.out.println("Ingrese k");
		int k=Integer.parseInt(br.readLine());
		if(n>=k){
			int comb=combinatorio(n, k);
			System.out.println("el combinatorio de los numero es "+ comb);
			System.out.println("Desea continuar?(s/n)");
			char cont=br.readLine().charAt(0);
			if(cont=='s')continuar=true;
			else continuar=false;
		}
			else {
				System.out.println("el numero no puede ser menor a k");
				combinatorioN();
			}
		
	}
	
	public static double polibernstein(int n, int k, double t){
		return (combinatorio(n, k))*Math.pow(t, k)*Math.pow((1-t),(n-k));
		
	}
	public static void Bernstein() throws NumberFormatException, IOException {
		boolean error=false;

		System.out.println("Ingrese Numero");
		int n=Integer.parseInt(br.readLine());
		System.out.println("Ingrese k");
		int k=Integer.parseInt(br.readLine());
		if(n>=k){
		System.out.println("B "+n+" "+k+" = "+combinatorio(n, k)+".t"+k+".(1-t)"+(n-k));
		do{
		System.out.println("Ingrese t");
		double t=Double.parseDouble(br.readLine());
		if(t>=0 || t<=1){
			System.out.println("B "+n+" "+k+" = "+polibernstein(n,k,t));
			
		
		}
		else {
			error=true;
		}
		}while(error);
		
		System.out.println("Desea continuar?(s/n)");
		char cont=br.readLine().charAt(0);
		if(cont=='s')continuar=true;
		else continuar=false;
		
		
	}
		else {
			System.out.println("el numero no puede ser menor a k");
			Bernstein();
		}
		
	}
	
	
	
	public static void main(String[] args) throws IOException{
		
	while(continuar){
		System.out.println("************************************");
		System.out.println("Escoja su opcion");
		System.out.println("************************************");
		System.out.println("1.Calcular el Factorial de un numero");
		System.out.println("2.Calcular un numero combinatorio");
		System.out.println("3.Calcular polinomio de Bernstein");
		System.out.println("************************************");
		char respuesta=br.readLine().charAt(0);
		switch(respuesta){
		case '1': factorialN();break;
		case '2':combinatorioN();
		case '3':Bernstein();
		default:{continuar=false;
			System.out.println("byebye");break;}
		}
		
		}
	
		
		
		
	}

	

	
	
}

