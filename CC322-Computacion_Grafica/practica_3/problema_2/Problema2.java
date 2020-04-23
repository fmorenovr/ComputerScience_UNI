import javax.swing.*;
import java.awt.*;

public class Problema2 extends JApplet {
    Lienzo l;
    int lonx=1000,lony=650;
    @Override
    public void init(){
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

        @Override
        public void paint(Graphics g){
	      super.paint(g);
	      // todo punto inicia en x = lonx, y = lony
        g.setColor( Color.BLACK );
	      g.drawLine(lonx/2,0,lonx/2,lony);
	      g.drawLine(0,lony/2,lonx,lony/2);
	      
        // Dibujamos la figura de altura 150 y longuitud 100
        g.setColor( Color.RED );
        bresahamLine(g,lonx/2,lony/2,lonx/2,lony/2-150);
        bresahamLine(g,lonx/2,lony/2-150,lonx/2+100,lony/2-150);
        bresahamLine(g,lonx/2+100,lony/2-150,lonx/2+100,lony/2-125);
        bresahamLine(g,lonx/2+100,lony/2-125,lonx/2+35,lony/2-125);
        bresahamLine(g,lonx/2+35,lony/2-125,lonx/2+35,lony/2);
        bresahamLine(g,lonx/2+35,lony/2,lonx/2,lony/2);
        
        // empezamos con la rotacion en 90
        g.setColor( Color.GREEN );
        int[] x1=new int[4];
        int[] x2=new int[4];
	      x1=rotate(g,lonx/2,lony/2,lonx/2,lony/2-150,90);
	      bresahamLine(g,x1[0],x1[1],x1[2],x1[3]);
	      //translate(g,x1[0],x1[1],x1[2],x1[3],150,150);
        x1=rotate(g,lonx/2,lony/2-150,lonx/2+100,lony/2-150,90);
        x2=translate(g,lonx/2,lony/2-150,lonx/2+100,lony/2-150,50,50);
        bresahamLine(g,x1[0],x1[1],x1[2],x1[3]);
        rotate(g,lonx/2+100,lony/2-150,lonx/2+100,lony/2-125,90);
        rotate(g,lonx/2+100,lony/2-125,lonx/2+35,lony/2-125,90);
        rotate(g,lonx/2+35,lony/2-125,lonx/2+35,lony/2,90);
        rotate(g,lonx/2+35,lony/2,lonx/2,lony/2,90);
        // empezamos la rotacion
        rotate(g,0,0,90,120,30);    
        //figure(g);
        }
        public void ptos(Graphics g,int x1,int y1,int x2,int y2){
            g.drawLine(x1, y1, x2, y2);
        }
        public void figure(Graphics g,int[] x,int[] y,int n){
          int i;
          for(i=0;i<n-1;i++)
            g.drawLine(x[i],y[i],x[i+1],y[i+1]);
          /*
          g.drawLine(0,6,4,6);
          g.drawLine(0,0,2,0);
          g.drawLine(2,0,2,3);
          g.drawLine(2,3,4,3);
          g.drawLine(4,3,4,4);
          g.drawLine(2,4,2,5);
          g.drawLine(2,5,4,5);
          g.drawLine(4,5,4,6);
          */
        }
        public int[] translate(Graphics g,int x1,int y1,int x2,int y2,float tx,float ty){
            int f1,f2,g1,g2;
            int[] coordenadas = new int[4];
            f1=x1+(int)(tx+0.5);
            f2=x2+(int)(tx+0.5);
            g1=y1+(int)(ty+0.5);
            g2=y2+(int)(ty+0.5);
            //g.drawLine(f1,g1,f2,g2);
            coordenadas[0]=f1;
            coordenadas[1]=f2;
            coordenadas[2]=g1;
            coordenadas[3]=g2;
            return coordenadas;
                
        }
        public int[] rotate(Graphics g,int x1,int y1,int x2,int y2,float ang){
            double x3,y3;
            int[] coordenadas = new int[4];
            x3=x1+(x2-x1)*Math.cos(Math.toRadians(ang))-(y2-y1)*Math.sin(Math.toRadians(ang));
            y3=y1+(x2-x1)*Math.sin(Math.toRadians(ang))+(y2-y1)*Math.cos(Math.toRadians(ang));
            
            //g.drawLine(x1,y1,(int)(x3+0.5),(int)(y3+0.5));
            coordenadas[0]=x1;
            coordenadas[1]=y1;
            coordenadas[2]=(int)(x3+0.5);
            coordenadas[3]=(int)(y3+0.5);
            return coordenadas;
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
