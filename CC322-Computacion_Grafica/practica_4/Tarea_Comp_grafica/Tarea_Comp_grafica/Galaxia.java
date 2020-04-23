package Tarea_Comp_grafica;
import java.util.Scanner;


public class Galaxia {
    static Scanner leer = new Scanner(System.in);
    public static void main(String[] args)throws InterruptedException {
    System.out.println("Ingrese la cantidad a moverse en X: ");
      int dx = leer.nextInt(); // -25
      System.out.println("Ingrese la cantidad a moverse en Y: ");
      int dy = leer.nextInt(); // -50
      //System.out.println("Ingrese la cantidad de pasos de traslado: ");
      //int subpasos = leer.nextInt(); // 15
      System.out.println("Ingrese la cantidad multiplo de Tamano: ");
      float escala = leer.nextFloat(); // 2
      System.out.println("Ingrese angulo a Rotar: ");
      float ang = leer.nextFloat(); // 15
      //System.out.println("Ingrese subangulo: ");
      //int subang = leer.nextInt(); // 60
        Ventana windows = new Ventana("Galaxia",1200,650,dx,dy,10,escala,ang,20);
	windows.setVisible(true);
        while(true){
          windows.panel.move();
          windows.panel.repaint();
          Thread.sleep(60);
            }
    }
    
}
