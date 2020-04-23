package ejercicio1;

public class Coordenada {
    private double x;
    private double y;
    Coordenada(double x0,double y0){
        x=x0;
        y=y0;
    }
    public double x(){
        return x;
    }
    public void x(double x){
        this.x=x;
    }
    public double y(){
        return y;
    }
    public void y(double y){
        this.y=y;
    }
}
