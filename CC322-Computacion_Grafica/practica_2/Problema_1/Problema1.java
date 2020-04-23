// procedure bres_line graphic
import java.awt.*;
import java.awt.Color;
import java.awt.Graphics.*;
import java.awt.geom.*;
import java.awt.image.*;
import javax.swing.*;
import java.util.Scanner;

public class Problema1 extends JApplet {
	Pizarra a;
  int xcenter,ycenter,Radio,particiones;
  float[] partes;
  float[] angulos;
  float[] xlong;
  float[] ylong;
	public void init(){
		Container c=this.getContentPane();
		c.setLayout(null);
		c.setBackground(Color.yellow);
		a=new Pizarra();
		a.setBounds(50,50,500,400);
//		c.add(a);
		setSize(600,600);
		Scanner leer = new Scanner(System.in);
    System.out.println("Ingrese el centro del diagrama pastel y el radio\n");
    xcenter = leer.nextInt();
    ycenter = leer.nextInt();
    Radio = leer.nextInt();
    System.out.println("Ingrese el numero de particiones del pastel:\n");
    particiones = leer.nextInt();
    partes = new float[particiones];
    angulos = new float[particiones];
    xlong = new float[particiones];
    ylong = new float[particiones];
    int i=0;
    System.out.println("Ingrese las particiones del pastel:\n");
    while(i<particiones){
      partes[i] = leer.nextFloat();
      angulos[i]=360*partes[i]/100;
      System.out.println("angulo "+angulos[i]+" "+"\n");
      if(Math.sin(angulos[i])<0){
        ylong[i]=ycenter - Radio*(float)Math.sin(angulos[i]);
      }
      else{
        ylong[i] = Radio*(float)Math.sin(angulos[i]);
      }
      
      if(Math.cos(angulos[i])<0){
        xlong[i] = xcenter - Radio*(float)Math.cos(angulos[i]);
      }
      else{
        xlong[i] = Radio*(float)Math.cos(angulos[i]);
      }
      System.out.println("coordenadas: "+(int)xlong[i]+" "+(int)ylong[i]+"\n");
      i++;
    }
    System.out.println("Graficando el pastel:\n");
    
	}
	
	public void paint(Graphics g){
		super.paint(g);
//		bresahamLine(g,3,4,12,50);
    int i=0;
    while(i<particiones){
      bresahamLine(g,xcenter,ycenter,(int)xlong[i]+1,(int)ylong[i]-1);
      i++;
    }
		bresahamCircle(g,xcenter,ycenter,Radio);
		} 
	

class Pizarra extends Canvas{
            
    Pizarra()
    {
        setBackground(new Color(128,128,255));
        setSize(500,400);
    }      
    
    
    public void paint(Graphics g)
            { 
              super.paint(g);/*
              Graphics2D g2 = (Graphics2D) g;
              GradientPaint patron = new GradientPaint(50,150,Color.red,getWidth(),0,Color.yellow,true);
              g2.setPaint(patron);
              
              g2.fillRect(50, 50, 100, 80);
              patron = new GradientPaint(0,200,Color.blue,200,0,Color.white,true);
              g2.setPaint(patron);
              
              g2.fillOval(200,50,100,50);
              Polygon p = new Polygon();
              p.addPoint(100, 100);
              p.addPoint(300, 250);
              p.addPoint(200, 350);
              patron = new GradientPaint(100,60,Color.blue,100,150,Color.yellow,true);
              g2.setPaint(patron);
              g2.fillPolygon(p);
              int x[] = {400,450,300,200,100};
              int y[] = {80,60,300,350,50};*/
              //g.setColor(Color.pink);
              //g.fillPolygon(x,y,5);
            }
        
    } //fin Pizarra
    /*
    public void bresahamLine(Graphics g,int x1,int y1,int x2,int y2){
	int dx,dy,x,y,x_end,p,const1,const2;
	dx = Math.abs(x1-x2);
	dy = Math.abs(y1-y2);
	p = 2*dy - dx;
	const1 = 2*dy;
	const2 = 2*(dy-dx);
	if(x1>x2){
		x=x2;y=y2;
		x_end = x1;
	}
	else{
		x = x1;y=y1;
		x_end = x2;
	}
	g.drawLine(x,y,x,y);
	while(x<x_end){
		x=x+1;
		if(p<0)	p=p+const1;
		else{
			y=y+1;
			p=p+const2;
		}
		g.drawLine(x,y,x,y);
	}
}*/

public void bresahamLine(Graphics g,int x0, int y0, int x1, int y1) { 
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

  public void bresahamCircle(Graphics g,int xc, int yc,int r){  
    int x = 0, y = r;
    int d = 3 - 2*r;
    while(x<y)
    {
      drawCircle(g,xc,yc,x,y);
      x++;
      if(d<0) d = d+4*x+6;
      else
      {
        y--;
        d = d+4*(x-y)+10;
      }
      drawCircle(g,xc,yc,x,y);
    }
  }
  public void drawCircle(Graphics g,int xc,int yc,int x,int y){
    g.drawLine(xc+x,yc+y,xc+x,yc+y);
    g.drawLine(xc-x,yc+y,xc-x,yc+y);
    g.drawLine(xc+x,yc-y,xc+x,yc-y);
    g.drawLine(xc-x,yc-y,xc-x,yc-y);
    g.drawLine(xc+y,yc+x,xc+y,yc+x);
    g.drawLine(xc-y,yc+x,xc-y,yc+x);
    g.drawLine(xc+y,yc-x,xc+y,yc-x);
    g.drawLine(xc-y,yc-x,xc-y,yc-x);
  }
    /*int radius=(int)(Math.sqrt((xf-xi)*(xf-xi)+(yf-yi)*(yf-yi)));  
  
    int d1 = 3 - (2 * radius);  
    int x = 0,i1=x1,i2=x2;  
  
    int y = radius;  
    boolean rov=true;  
  
    // for one eights, while x is not >= y  
    while (rov){  
        if (x>=y){rov=false;}  
        if (d1 < 0) { d1 = d1 + (4 * x) + 6; }  
        else{ d1 = d1 + 4 * (x - y) + 10; // (1)  
            y = y - 1;  
        }  
      
        // draw following circle points   
        g.drawLine((x1+x),(y1+y));  
        g.drawLine((x1+x),(y1-y));  
        g.drawLine((x1-x),(y1+y));  
        g.drawLine((x1-x),(y1-y));  
          
        g.drawLine((x1+y),(y1+x));  
        g.drawLine((x1+y),(y1-x));  
        g.drawLine((x1-y),(y1+x));  
        g.drawLine((x1-y),(y1-x));  
        x++;  
    }*/  
  } //fin Applet
  
