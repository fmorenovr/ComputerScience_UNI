import javax.swing.*;
import java.awt.*;

public class Traslacion extends JApplet {
    Lienzo l;
    
    @Override
    public void init(){
        Container c=this.getContentPane();
        c.setLayout(null);
        c.setBackground(Color.yellow);
        l=new Lienzo();
        l.setBounds(50,50,500,400);
        c.add(l);
        setSize(600,500);	
	}

    public void paint(Graphics g){
        super.paint(g);
        g.drawString(" LIENZO ",240,30);
                }
    
    class Lienzo extends Canvas{
        int x[]={50,100,150};
        int y[]={50,100,150};
	Lienzo(){
		setBackground(new Color(128,128,255));
		setSize(500,400);
			}

        @Override
        public void paint(Graphics g){
	super.paint(g);
        ptos(g,0,0,90,120);
	      translate(g,30,30,80,80,50,0);
        rotate(g,0,0,90,120,30);    
       
                        }
        public void ptos(Graphics g,int x1,int y1,int x2,int y2){
            g.drawLine(x1, y1, x2, y2);
                }
        
        public void translate(Graphics g,int x1,int y1,int x2,int y2,float tx,float ty){
            int f1,f2,g1,g2;
                f1=x1+(int)(tx+0.5);
                f2=x2+(int)(tx+0.5);
                g1=y1+(int)(ty+0.5);
                g2=y2+(int)(ty+0.5);
                g.drawLine(f1,g1,f2,g2);
                
                        }
        public void rotate(Graphics g,int x1,int y1,int x2,int y2,float ang){
            double x3,y3;
            x3=x1+(x2-x1)*Math.cos(Math.toRadians(ang))-(y2-y1)*Math.sin(Math.toRadians(ang));
            y3=y1+(x2-x1)*Math.sin(Math.toRadians(ang))+(y2-y1)*Math.cos(Math.toRadians(ang));
            
            g.drawLine(x1,y1,(int)(x3+0.5),(int)(y3+0.5));
            
                    }                
        //pi=Math.PI;
      }
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
    }

