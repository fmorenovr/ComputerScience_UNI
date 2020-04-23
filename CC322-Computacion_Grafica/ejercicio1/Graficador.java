package ejercicio1;
import java.awt.*;
import javax.swing.*;

public class Graficador extends JApplet{

    static int[] x = new int [3];
    static int[] y = new int [3];
    static Coordenada[] p = new Coordenada [3];
    static int xc,yc;
    
    public void init(){
        this.getContentPane().setBackground(Color.white);
        xc=900;
        yc=600;
        p[0] = new Coordenada(xc+200,yc-200);
        p[1] = new Coordenada(xc+400,yc-300);
        p[2] = new Coordenada(xc+300,yc-400);
        //Transformaciones.translatePoly(p, 3, -275, 275);
        /*for (int i = 0; i < 3; i++)
            Transformaciones.scale(p[i], 1.3, 1);*/
        x[0]=(int)p[0].x();
        x[1]=(int)p[1].x();
        x[2]=(int)p[2].x();
        y[0]=(int)p[0].y();
        y[1]=(int)p[1].y();
        y[2]=(int)p[2].y();
    }
    
    public void paint(Graphics g){
        super.paint(g);
        g.setColor(Color.blue);
        g.drawLine(xc-400, yc, xc+400, yc);
        g.drawLine(xc, yc+400, xc, yc-400);
        g.drawString("x",xc+410,yc+3);
        g.drawString("y",xc-3,yc-410);          
        g.setColor(Color.green);
        g.drawPolygon(x, y, 3);
        /*g.drawPolygon(x, y, 3);
        /*for (int i = 0; i < 3; i++) {
            Transformaciones.scale(p[i], 2, 2);
            x[i]=(int)p[i].x();
            y[i]=(int)p[i].y();
        }
        g.drawPolygon(x, y, 3);*/
       
      
    }
    
    public static void main(String[] args) {
        JFrame marco = new JFrame("Mi Marco");
        Graficador miApplet = new Graficador();
        
        Container c = marco.getContentPane();
        c.setLayout(null);
        miApplet.setBounds(100,0,2500,1500);  //posición del applet
        miApplet.init();
        //c.setBackground(Color.pink);
        //miApplet.setSize(300,300);
        
        c.add(miApplet);
        
        /*xc=500;
        Transformaciones.translatePoly(p, 3, 225, 25);
        for (int i = 0; i < 3; i++) {
            x[i]=(int)p[i].x();
            y[i]=(int)p[i].y();            
        }
        for (int i = 0; i < 3; i++) {
            System.out.println(x[i]);
            System.out.println(y[i]);
        }*/
        
        marco.setVisible(true);
        marco.setSize(600, 400);
        marco.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
}