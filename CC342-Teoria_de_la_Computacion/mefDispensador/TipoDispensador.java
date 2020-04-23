package mef;
import java.util.*;

public class TipoDispensador{
	private int nroProductos;
	private float costo;
	private String nombreProducto;

	public int getNroProductos(){
		return nroProductos;
	}
	public float getCosto(){
		return costo;
	}
	public String getNombre(){
		return nombreProducto;
	}
	public void hacerVenta(){
		this.nroProductos = this.nroProductos - 1;
	}
	TipoDispensador(String nombre){
		this.nombreProducto = nombre;
		this.costo = 3;
		this.nroProductos = 10;
	}
	TipoDispensador(String nombre,int nro,float precio){
		this.nombreProducto = nombre;
		if(precio < 0)	this.costo = 3;
		else 	this.costo = precio;
		if(nro<0)	this.nroProductos = 10;
		else	this.nroProductos = nro;
	}
}
