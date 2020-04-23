import javax.swing.*;
import java.awt.*;
import java.lang.*;
import java.util.Scanner;

public class Problema1 extends JApplet{
  Lienzo l;
  Polygon p=new Polygon();
  int lonx=1000,lony=650;
  Scanner leer = new Scanner(System.in);

  @Override public void init(){
      Container c=this.getContentPane();
      c.setLayout(null);
      c.setBackground(Color.white);
      l=new Lienzo();
      l.setBounds(0,0,lonx,lony);
      c.add(l);
      setSize(lonx,lony);
  }

  public void paint(Graphics g){
      super.paint(g);
      g.drawString(" LIENZO ",240,30);
  }

  class Lienzo extends Canvas{
    Lienzo(){
      setBackground(new Color(255,255,255));
      setSize(lonx,lony);
    }

    @Override public void paint(Graphics g){
      System.out.println("Ingrese la cantidad a moverse en X: ");
      int x = leer.nextInt(); // -25
      System.out.println("Ingrese la cantidad a moverse en Y: ");
      int y = leer.nextInt(); // -50
      System.out.println("Ingrese la cantidad multiplo de Tamano: ");
      int escala = leer.nextInt(); // 3
      System.out.println("Ingrese la cantidad de pasos de incremento: ");
      int subescalas = leer.nextInt(); // 15
      System.out.println("Ingrese angulo a Rotar: ");
      float ang = leer.nextFloat(); // 15
      System.out.println("Ingrese subangulo: ");
      int subangulos = leer.nextInt(); // 60
      
      
      super.paint(g);
      g.setColor( Color.BLACK );
      
      // graficando los EJES COORDENADOS
      g.drawLine(lonx/2,0,lonx/2,lony);
      g.drawLine(0,lony/2,lonx,lony/2);

      int z[][];
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
      animarEscalaRotacionTraslacionPoligono(g,p,40,x,y,escala,subescalas,ang,subangulos);
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
  }

  public void ptos(Graphics g,int x1,int y1,int x2,int y2){
    g.drawLine(x1, y1, x2, y2);
  }

  public int[] translateLine(Graphics g,int x1,int y1,int x2,int y2,float tx,float ty){
    int f1,f2,g1,g2;
    f1=x1+(int)(tx+0.5);
    f2=x2+(int)(tx+0.5);
    g1=y1+(int)(ty+0.5);
    g2=y2+(int)(ty+0.5);
    int x[]={f1,f2,g1,g2};
    //g.drawLine(f1,g1,f2,g2);
    return x;
  }

  // rota en sentido antihorario
  public int[] rotateLine(Graphics g,int x1,int y1,int x2,int y2,float ang){
    double x3,y3;
    if(ang<0){
      ang = 360 + ang;
    }
    x3=x1+(x2-x1)*Math.cos(ang*Math.PI/180)+(y2-y1)*Math.sin(ang*Math.PI/180);
    y3=y1-(x2-x1)*Math.sin(ang*Math.PI/180)+(y2-y1)*Math.cos(ang*Math.PI/180);
    //g.drawLine(x1,y1,(int)(x3+0.5),(int)(y3+0.5));
    int Rx=(int)(x3+0.5),Ry=(int)(y3+0.5);
    int x[]={x1,y1,Rx,Ry};
    return x;
  }

  // distancia del centro al punto arriba, traslado en x, traslado en y.
  public int[][] dibujarPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy){
    int x[] = {lonx/2+dx, lonx/2-(int)(dcenter/2*Math.sqrt(3.0))+dx, lonx/2+(int)(dcenter/2*Math.sqrt(3.0))+dx};
    int y[] = {(int)(lony/2-dcenter+dy), (int)(lony/2+dcenter/2+dy), (int)(lony/2+dcenter/2+dy)};
    p=new Polygon(x,y,x.length);
    g.setColor(Color.green);
    g.fillPolygon(p);
    g.setColor(Color.red);
    g.fillOval(x[0]-dcenter/8, y[0]+dcenter-4, dcenter/4, dcenter/4);
    int z[][] = {x,y};
    return z;
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
    p=new Polygon(x,y,x.length);
    g.setColor(Color.green);
    g.fillPolygon(p);
    g.setColor(Color.red);
    g.fillOval(centrOval[0],centrOval[1], dcenter/4, dcenter/4);
    int z[][] = {x,y};
    return z;
  }

  // distancia del centro al punto de arriba, traslado en x, traslado en y, angulo, numero de subangulos
  public void animarRotacionPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,float ang,int n){
    int z[][];
    z = rotarPoligono(g,p,dcenter,dx,dy,0);
    int i;
    int hang=(int)(ang/n);
    int angulo=0;
    for(i=0;;i++){
      angulo = angulo + hang;
      z = rotarPoligono(g,p,dcenter,dx,dy,angulo);
    }
  }

  // distancia del centro al punto arriba, traslado en x, traslado en y, intervalos de distancia.
  public void animarTraslacionPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,int n){
    int z[][];
    z = dibujarPoligono(g,p,dcenter,dx,dy);
    int i;
    int h=dx/n;
    int k=dy/n;
    int limX=0,limY=0;
    int limX1=lonx,limY1=lony;
    int x=0,y=0;
    for(i=0;;i++){
      x = x + h;
      y = y + k;
      z=dibujarPoligono(g,p,dcenter,x,y);
      if(z[0][1]<limX){
        h=-h;
      }
      if(z[0][2]>limX1){
        h=-h;
      }
      if(z[1][0]<limY){
        k=-k;
      }
      if(z[1][2]>limY1){
        k=-k;
      }
    }
  }

  // distancia del centro al punto arriba, traslado en x, traslado en y, limite de incremento de la escala.
  public void animarEscalaPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,int limCenter){
    int z[][];
    z = dibujarPoligono(g,p,dcenter,dx,dy);
    int i;
    int dcenter1=dcenter-1;
    int inc=1;
    for(i=0;;i++){
      dcenter1 = dcenter1 + inc;
      z=dibujarPoligono(g,p,dcenter1,dx,dy);
      if(dcenter1>limCenter){
        inc=-inc;
      }
      if(dcenter1<0){
        inc=-inc;
      }
    }
  }

  // distancia del centro al punto arriba, traslado en x, traslado en y, limite de incremento de la escala, intervalos de distancia.
  public void animarEscalaTraslacionPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,int limCenter,int n){
    int z[][];
    z = dibujarPoligono(g,p,dcenter,dx,dy);
    int i;
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
      z=dibujarPoligono(g,p,dcenter1,x,y);
      if(dcenter1>limCenter){
        inc=-inc;
      }
      if(dcenter1<0){
        inc=-inc;
      }
      if(z[0][1]<limX){
        h=-h;
      }
      if(z[0][2]>limX1){
        h=-h;
      }
      if(z[1][0]<limY){
        k=-k;
      }
      if(z[1][2]>limY1){
        k=-k;
      }
    }
  }

  // distancia del centro al punto arriba, traslado en x, traslado en y, limite de incremento de la escala, intervalos de distancia, angulo, subangulos
  public void animarEscalaRotacionTraslacionPoligono(Graphics g,Polygon p,int dcenter,int dx,int dy,int limCenter,int n,float ang,int m){
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
      if(dcenter1>limCenter*dcenter){
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

  public void DDA(int x0, int y0, int x1, int y1, Graphics g){
    int dx = x1 - x0;
    int dy = y1 - y0;

    g.drawLine( x0, y0, x1, y1);
    if (Math.abs(dx) > Math.abs(dy)) {          // pendiente < 1
      float m = (float) dy / (float) dx;
      float b = y0 - m*x0;
      if(dx<0)
      dx =  -1;
      else
      dx =  1;
      while (x0 != x1) {
        x0 += dx;
        y0 = Math.round(m*x0 + b);
        g.drawLine( x0, y0, x1, y1);
      }
    } else {
      if (dy != 0) {                              // slope >= 1
        float m = (float) dx / (float) dy;      // compute slope
        float b = x0 - m*y0;
        if(dy<0)
        dy =  -1;
        else
        dy =  1;
        while (y0 != y1) {
          y0 += dy;
          x0 = Math.round(m*y0 + b);
          g.drawLine( x0, y0, x0, y0);
        }
      }
    }
  }

  public void bresahamLine(Graphics g,int x0, int y0, int x1, int y1){
    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    dx = (x1 - x0);
    dy = (y1 - y0);
    if (dy < 0) { 
      dy = -dy; 
      stepy = -1; 
    } 
    else {
      stepy = 1;
    }
    if (dx < 0) {  
      dx = -dx;  
      stepx = -1; 
    } 
    else {
      stepx = 1;
    }
    x = x0;
    y = y0;
    g.drawLine( x0, y0, x0, y0);
    if(dx>dy){
      p = 2*dy - dx;
      incE = 2*dy;
      incNE = 2*(dy-dx);
      while (x != x1){
        x = x + stepx;
        if (p < 0){
          p = p + incE;
        }
        else {
          y = y + stepy;
          p = p + incNE;
        }
        g.drawLine( x, y, x, y);
      }
    }
    else{
      p = 2*dx - dy;
      incE = 2*dx;
      incNE = 2*(dx-dy);
      while (y != y1){
        y = y + stepy;
        if (p < 0){
          p = p + incE;
        }
        else {
          x = x + stepx;
          p = p + incNE;
        }
        g.drawLine( x, y, x, y);
      }
    }
  }
}
