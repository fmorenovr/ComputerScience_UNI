package ejercicio1;

public class Transformaciones {

    public static void translate (Coordenada p,double tx,double ty){
        p.x(p.x()+tx);
        p.y(p.y()+ty);
    }
    public static void scale (Coordenada p,double sx,double sy){
        p.x(p.x()*sx);
        p.y(p.y()*sy);
    }
    public static void rotate (Coordenada p,double a){
        double sn = Math.sin(a*Math.PI/180);
        double cs = Math.cos(a*Math.PI/180);
        double x0=p.x();
        double y0=p.y();
        p.x(cs*x0 - sn*y0);
        p.y(cs*y0 + sn*x0);
    }
    public static void rotateFix (Coordenada p,double a,double xr,double yr){
        translate(p,-xr,-yr);
        rotate(p,a);
        translate(p,xr,yr);
    }
    public static void scaleFix (Coordenada p,double sx,double sy,double xf,double yf){
        translate(p,-xf,-yf);
        scale(p,sx,sy);
        translate(p,xf,yf);
    }
    public static void translatePoly(Coordenada p[],int n,double tx,double ty){
        for (int i = 0; i < n; i++) {
            translate(p[i],tx,ty);
        }
    }
}