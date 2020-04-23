/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package animacion;

import java.awt.*;  
import java.awt.Canvas;
import java.awt.Color;
import static java.awt.Color.black;
import static java.awt.Color.red;
import static java.awt.Color.white;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.geom.Point2D;
import javax.swing.JApplet;

/**
 *
 * @author Childéric
 */
public class Animacion extends JApplet{
    Lienzo l;
    
    @Override
    public void init(){
        Container c=this.getContentPane();
        c.setLayout(null);
        Color background=new Color(238,238,209);
        c.setBackground(background);
        l=new Lienzo();
        l.setBounds(50,50,500,400);
        c.add(l);
        setSize(600,500);	
	}

    public void paint(Graphics g){
        super.paint(g);
        g.drawString(" Animación",240,30);
        g.setColor(new Color(128,128,255));
        g.fillRect(50,250,500,150);
    }
    
    class Lienzo extends Canvas{
        int x[]={25,0,150,125};
        int y[]={350,300,300,350};
        int palox[]={70,70,80,80};
        int paloy[]={350,200,200,350};
        int velax[]={20,70,70};
        int velay[]={225,200,250};
        int xx[]={150,150,175};
        int yy[]={100,75,(int)87.5};
	Lienzo(){
            setBackground(Color.red);
            setSize(500,400);
        }

        @Override
        public void paint(Graphics g){
            super.paint(g);
            int i,j;
            Graphics2D g2 = (Graphics2D) g;
            GradientPaint patron = new GradientPaint(250,500,new Color(0,0,205),250,250,new Color(185,211,238),true);
            g2.setPaint(patron);
            g2.fillRect(0,250,500,150);
            
            Point2D center = new Point2D.Float(400, 125);
            float radius = 50;
            float radius2 = 100;
            float[] dist = {0.0f, 0.7f, 1.0f};
            float[] dist2 = {0.0f, 0.3f, 1.0f};
            Color[] colors = {new Color(255,255,0), new Color(255,215,0), new Color(255,236,139)};
            RadialGradientPaint p = new RadialGradientPaint(center, radius, dist, colors);
            RadialGradientPaint p2 = new RadialGradientPaint(center, radius2, dist2, colors);
            
            g2.setPaint(p);
            g2.fillOval(375, 100, 50, 50);
            g.setColor(new Color (139,69,19));
            poly(g,x,y);
            poly(g,palox,paloy);
            g.setColor(white);
            poly(g,velax,velay);
            g.setColor(black);
            poly(g,xx,yy);
            rotateFix(g,xx,yy,150,125,90);
            rotateFix(g,xx,yy,150,125,180);
            rotateFix(g,xx,yy,150,125,270);
            
            for (i=0;i<500;i=i+25)
            {       
                try
                {
                    Thread.sleep(100); //Pausa de 100ms
                }
                catch(InterruptedException e) 
                {
                    e.printStackTrace();
                }
                
                //g.setColor(new Color(128,128,255));
                //g.fillRect(0, 250, 500, 150);
                g2.setPaint(patron);
                g2.fillRect(0,250,500,150);
                g.setColor(red);
                g.fillRect(0, 200, 500, 50);
                g.fillRect(100, 75, 200, 175);
                g.setColor(new Color (139,69,19));
                translate(g,x,y,i,0);
                translate(g,palox,paloy,i,0);
                g.setColor(white);
                translate(g,velax,velay,i,0);
                g.setColor(black);
                
                if (i%2 == 0)
                {
                rotateFix(g,xx,yy,150,125,45);
                rotateFix(g,xx,yy,150,125,135);
                rotateFix(g,xx,yy,150,125,225);
                rotateFix(g,xx,yy,150,125,315);
                }
                else
                {
                rotateFix(g,xx,yy,150,125,0);
                rotateFix(g,xx,yy,150,125,90);
                rotateFix(g,xx,yy,150,125,180);
                rotateFix(g,xx,yy,150,125,270); 
                }
                
                g.setColor(red);
                g.fillRect(350, 75, 100, 100);
                g2.setPaint(p2);
                scaleOvalFix(g,375,100,50,50,2,2,375,100);
                
                try
                {
                    Thread.sleep(500); // Pausa de 500ms
                }
                catch(InterruptedException e) 
                {
                    e.printStackTrace();
                }
                
                g.setColor(red);
                g.fillRect(350, 75, 100, 100);
                g2.setPaint(p);
                g.fillOval(375, 100, 50, 50);
            }
        }
        
        public void poly(Graphics g,int x[], int y[]){
            int tab=x.length;
            g.fillPolygon(x, y, tab);
                }
        
        public void translate(Graphics g, int x[], int y[], float tx,float ty){
                
                int i = 0;
                int tab = x.length;
                int[] xt = new int[tab];
                int[] yt = new int[tab];
                
                for(i=0;i<tab;i++)
                {
                    xt[i]=x[i]+(int)(tx+0.5); 
                    yt[i]=y[i]+(int)(ty+0.5);
                }
                    g.fillPolygon(xt, yt, tab);
        }
        
        public void puntos(Graphics g, int x, int y, int x1, int y1){
            super.paint(g);
            g.drawLine(x, y, x1, y1);
        }
        
        public void rotateFix(Graphics g,int x[], int y[], int xf, int yf, float ang){
            int i=0, tab=x.length;
            double sn = Math.sin(Math.toRadians(ang));
            double cs = Math.cos(Math.toRadians(ang));
            int[] x3 = new int[tab];
            int[] y3 = new int[tab];
            
            for (i=0;i<tab;i++)
            {
                x3[i]=(int) (xf+(x[i]-xf)*cs-(y[i]-yf)*sn);
                y3[i]=(int) (yf+(x[i]-xf)*sn+(y[i]-yf)*cs);
                //x3[i]=(int) (x[i]*cs - y[i]*sn);
                //y3[i]=(int) (y[i]*cs + x[i]*sn);
            }
            g.fillPolygon(x3,y3,tab);
        }
        
        
        /*public void rotate(Graphics g,int x1,int y1,int x2,int y2,float ang){
            double x3,y3;
            x3=x1+(x2-x1)*Math.cos(Math.toRadians(ang))-(y2-y1)*Math.sin(Math.toRadians(ang));
            y3=y1+(x2-x1)*Math.sin(Math.toRadians(ang))+(y2-y1)*Math.cos(Math.toRadians(ang));
            
            g.drawLine(x1,y1,(int)(x3+0.5),(int)(y3+0.5));
        }  */              
        
        public void scaleOvalFix(Graphics g, int x, int y, int x1, int y1, float sx, float sy, float xf, float yf){
            int f1, g1, xff, yff;
            
            //f1 = (int) (xf + (x-xf)*sx);
            //g1 = (int) (yf + (y-yf)*sy);
            f1 = (int) (x1*sx);
            g1 = (int) (y1*sy);
            xff = (int) (xf - x1/sx);
            yff = (int) (yf - y1/sy);
            
            g.fillOval(xff,yff,f1,g1);
      }
    
    }
}

