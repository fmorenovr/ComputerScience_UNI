import javax.swing.*;
import java.awt.*;
import java.lang.*;
import java.util.Scanner;

public class Problema1 extends JApplet{
  Particula l=new Particula();
  Polygon p=new Polygon();
  int lonx=1000,lony=700;
  Scanner leer = new Scanner(System.in);
  Container c;
  int x[] = new int[4];
  int y[] = new int[4];
  int z[][] = new int[2][4];
  public Problema1(){}
  
  @Override
  public void init(){
      c=this.getContentPane();
      c.setLayout(null);
      c.setBackground(Color.white);
      l.setBounds(0,0,lonx,lony);
      c.add(l);
      c.setSize(lonx,lony); // las longuitudes el applet
  }

  public void paint(Graphics g){
      super.paint(g);
  }
  class Particula extends Canvas{
    public Particula(){
      this.setBackground(Color.BLACK);
    }

    public void paint(Graphics g){

      // graficando los EJES COORDENADOS
      super.paint(g);
      
      // Escribiendo la letra
      g.setFont(new Font("TimesRoman", Font.PLAIN, 10));
      g.drawString("5",lonx/4-10,lony/4-50);
      g.drawString("5",lonx/4+50,lony/4+10);
      
      // Rectas
      
      g.setColor(Color.MAGENTA);
      
      int x0[]={lonx/4,lonx/4,lonx/4+50,lonx/4+50,lonx/4+20,lonx/4+20,lonx/4+50,lonx/4+50,lonx/4+20,lonx/4+20,lonx/4+50,lonx/4+50};
      int y0[]={lony/4,lony/4-50,lony/4-50,lony/4-40,lony/4-40,lony/4-30,lony/4 -30,lony/4-20,lony/4-20,lony/4-10,lony/4-10,lony/4};
      Polygon p0=new Polygon(x0,y0,x0.length);
      g.fillPolygon(p0);

      z = rotarAgrandarPoligono(x0,y0);
      x=z[0];
      y=z[1];
      Polygon p1=new Polygon(x,y,x.length);
      g.fillPolygon(p1);

      int x8[]={lonx/2+200,lonx/2-200,lonx/2-200,lonx/2+200};
      int y8[]={3*lony/4-100,3*lony/4-100,3*lony/4-180,3*lony/4-180};
      Polygon p8=new Polygon(x8,y8,x8.length);
      g.fillPolygon(p8);
      
      
      g.setColor(Color.green);
      int x4[]={3*lonx/4-100,3*lonx/4-50,3*lonx/4+50,3*lonx/4+100,3*lonx/4};
      int y4[]={lony/4,lony/4-50,lony/4-50,lony/4,lony/4+100};
      Polygon p4=new Polygon(x4,y4,x4.length);
      g.fillPolygon(p4);
      
      g.setColor(Color.green);
      int x7[]={lonx/2,lonx/2+200,lonx/2+200,lonx/2-200,lonx/2-200};
      int y7[]={3*lony/4-100,3*lony/4-50,3*lony/4,3*lony/4,3*lony/4-100};
      Polygon p7=new Polygon(x7,y7,x7.length);
      g.fillPolygon(p7);
      
      g.setColor(Color.blue);
      int x5[]={3*lonx/4-50,3*lonx/4,3*lonx/4+50};
      int y5[]={lony/4-50,lony/4-100,lony/4-50};
      Polygon p5=new Polygon(x5,y5,x5.length);
      g.fillPolygon(p5);
      
      int x6[]={lonx/2,lonx/2+200,lonx/2+200};
      int y6[]={3*lony/4-100,3*lony/4-100,3*lony/4-50};
      Polygon p6=new Polygon(x6,y6,x6.length);
      g.fillPolygon(p6);
      
      g.setColor( Color.WHITE );
      g.drawLine(lonx/2,0,lonx/2,lony);
      g.drawLine(0,lony/2,lonx,lony/2);
      g.drawLine(lonx/4,0,lonx/4,lony/2);
      g.drawLine(0,lony/4,lonx,lony/4);
      g.drawLine(3*lonx/4,0,3*lonx/4,lony/2);
      g.drawLine(0,3*lony/4,lonx,3*lony/4);
      
      /*
      bresahamLine(g,lonx/4,lony/4,lonx/4,lony/4-50); // |
      bresahamLine(g,lonx/4,lony/4,lonx/4+50,lony/4); // --
      bresahamLine(g,lonx/4,lony/4-50,lonx/4+50,lony/4-50); // 1-
      bresahamLine(g,lonx/4+50,lony/4-50,lonx/4+50,lony/4-40); // 1|
      bresahamLine(g,lonx/4+20,lony/4-40,lonx/4+50,lony/4-40); // 2-
      bresahamLine(g,lonx/4+20,lony/4-40,lonx/4+20,lony/4-30); // 2|
      bresahamLine(g,lonx/4+20,lony/4-30,lonx/4+50,lony/4-30); // 3-
      bresahamLine(g,lonx/4+50,lony/4-30,lonx/4+50,lony/4-20); // 3|
      bresahamLine(g,lonx/4+20,lony/4-20,lonx/4+50,lony/4-20); // 4-
      bresahamLine(g,lonx/4+20,lony/4-20,lonx/4+20,lony/4-10); // 4|
      bresahamLine(g,lonx/4+20,lony/4-10,lonx/4+50,lony/4-10); // 5-
      bresahamLine(g,lonx/4+50,lony/4-10,lonx/4+50,lony/4); // 5|
      
      // rotar
      g.setColor(Color.GREEN);
      x = rotateLine(g,lonx/4,lony/4,lonx/4,lony/4-50,90); // |
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4,lony/4,lonx/4+50,lony/4,90); // -
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4,lony/4-50,lonx/4+50,lony/4-50,90); // 1-
      y = translateLine(x[0],x[1],x[2],x[3],-150,50);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+50,lony/4-50,lonx/4+50,lony/4-40,90); // 1|
      y = translateLine(x[0],x[1],x[2],x[3],-200,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-40,lonx/4+50,lony/4-40,90); // 2-
      y = translateLine(x[0],x[1],x[2],x[3],-160,+20);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-40,lonx/4+20,lony/4-30,90); // 2|
      y = translateLine(x[0],x[1],x[2],x[3],-150,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-30,lonx/4+50,lony/4-30,90); // 2-
      y = translateLine(x[0],x[1],x[2],x[3],-150,+20);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+50,lony/4-30,lonx/4+50,lony/4-20,90);
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-20,lonx/4+50,lony/4-20,90);
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-20,lonx/4+20,lony/4-10,90);
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+20,lony/4-10,lonx/4+50,lony/4-10,90);
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      
      x = rotateLine(g,lonx/4+50,lony/4-10,lonx/4+50,lony/4,90);
      y = translateLine(x[0],x[1],x[2],x[3],-100,0);
      bresahamLine(g,x[0],x[1],x[2],x[3]);
      g.setColor(Color.BLUE);
      bresahamLine(g,y[0],y[1],y[2],y[3]);
      g.setColor(Color.GREEN);
      */

      
    }
    
    public int[][] rotarAgrandarPoligono(int a[],int b[]){
      
      int x1[]={lonx/2+200,lonx/2-200,lonx/2-200,lonx/2-120,lonx/2-120,lonx/2-80,lonx/2-80,lonx/2-40,lonx/2- 40,lonx/2,lonx/2,lonx/2+200};
      int y1[]={3*lony/4-100,3*lony/4-100,3*lony/4-300,3*lony/4-300,3*lony/4-180,3*lony/4-180,3*lony/4 -260,3*lony/4-260,3*lony/4-180,3*lony/4-180,3*lony/4-300,3*lony/4-100};
      int z[][]={x1,y1};
      return z;    
    }
    
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
    
    public int[] translateLine(int x1,int y1,int x2,int y2,float tx,float ty){
    int f1,f2,g1,g2;
    f1=x1+(int)(tx+0.5);
    f2=x2+(int)(tx+0.5);
    g1=y1+(int)(ty+0.5);
    g2=y2+(int)(ty+0.5);
    int x[]={f1,g1,f2,g2};
    //g.drawLine(f1,g1,f2,g2);
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
    this.repaint();
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

}
