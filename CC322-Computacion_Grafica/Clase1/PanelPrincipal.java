
/*
 * Javier Abellán. 13 de febrero de 2004
 *
 * Principal.java
 *
 */

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.awt.geom.Line2D.Double;
import javax.swing.JButton;
import javax.swing.JPanel;


/**
 * Panel con un Lienzo y un botón.
 * Pulsando el botón se cambia la línea a dibujar en el lienzo.
 */
public class PanelPrincipal extends JPanel
 {
     /**
      * Constructor por defecto. Pone el lienzo y el botón en el panel y
      * hace que se dibuje la primera línea.
      */
     public PanelPrincipal()
     {
         ponComponentes();
         pintaLinea();
     }
     
     /**
      * Pone el lienzo y el botón en el panel.
      */
     private void ponComponentes()
     {
         this.add (lienzo);
         this.add (boton);

         /* Accion que se ejecuta al pulsar el botón, se hace que se pinte la
          * línea */
         boton.addActionListener (new ActionListener () {
             public void actionPerformed (ActionEvent e)
             {
                 pintaLinea();
             }
         });
     }
     
     /**
      * Dibuja una línea en el lienzo. Cada vez que se llama a este método,
      * la línea se cambia para que se dibuje en distinto sitio dentro del
      * lienzo.
      */
     private void pintaLinea(int x,int y,int x1,int y1,)
     {
         /* Se hace que la x cambie de 0 a 100 o de 100 a 0 en cada llamada. */
         if (x < 50.0) x = 100.0;
         else x = 0.0;
         
         /* Se crea una linea diagonal que puede ser / o \ */
         Line2D linea = new Double (x, 0.0, 100.0-x, 100.0);
         
         /* Se pasa la línea al lienzo y se hace que se redibuje */
         lienzo.tomaLinea (linea);
         lienzo.repaint();
     }
     

     /** Coordenada x del punto de origen de la línea que se dibuja en el
      * lienzo. Valdrá 0.0 o 100.0 */
     private double x = 0.0;
     
     /** El lienzo de dibujo */
     private Lienzo lienzo = new Lienzo();
     
     /** El botón que hace cambiar la línea dibujada en el lienzo */
     private JButton boton = new JButton ("Cambia dibujo");
}
