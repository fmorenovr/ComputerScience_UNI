import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.GeneralPath;

public class BSpline {
	static GeneralPath path=null;

	public static void dibujar(Graphics graph,float pX[],float pY[]){

		int n=pX.length-1, m=3;
		int y[]= new int[n+m+1];
		int ubicacion=0;
		float cdX,cdY,sumparcial;

		double incremento=1.0*(n-m+2)/100;


		if(path==null) path=new GeneralPath();
		else path.reset();

		generaNodos(m,n,y);


		for(double t=0.0; t<n-m+2;t=t+incremento){

			cdX=cdY=0;
			for(int k=0;k<=n;k++){
				cdX += pX[k]*N(k,m,t,y);
				cdY += pY[k]*N(k,m,t,y);

			}

                     // System.out.println("t="+t);
                        //  System.out.println(cdX);
                      //  System.out.println(cdY);
				if(ubicacion==0){
				path.moveTo((float)cdX, (float)cdY);
				ubicacion++;
				}
				else  path.lineTo((float)cdX, (float)cdY);

				
		}
                                path.lineTo(pX[n], pY[n]);

				Graphics2D graph2=(Graphics2D)graph;
				graph2.draw(path);
	}

	public static void redibujar(Graphics graph){
		if(path==null) return;
		Graphics2D graph2=(Graphics2D) graph;
		graph2.draw(path);
	}

	public static double N(int k, int m, double t, int[] y) {
		if(m==1)
			return ((double)y[k]<=t)&&(t<(double)y[k+1])?1:0;
		else{
			double d1,d2,N=0;
			d1=y[k+m-1]-y[k];
			if(d1 != 0)
				N=(t-y[k])*N(k,m-1,t,y)/d1;

			d2=y[k+m]-y[k+1];
			if(d2!=0)
				N=N+(y[k+m]-t)*N(k+1,m-1,t,y)/d2;
			return N;
		}
	}

	public static void generaNodos(int m, int n, int[] y) {

		if(n<m-1) return;
		for(int i=0;i<=n+m;i++)
			if(i<m) y[i]=0;
			else
				if(i<=n)y[i]=i-m+1;
				else y[i]=n-m+2;
	}



}
