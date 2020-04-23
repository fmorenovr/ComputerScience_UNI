package ejercicio2;
import javax.swing.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.BorderLayout;

public class Cardioid
    extends JFrame
{
    private CardioidGraph graph;
    private Rectangle2D.Float uSpace;
    
    public static void main( String [] args )
    {
        Rectangle2D.Float uS =
                new Rectangle2D.Float( -1.5F, 1.5F, 4.0F, 3.0F );
        Cardioid card  = new Cardioid( uS );
        card.setSize( 640, 480 );
        card.setVisible( true );
    }
    
    public Cardioid( Rectangle2D.Float uS )
    {
        super( "Cardioid" );
        setDefaultCloseOperation( EXIT_ON_CLOSE );

        uSpace = uS;
        graph = new CardioidGraph( uSpace );
        getContentPane().add( graph, BorderLayout.CENTER );

        JPanel cntlPanel = new JPanel();
        JButton startBtn = new JButton( "start" );
        startBtn.addActionListener(
            new ActionListener()
            {
                public void actionPerformed( ActionEvent e )
                {
                    graph.start();
                }
            }
        );
        cntlPanel.add( startBtn );
        getContentPane().add( cntlPanel, BorderLayout.NORTH );
    }
}