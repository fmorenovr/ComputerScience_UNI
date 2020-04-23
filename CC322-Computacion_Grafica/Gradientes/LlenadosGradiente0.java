// procedure bres_line graphic
import java.awt.*;
import java.awt.Color;
import java.awt.Graphics.*;
import java.awt.geom.*;
import java.awt.image.*;
import javax.swing.*;

public class LlenadosGradiente0 extends JApplet {
	Pizarra a;
	
	public void init(){
		Container c=this.getContentPane();
		c.setLayout(null);
		c.setBackground(Color.yellow);
		a=new Pizarra();
		a.setBounds(50,50,500,400);
		c.add(a);
		setSize(600,600);
	}
	
	public void paint(Graphics g){
		super.paint(g);
		g.drawString("Pizarra",240,30);
		} 
	

class Pizarra extends Canvas{
            
    Pizarra()
    {
        setBackground(new Color(128,128,255));
        setSize(500,400);
    }      
    
    
    public void paint(Graphics g)
            { 
              super.paint(g);
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
              int y[] = {80,60,300,350,50};
              //g.setColor(Color.pink);
              //g.fillPolygon(x,y,5);
            }
        
    } //fin Pizarra
    public void bresaham(Graphics g,int x1,int y1,int x2,int y2){
	int dx,dy,x,y,x_end,p,const1,const2;
	dx = Math.abs(x1-x2);
	dy = Math.abs(x1-x2);
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
}
  } //fin Applet

