package prac_domiciliaria;
import java.awt.Color;
import java.awt.Graphics2D;
/* @author georgeprado */

public class Sistema_solar{
    private double x0=700;
    private double y0=375;
    private double x=620,y;
    int i=0;
    double dx,dy;
    boolean inf=true;

    public Sistema_solar(Galaxia gal){
    
                }
    
    public void move(){
        //ecuacion :  dv=Math.pow(Math.pow(50,2)-Math.pow(x-x0,2),0.5);
            if(i<=160 && inf==true){
                dx=1;
                dy=Math.pow(Math.pow(80,2)-Math.pow(x-x0,2),0.5);       }
            if(i<=160 && inf==false){
                dx=-1;
                dy=(-1)*Math.pow(Math.pow(80,2)-Math.pow(x-x0,2),0.5);  }
            if(i==161){
                i=0;
                inf=!(inf);
                //x=650;   
            }
            i++;
            x=x+dx;
            y=y0+dy;
                }
    
    public void paint(Graphics2D g){
        g.setColor(Color.WHITE);
        //g.drawLine(700,0,700,750);
        //g.drawLine(0,375,1400,375);
        g.setColor(Color.ORANGE);
        g.fillOval(645,320,110,110);
        g.setColor(Color.red);
        g.fillOval((int)x,(int)y,10,10);
            }
                  }
