package prac_domiciliaria;
import java.awt.*;
import javax.swing.*;
/* @author georgeprado  */
public class Galaxia extends Canvas{
    Sistema_solar gt90=new Sistema_solar(this);
  
    public Galaxia(){
        this.setBackground(Color.black);
                                            }
    
  
    private void move(){
            gt90.move();
                }
    
    @Override
    public void paint(Graphics g){
            super.paint(g);
            Graphics2D g2d = (Graphics2D) g;
            //g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
            gt90.paint(g2d);
            }

    public static void main(String[] args)throws InterruptedException {
           JFrame windows = new JFrame("Simulación Galaxia");
           Galaxia andromeda= new Galaxia();
           windows.add(andromeda);
           windows.setSize(1400,750);
           windows.setVisible(true);
           windows.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		while (true) {
			andromeda.move();
			andromeda.repaint();
			Thread.sleep(60);
		}
    }
    
}
