import java.applet.*;
import java.awt.*;

public class HelloWorldApplets extends Canvas {

    public static void main(String[] args) {
        System.out.println("Hello, World");
        Canvas lienzo = new Canvas();
        Graphics g = lienzo.getGraphics();
        g.drawString ("Hello World", 25, 50);
    }

}

