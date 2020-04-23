/*
 * Javier Abellán, 26 de Febrero de 2004
 *
 * AppletPrincipal
 */

/**
 * Applet de ejemplo de pintado de gráficos.
 */
public class AppletPrincipal extends java.applet.Applet 
{
    /**
     * Método init() del applet al que llamará el navegador cuando se cargue
     * el applet.
     */
    public void init() 
    {
        this.add (panel);
    }
    
    /** Panel principal con un lienzo de dibujo y un botón para cambiar el
     * dibujo en el lienzo */
    private PanelPrincipal panel = new PanelPrincipal();
}
