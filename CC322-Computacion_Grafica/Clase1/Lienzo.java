/*
 * Javier Abellán. 13 de febrero de 2004
 *
 * Lienzo.java
 *
 */

import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.geom.Line2D;

/**
 * Clase que hereda de Canvas y sirve para dibujar una linea.
 */
public class Lienzo extends Canvas
{
    /**
     * Constructor. Hace que el tamaño del canvas sea 100x100 pixels.
     */
    public Lienzo()
    {
        this.setSize (100, 100);
    }
    
    /**
     * Dibuja la última línea que se le haya pasado.
     */
    public void paint(Graphics g)
    {
        if (linea == null) return;
        g.drawLine ((int)linea.getP1().getX(), (int)linea.getP1().getY(),
            (int)linea.getP2().getX(), (int)linea.getP2().getY());
    }
    
    /**
     * Guarda la línea que se le pasa para dibujarla cuando se le indique
     * llamando a paint()
     */
    public void tomaLinea (Line2D linea)
    {
        this.linea = linea;
    }
    
    /** La linea a dibujar */
    private Line2D linea = null;
}
