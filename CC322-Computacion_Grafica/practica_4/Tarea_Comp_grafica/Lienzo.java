package Tarea_Comp_grafica;
import java.awt.*;
import javax.swing.*;
//tamañ0 1400,750
public class Lienzo extends Canvas{
    private double sxt,syt,sx0=645,sy0=320;
    private double rf,r0=110;
    public float   sx=(float) 0.8,sy=(float) 0.8;
    private double x0=700,y0=375;//indica el centro del sistema solar
    private double x1=620,y1;//r=80
    private double x2=590,y2;//r=110
    private double x3=560,y3;//r=140
    private double x4=520,y4;//r=180
    private double x5=480,y5;//r=220
    private double x6=450,y6;//r=250
    private double x7=420,y7;//r=280
    private double x8=390,y8;//r=310
    private int t=0;
    int i=0,j=0,k=0,l=0,m=0,n=0,p=0,q=0;
    double dx1,dy1,dx2,dy2,dx3,dy3,dx4,dy4;
    double dx5,dy5,dx6,dy6,dx7,dy7,dx8,dy8;
    boolean inf1=true,inf2=true,inf3=true,inf4=true;
    boolean inf5=true,inf6=true,inf7=true,inf8=true;
    
    public Lienzo(){
        this.setBackground(Color.black);
            }
    
    @Override
    public void paint(Graphics g){
        super.paint(g);
        // orbitas de los planetas
        g.setColor(Color.WHITE);
        g.drawOval(620,295,160,160);
        g.drawOval(590,265,220,220);
        g.drawOval(560,235,280,280);
        g.drawOval(520,195,360,360);
        g.drawOval(480,155,440,440);
        g.drawOval(450,125,500,500);
        g.drawOval(420,95,560,560);
        g.drawOval(390,65,620,620);
       
        g.setColor(Color.ORANGE);//el sol
        g.fillOval((int)sxt,(int)syt,(int)rf,(int)rf);
         
        //pintado de los planetas
            g.setColor(Color.green);
        g.fillOval((int)x1,(int)y1,10,10);
            g.setColor(Color.MAGENTA);
        g.fillOval((int)x2,(int)y2,15,15);
            g.setColor(Color.BLUE);
        g.fillOval((int)x3,(int)y3,18,18);
            g.setColor(Color.RED);
        g.fillOval((int)x4,(int)y4,15,15);
            g.setColor(Color.LIGHT_GRAY);
        g.fillOval((int)x5,(int)y5,24,24);
            g.setColor(Color.CYAN);
        g.fillOval((int)x6,(int)y6,21,21);
            g.setColor(Color.pink);
        g.fillOval((int)x7,(int)y7,17,17);
            g.setColor(new Color(120,90,125));
        g.fillOval((int)x8,(int)y8,15,15);
        
        //estrellas y otros cuerpos
            g.setColor(Color.WHITE);
          for(int z=0;z<15;z++){
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
            g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
                                        }
          //meteoritos
           g.setColor(new Color(120,80,50));
           meteoros(g,1,-1);
           meteoros(g,2,-2);
           meteoros(g,1,-3);
           meteoros(g,2,-4);
    }
    //movimiento de los planetas
    public void move(){
        //ecuacion :  dv=Math.pow(Math.pow(50,2)-Math.pow(x-x0,2),0.5);
            if(t%10==0){
                sxt=sx0;
                syt=sy0;
                rf=r0;
                }
            else if(t%10==5){
                rf =r0*sx;
                sxt = x0 - rf/2;
                syt = y0 - rf/2;
                }
            else;    
            
            //primer planeta     
            if(i<=160 && inf1==true){
                dx1=1;
                dy1=Math.pow(Math.pow(80,2)-Math.pow(x1-x0,2),0.5);       }
            if(i<=160 && inf1==false){
                dx1=-1;
                dy1=(-1)*Math.pow(Math.pow(80,2)-Math.pow(x1-x0,2),0.5);  }
            if(i==161){
                i=0;
                inf1=!(inf1);   }
            
            //segundo planeta
            if(j<=220 && inf2==true){
                dx2=1;
                dy2=Math.pow(Math.pow(110,2)-Math.pow(x2-x0,2),0.5);       }
            if(j<=220 && inf2==false){
                dx2=-1;
                dy2=(-1)*Math.pow(Math.pow(110,2)-Math.pow(x2-x0,2),0.5);  }
            if(j==221){
                j=0;
                inf2=!(inf2);   }
            
            //tercer planeta
            if(k<=280 && inf3==true){
                dx3=1;
                dy3=Math.pow(Math.pow(140,2)-Math.pow(x3-x0,2),0.5);       }
            if(k<=280 && inf3==false){
                dx3=-1;
                dy3=(-1)*Math.pow(Math.pow(140,2)-Math.pow(x3-x0,2),0.5);  }
            if(k==281){
                k=0;
                inf3=!(inf3);   }
            
            //cuarto planeta
            if(l<=360 && inf4==true){
                dx4=1;
                dy4=Math.pow(Math.pow(180,2)-Math.pow(x4-x0,2),0.5);       }
            if(l<=360 && inf4==false){
                dx4=-1;
                dy4=(-1)*Math.pow(Math.pow(180,2)-Math.pow(x4-x0,2),0.5);  }
            if(l==361){
                l=0;
                inf4=!(inf4);   }
            
            //quinto planeta
             if(m<=440 && inf5==true){
                dx5=1;
                dy5=Math.pow(Math.pow(220,2)-Math.pow(x5-x0,2),0.5);       }
            if(m<=440 && inf5==false){
                dx5=-1;
                dy5=(-1)*Math.pow(Math.pow(220,2)-Math.pow(x5-x0,2),0.5);  }
            if(m==441){
                m=0;
                inf5=!(inf5);   }
            
            //sexto planeta
            if(n<=500 && inf6==true){
                dx6=1;
                dy6=Math.pow(Math.pow(250,2)-Math.pow(x6-x0,2),0.5);       }
            if(n<=500 && inf6==false){
                dx6=-1;
                dy6=(-1)*Math.pow(Math.pow(250,2)-Math.pow(x6-x0,2),0.5);  }
            if(n==501){
                n=0;
                inf6=!(inf6);   }
            
            //septimo planeta
            if(p<=560 && inf7==true){
                dx7=1;
                dy7=Math.pow(Math.pow(280,2)-Math.pow(x7-x0,2),0.5);       }
            if(p<=560 && inf7==false){
                dx7=-1;
                dy7=(-1)*Math.pow(Math.pow(280,2)-Math.pow(x7-x0,2),0.5);  }
            if(p==561){
                p=0;
                inf7=!(inf7);   }
            
            //octavo planeta
            if(q<=620 && inf8==true){
                dx8=1;
                dy8=Math.pow(Math.pow(310,2)-Math.pow(x8-x0,2),0.5);       }
            if(q<=620 && inf8==false){
                dx8=-1;
                dy8=(-1)*Math.pow(Math.pow(310,2)-Math.pow(x8-x0,2),0.5);  }
            if(q==621){
                q=0;
                inf8=!(inf8);   }
            
            i++;j++;k++;l++;
            m++;n++;p++;q++;
            t=t+5;
            x1=x1+dx1;
            y1=y0+dy1;
            x2=x2+dx2;
            y2=y0+dy2;
            x3=x3+dx3;
            y3=y0+dy3;
            x4=x4+dx4;
            y4=y0+dy4;
            x5=x5+dx5;
            y5=y0+dy5;
            x6=x6+dx6;
            y6=y0+dy6;
            x7=x7+dx7;
            y7=y0+dy7;
            x8=x8+dx8;
            y8=y0+dy8;
        }
    public void meteoros(Graphics g,int tx,int ty){
            int x,y,xf,yf;
            x=(int)(Math.random()*500+10);
            y=(int)(Math.random()*300+10);
            
            for(int i=0;i<400;i++){
            xf=x+tx*i;
            yf=y+tx*i;
            g.fillOval(xf, yf,5,5);
                    }
    
                }
    
}
