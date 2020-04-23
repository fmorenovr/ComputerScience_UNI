package Tarea_Comp_grafica;
import javax.swing.JFrame;

public class Ventana extends JFrame {
    Lienzo panel;
    
    public Ventana(String nombre,int lonx,int lony,int dx,int dy,int subpaso,float escala,float ang,int subang){
        super(nombre);
        panel=new Lienzo(lonx,lony,dx,dy,subpaso,escala,ang,subang);
        add(panel);
        setSize(lonx,lony);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
                }
    }
