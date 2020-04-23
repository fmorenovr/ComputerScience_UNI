package ejercicio2;
import java.awt.geom.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.BasicStroke;
import java.awt.Shape;
import java.awt.Composite;
import java.awt.AlphaComposite;


public class CardioidGraph
    extends GraphPanel
    implements ActionListener
{
    private Timer timer = null;
    private int tIval = 100;
    private float tick;
    private float diam;
    private int tCount = 0;
    private GeneralPath curve;
    private Shape hub;
    private GeneralPath wheel;
    
    public CardioidGraph( Rectangle2D.Float uR )
    {
        super( uR );

        diam = uRect.width / 4;
        hub = new Ellipse2D.Float( 0F, -diam / 2, diam, diam );

        tick = uRect.width / 40;
        wheel = new GeneralPath();
        Shape s = new Ellipse2D.Double( diam, -diam / 2, diam, diam );
        wheel.append( s, false );
        wheel.moveTo( 2*diam, 0F );
        wheel.lineTo( 2*diam + tick, 0F );
    }
	
    public void start()
    {
        if ( timer != null )
        {
            timer.stop();
        }
        timer = new Timer( tIval, this );

        curve = new GeneralPath();
        curve.moveTo( 2F, 0F );

        tCount = 0;
        repaint();
        timer.start();
    }
	
    public void actionPerformed( ActionEvent e )
    {
        tCount++;
        double theta = tCount * Math.PI / 180;
        double sint = Math.sin( theta );
        double cost = Math.cos( theta );
        double cx = cost + cost*cost;
        double cy = sint + sint*cost;
        curve.lineTo( (float)cx, (float) cy );

        if ( tCount >= 360 )
        {
            timer.stop();
            timer = null;
        }
        repaint();
    }
	
    public void paintComponent( Graphics g )
    {
        super.paintComponent( g );

        Graphics2D g2 = (Graphics2D) g;
        drawHub( g2 );
        drawCurve( g2 );
        drawWheel( g2 );
    }

    private void drawHub( Graphics2D g2 )
    {
        if ( hub == null )
            return;

        Composite c = g2.getComposite();
        Composite hc = AlphaComposite.getInstance( AlphaComposite.SRC_OVER,
                                                   .5F
                                                  );
        g2.setComposite( hc );
        g2.setPaint( Color.blue );
        g2.setStroke( new BasicStroke( 2 ) );
        g2.draw( baseXf.createTransformedShape( hub ) );
        g2.setComposite( c );
    }

    private void drawCurve( Graphics2D g2 )
    {
        if ( curve == null )
            return;
        Composite c = g2.getComposite();
        Composite hc = AlphaComposite.getInstance( AlphaComposite.SRC_OVER,
                                                   .5F
                                                  );
        g2.setComposite( hc );
        g2.setPaint( Color.red );
        g2.setStroke( new BasicStroke( 2 ) );
        g2.draw( baseXf.createTransformedShape( curve ) );
        g2.setComposite( c );
    }
    
    private void drawWheel( Graphics2D g2 )
    {
        Composite c = g2.getComposite();
        Composite hc = AlphaComposite.getInstance( AlphaComposite.SRC_OVER,
                                                   .5F
                                                  );
        g2.setComposite( hc );
        g2.setPaint( Color.orange );
        g2.setStroke( new BasicStroke( 2 ) );

        double theta = tCount * Math.PI / 180;
        AffineTransform wheelXf2 = new AffineTransform( baseXf );
        wheelXf2.rotate( theta, diam/2, 0.0 );
        wheelXf2.rotate( theta, 3*diam/2, 0.0 );
        g2.draw( wheelXf2.createTransformedShape( wheel ) );
        g2.setComposite( c );
    }
}