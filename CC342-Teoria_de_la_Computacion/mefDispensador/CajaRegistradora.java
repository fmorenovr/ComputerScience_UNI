package mef;
import java.util.*;

public class CajaRegistradora{
	private float cajaChica;
	public void aceptarMonto(float montoAbonado){
		this.cajaChica = this.cajaChica + montoAbonado;
	}
	CajaRegistradora(){
		cajaChica = 500;
	}
	public float getSaldoActual(){
		return cajaChica;
	}
}
