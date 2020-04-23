import java.awt.*;
import javax.swing.*;

public class Lienzo extends JApplet {
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
		g.drawString("lINEZO",240,30);
		} 
	

class Pizarra extends Canvas{
	Pizarra(){
		setBackground(new Color(128,128,255));
		setSize(500,400);
			}
	public void paint(Graphics g){
		super.paint(g);
			g.drawString("Recta Trazada",100,300);
			/*aca podemos dibujar lineal cirunferencias etc*/
				} 
		} 	
}
