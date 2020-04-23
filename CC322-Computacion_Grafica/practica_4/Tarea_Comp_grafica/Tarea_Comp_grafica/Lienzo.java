package Tarea_Comp_grafica;
import java.awt.*;
import javax.swing.*;
//tamañ0 1400,750
public class Lienzo extends Canvas{
    private int lonx,lony;
    
    // Cuerpo de Estrella
    private int dx,dy,subpaso,subang;
    private float escala;
    private float ang;
    private float hang;
    private float angulo=0;
    private int h,k;
    private int limX=0,limY=0,limX1,limY1;
    private int inc=1;
    private int x=0,y=0;
    private int dcenter=45;
    private int dcenter1=dcenter-1;
    Polygon p = new Polygon();
    private int ordenadas[] = new int[3]; // y
    private int abscisas[] = new int[3]; // x
    private int center[] = new int[2];
    private int centrOval[] = new int[2];
    private int w[] = new int[4];
    private int centerCir[] = new int[2];
    private int movX=0,movY=0;
    
    // Cuerpo circular
    private int centroCir[] = new int[2];
    private int xcir=0,ycir=0;
    private int fontSize = 20;
    private boolean inf = true;
    private int i=0;
    
    public Lienzo(int heigth,int width,int delX,int delY,int subPasos, float scala,float Ang,int subAng){
        this.setBackground(Color.black);
        this.lonx=heigth;
        this.lony=width;
        this.dx = delX;
        this.dy = delY;
        this.escala = scala;
        this.subpaso=subPasos;
        this.ang = Ang;
        this.subang = subAng;
        this.hang = Ang/subAng;
        this.h=delX/subPasos;
        this.k=delY/subPasos;
        this.limX1=heigth;
        this.limY1=width;
            }
    public Lienzo(){
        this.setBackground(Color.black);
            }
    @Override
    public void paint(Graphics g){
        super.paint(g);
        
      // Cuerpo Triangular
      g.setColor(Color.white);
      g.setFont(new Font("TimesRoman", Font.PLAIN, fontSize));
      g.drawString("Cuerpos Celestes Computacion Grafica 2015 Meow!",lonx/2-300,25);
      g.setColor(Color.orange);
      g.setFont(new Font("TimesRoman", Font.PLAIN, fontSize+5));
      g.drawString("Moreno Vera, Felipe Adrian",10,lony-30);
      
      Polygon pol=new Polygon(abscisas,ordenadas,abscisas.length);
      g.setColor(new Color(255,45,84));
      g.fillPolygon(pol);
      g.setColor(Color.blue);
      g.fillOval(centrOval[0],centrOval[1], dcenter1/4, dcenter1/4);
      
      // orbita
      g.setColor(Color.white);
      g.drawOval((int)(centrOval[0]-1.5*dcenter1),(int)(centrOval[1]-dcenter1*1.5),dcenter1*3,dcenter1*3);
      
      centerCir[0] = centrOval[0]-(int)(1.5*dcenter1)-15 + movX;
      centerCir[1] = centrOval[1] + movY;
      
      // cuerpo circular
      g.setColor(Color.yellow);
      g.fillOval(centerCir[0],centerCir[1],30,30);
        //estrellas y otros cuerpos
        g.setColor(Color.WHITE);
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
        g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
        g.fillOval((int)(Math.random()*1000+50),(int)(Math.random()*650+50),3,3);
    }
    
    public int[] rotateLine(int x1,int y1,int x2,int y2,float ang){
      double x3,y3;
      if(ang<0){
        ang = 360 + ang;
      }
      x3=x1+(x2-x1)*Math.cos(ang*Math.PI/180)+(y2-y1)*Math.sin(ang*Math.PI/180);
      y3=y1-(x2-x1)*Math.sin(ang*Math.PI/180)+(y2-y1)*Math.cos(ang*Math.PI/180);
      //g.drawLine(x1,y1,(int)(x3+0.5),(int)(y3+0.5));
      int Rx=(int)(x3+0.5),Ry=(int)(y3+0.5);
      int x[]={x1,y1,Rx,Ry};
      return x;
    }
    public void move(){
      x = x + h;
      y = y + k;
      dcenter1 = dcenter1 + inc;
      angulo = angulo + hang;
      try {
        Thread.sleep(10);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
      abscisas[0] = lonx/2 + x;
      abscisas[1] = lonx/2-(int)(dcenter1/2*Math.sqrt(3.0))+x;
      abscisas[2] = lonx/2+(int)(dcenter1/2*Math.sqrt(3.0))+x;
      
      ordenadas[0] = (int)(lony/2-dcenter1+y);
      ordenadas[1] = (int)(lony/2+dcenter1/2+y);
      ordenadas[2] = (int)(lony/2+dcenter1/2+y);
      center[0] = abscisas[0];
      center[1] = ordenadas[0]+dcenter1;

      centrOval[0] = abscisas[0] - dcenter1/8;
      centrOval[1] = ordenadas[0] +dcenter1-4;
      w=rotateLine(center[0],center[1],abscisas[0],ordenadas[0],angulo);
      abscisas[0]=w[2];
      ordenadas[0]=w[3];
      w = rotateLine(center[0],center[1],abscisas[1],ordenadas[1],angulo);
      abscisas[1]=w[2];
      ordenadas[1]=w[3];
      w = rotateLine(center[0],center[1],abscisas[2],ordenadas[2],angulo);
      abscisas[2]=w[2];
      ordenadas[2]=w[3];
      if(dcenter1>(int)(escala*dcenter)){
        inc=-inc;
      }
      if(dcenter1<dcenter){
        inc=-inc;
      }
      if((abscisas[0]<limX||abscisas[1]<limX||abscisas[2]<limX)||(abscisas[0]>limX1||abscisas[1]>limX1||abscisas[2]>limX1)){
        h=-h;
      }
      if((ordenadas[0]<limY||ordenadas[1]<limY||ordenadas[2]<limY)||(ordenadas[0]>limY1||ordenadas[1]>limY1||ordenadas[2]>limY1)){
        k=-k;
      }
      if(movX<=3*dcenter1 && inf==true){ // hacia abajo y derecha
          movX+=1;
          movY=(int)(Math.sqrt(Math.pow(1.5*dcenter1,2)-Math.pow(centrOval[0]-centerCir[0]-15,2)))-15;
       }
        if(movX>=0 && inf==false){ // hacia arriba e izquierda
          movX-=1;
          movY=(-1)*(int)(Math.sqrt(Math.pow(1.5*dcenter1,2)-Math.pow(centrOval[0]-centerCir[0]-15,2)))-15;
        }
        if((movX==3*dcenter1+1)||(movX==-1)){ // de vuelta al inicio
          movY=0;
          inf=!(inf);
      }
    }
}
