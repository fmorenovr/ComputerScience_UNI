import java.awt.*;
import javax.swing.*;

public class LienzoDDA extends JApplet {
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
		g.drawString("lIENZO",240,30);
		} 
	

class Pizarra extends Canvas{
	Pizarra(){
		setBackground(new Color(128,128,255));
		setSize(500,400);
			} 	
  public void DDA(int x0, int y0, int x1, int y1, Graphics g)
    {
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
        } else
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
	public void paint(Graphics g){
		super.paint(g);
			g.drawString("Recta Trazada",100,300);
			/*aca podemos dibujar lineal cirunferencias etc*/
				} 
		}
}
