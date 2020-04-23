import javax.swing.*;
import java.awt.*;
import java.lang.*;
import java.util.Scanner;

public class Problema1 extends Canvas{
  Polygon p=new Polygon();
  int lonx=1000,lony=650;
  Particula partycle=new Particula(lonx,lony);
  Scanner leer = new Scanner(System.in);
  Container c;

  public Problema1(int a,int b,int c,int d, float e, int f){
    partycle.setTrasX(a);
    partycle.setTrasY(b);
    partycle.setScale(c);
    partycle.setSubScale(d);
    partycle.setAng(e);
    partycle.setSubAng(f);
    this.setBackground(Color.black);
  }
  /*
  @Override
  public void init(){
      c=this.getContentPane();
      c.setLayout(null);
      c.setBackground(Color.white);
      partycle.setBounds(0,0,lonx,lony);
      c.add(l);
      c.setSize(lonx,lony); // las longuitudes el applet
  }
*/
  private void animar(){
    partycle.move();
  }

  public void paint(Graphics g){
      super.paint(g);
      Graphics2D g2d = (Graphics2D) g;
      Particula.paint(g);
  }
  public static void main(String[] args)throws InterruptedException {
      System.out.println("Ingrese la cantidad a moverse en X: ");
      int dx = leer.nextInt(); // -25
      System.out.println("Ingrese la cantidad a moverse en Y: ");
      int dy = leer.nextInt(); // -50
      System.out.println("Ingrese la cantidad multiplo de Tamano: ");
      int escala = leer.nextInt(); // 3
      System.out.println("Ingrese la cantidad de pasos de incremento: ");
      int subescalas = leer.nextInt(); // 15
      System.out.println("Ingrese angulo a Rotar: ");
      float ang = leer.nextFloat(); // 15
      System.out.println("Ingrese subangulo: ");
      int subangulos = leer.nextInt(); // 60
    JFrame windows = new JFrame("Simulación Osiclacion Corporal");
    Problema1 celesteBody= new Problema1(dx,dy,escala,subescalas,ang,subangulos);
    windows.add(celesteBody);
    windows.setSize(lonx,lony);
    windows.setVisible(true);
    windows.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	
		while (true) {
			celesteBody.animar();
			celesteBody.repaint();
			Thread.sleep(60);
		}
  }
}
public  class Particula{
    private int lonx,lony;
    private int dx,dy,escala,subescalas,subangulos;
    private float ang;
    public Particula(int a,int b){
      this.lonx=a;
      this.lony=b;
    }

    public void paint(Graphics g){

      // graficando los EJES COORDENADOS
      g.drawLine(lonx/2,0,lonx/2,lony);
      g.drawLine(0,lony/2,lonx,lony/2);
      
      
      super.paint(g);
      g.setColor( Color.BLACK );
      

      //int z[][];
      // Dibujar poligono en origen de coordenadas
      //z = dibujarPoligono(g,p,40,0,0);
      //System.out.println("("+z[0][0]+","+z[1][0]+"),("+z[0][1]+","+z[1][1]+"),("+z[0][2]+","+z[1][2]+")\n");
      
      // El primer argumento y los otros 2 siguientes determinan la escala y el traslado
      //z = dibujarPoligono(g,p,60,-100,100);
      //z = dibujarPoligono(g,p,100,-200,-100);
      //z = dibujarPoligono(g,p,200,-200,-100);
      
      // Rota Poligono
      //rotarPoligono(g,p,40,-100,100,10);
      
      // Animaciones separadas
      //animarTraslacionPoligono(g,p,40,-100,-50,16);
      //animarEscalaPoligono(g,p,40,0,0,100);
      //animarRotacionPoligono(g,p,40,0,0,60,6);
      
      // animaciones compuestas
      //animarEscalaTraslacionPoligono(g,p,20,-100,-50,50,16);
      animarEscalaRotacionTraslacionPoligono(g,p,40,dx,dy,escala,subescalas,ang,subangulos);
      //distancia del centro al punto arriba, traslado en x, traslado en y, limite de incremento de la escala, intervalos de distancia, angulo, subangulos
      /*
      int x[];
      g.setColor(Color.RED);
      bresahamLine(g,500,325,550,450);      
      x = rotateLine(g,500,325,550,450,60);
      g.setColor(Color.GREEN);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      System.out.println("("+x[0]+","+x[1]+"),("+x[2]+","+x[3]+")\n");
      */
    }
    public int[] rotateLine(int x1,int y1,int x2,int y2,float ang){
    double x3,y3;
    if(ang<0){
      ang = 360 + ang;
    }
    x3=x1+(x2-x1)*Math.cos(ang*Math.PI/180)+(y2-y1)*Math.sin(ang*Math.PI/180);
    y3=y1-(x2-x1)*Math.sin(ang*Math.PI/180)+(y2-y1)*Math.cos(ang*Math.PI/180);
    int Rx=(int)(x3+0.5),Ry=(int)(y3+0.5);
    int x[]={x1,y1,Rx,Ry};
    return x;
    }
    
    public int[][] rotarPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,float ang){
    int x[] = {lonx/2+dx, lonx/2-(int)(dcenter/2*Math.sqrt(3.0))+dx, lonx/2+(int)(dcenter/2*Math.sqrt(3.0))+dx};
    int y[] = {(int)(lony/2-dcenter+dy), (int)(lony/2+dcenter/2+dy), (int)(lony/2+dcenter/2+dy)};
    int centrOval[]={x[0]-dcenter/8, y[0]+dcenter-4};
    int center[]={(int)x[0], (int)(y[0]+dcenter)};
    int w[];
    w=rotateLine(g,center[0],center[1],x[0],y[0],ang);
    x[0]=w[2];
    y[0]=w[3];
    w = rotateLine(g,center[0],center[1],x[1],y[1],ang);
    x[1]=w[2];
    y[1]=w[3];
    w = rotateLine(g,center[0],center[1],x[2],y[2],ang);
    x[2]=w[2];
    y[2]=w[3];
    g.setColor(Color.BLACK);
    g.drawLine(lonx/2,0,lonx/2,lony);
    g.drawLine(0,lony/2,lonx,lony/2);
    p=new Polygon(x,y,x.length);
    g.setColor(Color.green);
    g.fillPolygon(p);
    g.setColor(Color.red);
    g.fillOval(centrOval[0],centrOval[1], dcenter/4, dcenter/4);
    int z[][] = {x,y};
    return z;
    }
    
    public void animarEscalaRotacionTraslacionPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,int escala,int n,float ang,int m){
    int z[][];
    z = rotarPoligono(g,p,dcenter,0,0,0);
    int i;
    float hang=ang/m;
    float angulo=0;
    int h=dx/n;
    int k=dy/n;
    int limX=0,limY=0;
    int dcenter1=dcenter-1;
    int limX1=lonx,limY1=lony;
    int inc=1;
    int x=0,y=0;
    for(i=0;;i++){
      x = x + h;
      y = y + k;
      dcenter1 = dcenter1 + inc;
      angulo = angulo + hang;
      try {
        Thread.sleep(10);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
      z=rotarPoligono(g,p,dcenter1,x,y,angulo);
      if(dcenter1>escala*dcenter){
        inc=-inc;
      }
      if(dcenter1<10){
        inc=-inc;
      }
      if(z[0][0]<limX||z[0][1]<limX||z[0][2]<limX){
        h=-h;
      }
      if(z[0][0]>limX1||z[0][1]>limX1||z[0][2]>limX1){
        h=-h;
      }
      if(z[1][0]<limY||z[1][1]<limY||z[1][2]<limY){
        k=-k;
      }
      if(z[1][0]>limY1||z[1][1]>limY1||z[1][2]>limY1){
        k=-k;
      }
    }
    }
  }
