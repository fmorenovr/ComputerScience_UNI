/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ejercicio2;
import javax.swing.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.BasicStroke;
import java.awt.Shape;
import java.awt.geom.*;

public class GraphPanel
    extends JPanel
{
    protected Rectangle2D.Float uRect;
    protected AffineTransform baseXf = null;
    protected Dimension curDim = null;
    protected double scale;
    
    private double hScale;
    private double vScale;
    private float uIval;
    private GeneralPath axes = null;
    private GeneralPath grid = null;
    
    static public final int MIN_GRID_SPACING = 10;
    static public final float [] GRID_IVALS =
                            { 0.01F, 0.1F, 0.2F, 0.25F, 0.5F,
                              1F, 2F, 5F, 10F };
    
    public GraphPanel( Rectangle2D.Float uR )
    {
        uRect = (Rectangle2D.Float) uR.clone();
        setBackground( Color.gray );   
    }
	
    public void paintComponent( Graphics g )
    {
        super.paintComponent( g );
        Graphics2D g2 = (Graphics2D) g;
        if ( ! getSize().equals( curDim ) )
            doResize();
        drawAxes( g2 );
        drawGrid( g2 );
    }

    private void doResize()
    {
        curDim = getSize();
        hScale = curDim.width / uRect.width;
        vScale = curDim.height / uRect.height;
        scale = Math.min( hScale, vScale );
        baseXf = new AffineTransform();
        baseXf.scale( scale, -scale );
        baseXf.translate( -uRect.x, -uRect.y );

        axes = createAxes();
        grid = createGrid();
    }

    private void drawAxes( Graphics2D g2 )
    {
        g2.setPaint( Color.green );
        g2.setStroke( new BasicStroke(3 ) );
        g2.draw( baseXf.createTransformedShape( axes ) );
    }

    private void drawGrid( Graphics2D g2 )
    {
        g2.setPaint( Color.green );
        g2.setStroke( new BasicStroke( 1 ) );
        g2.draw( baseXf.createTransformedShape( grid ) );
    }
	
    private GeneralPath createAxes()
    {
        GeneralPath path = new GeneralPath();
        path.moveTo( uRect.x, 0F );
        path.lineTo( uRect.x + uRect.width, 0F );
        path.moveTo( 0F, uRect.y );
        path.lineTo( 0F, uRect.y - uRect.height );
        return path;
    }

    private GeneralPath createGrid()
    {
        GeneralPath path = new GeneralPath();
        uIval = 0F;

        for ( int i = 0; i < GRID_IVALS.length; i++ )
        {
            if ( GRID_IVALS[ i ]*scale >= MIN_GRID_SPACING )
            {
                uIval = GRID_IVALS[ i ];
                break;
            }    
        }
        if ( uIval == 0.0 )
        {
            System.err.println( "No es posible determinar la cuadrícula de la gráfica" );
            System.exit( 1 );
        }

        for ( float xt = uRect.x; xt <= uRect.x + uRect.width; xt += uIval )
        {
            path.moveTo( xt, uRect.y );
            path.lineTo( xt, uRect.y - uRect.height );
        }
        for ( float yt = uRect.y; yt >= uRect.y - uRect.height; yt -= uIval )
        {
            path.moveTo( uRect.x, yt );
            path.lineTo( uRect.x + uRect.width, yt );
        }

        return path;
    }
}