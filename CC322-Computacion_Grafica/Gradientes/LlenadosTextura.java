import java.awt.*;
import java.awt.Color;
import java.awt.Graphics.*;
import java.awt.geom.*;
import java.awt.image.*;
import javax.swing.*;

public class LlenadosTextura extends JApplet {
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
              BufferedImage bi = new BufferedImage(30,30,BufferedImage.TYPE_INT_RGB);
              Graphics2D gi = bi.createGraphics();
              gi.setColor(Color.green);
              gi.fillRect(0, 0, 15, 15);
              gi.setColor(Color.red);
              gi.drawRect(2,2,14,14);
              gi.setColor(Color.black);
              gi.fillRect(4, 4, 4, 4);
              Rectangle rect = new Rectangle(20,20);
              TexturePaint textura = new TexturePaint(bi, rect);
              Graphics2D g2 = (Graphics2D)g;
              g2.setPaint(textura);
              g2.fillOval(50,50,200,150);
            }
        
    } //fin Pizarra
    
  } //fin Applet

