package mef;
import mef.TipoDispensador;
import mef.CajaRegistradora;
import java.lang.*;
import java.util.*;

public class MainCaja{
	public static void main(String[] args){
		CajaRegistradora cajaRe = new CajaRegistradora();
		TipoDispensador tipo1 = new TipoDispensador("Gaseosa");
		TipoDispensador tipo2 = new TipoDispensador("Travesuras",-2,5);
		TipoDispensador tipo3 = new TipoDispensador("Pop porn",15,20);
		TipoDispensador tipo4 = new TipoDispensador("Galleta Soda",25,-6);
		TipoDispensador tipoarray[] = {tipo1,tipo2,tipo3,tipo4};
		Scanner leer = new Scanner(System.in);
		int opcion;
		float monto,vuelto1;
		do{
			System.out.println("Bienvenido a la dispensadora FC-UNI\n");
			System.out.println("Para Elegir un producto ingrese:\n");
			System.out.println("1. por "+tipo1.getNroProductos()+" para "+tipo1.getNombre()+" con precio: "+tipo1.getCosto()+"\n");
		
			System.out.println("2. por "+tipo2.getNroProductos()+" para "+tipo2.getNombre()+" con precio: "+tipo2.getCosto()+"\n");
		
			System.out.println("3. por "+tipo3.getNroProductos()+" para "+tipo3.getNombre()+" con precio: "+tipo3.getCosto()+"\n");
		
			System.out.println("4. por "+tipo4.getNroProductos()+" para "+tipo4.getNombre()+" con precio: "+tipo4.getCosto()+"\n");
		
			System.out.println("5. Para Salir del programa\n");
			System.out.println("Ingrese opcion para la compra: ");
			opcion = leer.nextInt();
			System.out.println("Ingrese monto a depositar: ");
			monto = leer.nextFloat();
			vuelto1 = venderProducto(monto,cajaRe,tipoarray,opcion-1);
			System.out.println("su vuelto es: "+vuelto1+"\n");
		}while(opcion!=9 && opcion>0 && opcion <5);
		System.out.println("Hasta la vista!\n");
	}

	public static float venderProducto(float monto,CajaRegistradora caj,TipoDispensador tip[],int i){
		float vuelto=0;
		if(tip[i].getNroProductos()>0){
			if(monto>=tip[i].getCosto()){
				float precio = tip[i].getCosto();
				caj.aceptarMonto(precio);
				tip[i].hacerVenta();
				vuelto = monto - precio;
			}
			else{
				System.out.println("Monto no es suficiente para la compra\n");
				vuelto = monto;
			}
			return vuelto;
		}
		else{
			System.out.println("No hay productos para vender!\n");
			vuelto=monto;
			return vuelto;
		}
	}
}
