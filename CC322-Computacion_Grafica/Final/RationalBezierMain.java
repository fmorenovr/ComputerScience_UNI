import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import javax.swing.*;
import java.util.Scanner;
import java.io.BufferedReader; 
import java.io.IOException; 
import java.io.InputStreamReader; 

public class RationalBezierMain {

  private JFrame frame;
  private JPanel panel;
  private JButton botonDibujarBezier;
  private JButton botonDibujarBezierRational;
  private JButton botonBorrar;
  private JToolBar barra;
  private JSpinner spinner;
  private SpinnerModel model;
  private ArrayList<Point> puntos;
  public Scanner leer = new Scanner(System.in);
  public BufferedReader bf = new BufferedReader(new InputStreamReader(System.in)); 

  public RationalBezierMain() {
    puntos = new ArrayList<>();
    inicializarComponentes();
  }
  
  public void inicializarComponentes() {
    this.frame = new JFrame("Curvas de Bezier Racionales y Cruvas de Bezier");
    frame.getContentPane().setLayout(new BorderLayout());    
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
    this.panel = new JPanel();
    panel.setBackground(Color.WHITE);
    panel.addMouseListener( new MouseAdapter() {
                @Override public void mousePressed(MouseEvent e) {
                    panel.getGraphics().fillOval(e.getX() - 5, e.getY() - 5, 10, 10);
                    puntos.add(new Point(e.getX(), e.getY()));
                }});

    model = new SpinnerNumberModel(200, 1, 1000, 10);
    spinner = new JSpinner(model);
    botonBorrar = new JButton("Borrar");
    botonBorrar.addActionListener( new ActionListener() {
                @Override public void actionPerformed(ActionEvent e) {
                    panel.repaint();
                    puntos.clear();
                }});
    
    this.botonDibujarBezier = new JButton("Dibujar Bezier");
    this.botonDibujarBezier.addActionListener( new ActionListener() {
                @Override public void actionPerformed(ActionEvent e) {
                    dibujarBezier(panel.getGraphics(), puntos, (int) model.getValue());
                    puntos.clear();
                }});
    
    this.botonDibujarBezierRational = new JButton("Dibujar Bezier Racional");
    this.botonDibujarBezierRational.addActionListener( new ActionListener() {
                @Override public void actionPerformed(ActionEvent e) {
                    //pedirPesos();
                    dibujarBezierRational(panel.getGraphics(), puntos, (int) model.getValue());
                    puntos.clear();
                }});
    
    this.barra = new JToolBar();
    
    barra.add(botonBorrar);
    barra.add(botonDibujarBezier);
    barra.add(botonDibujarBezierRational);
    //barra.add(spinner);
    
    frame.add(barra, BorderLayout.NORTH);
    frame.add(panel, BorderLayout.CENTER);        
    frame.setSize(800, 600);
    frame.setLocationRelativeTo(null);
    frame.setVisible(true);
  }
  
  public static void main(String[] args) {
      new RationalBezierMain();
  }

  public ArrayList<Double> pedirPesos(int tamano){
    ArrayList<Double> pesos = new ArrayList<>();
    System.out.println("\nIngrese los pesos a graficar:\n");
    for(int i=0;i<tamano;i++){
      try {
      double d3 = Double.parseDouble(bf.readLine());
      pesos.add(d3);
      } catch (NumberFormatException e) { 
      e.printStackTrace(); 
      } catch (IOException e) { 
      e.printStackTrace(); 
      } 
      //Double d3 = new Double(weidh);
      
    }
    return pesos;
  }

  public void dibujarBezierRational(Graphics g, ArrayList<Point> puntos, int numeroPuntos) {
    //Variables para almacenar el punto calculado
    double puntoX = 0, puntoY = 0;      
    //En esta lista se guardan los puntos anteriores que nos sirven para poder 
    //dibujar las líneas que van de punto a punto
    ArrayList<int[]> anteriores = new ArrayList<>();
    double avance = 1 / ((double) numeroPuntos);
    int tamLista = puntos.size();
    ArrayList<Double> pesosBezier = new ArrayList<>();
    pesosBezier = pedirPesos(tamLista);
    //Este ciclo realiza el número de iteraciones que el usuario desee en base 
    //al número de puntos que se desean
    g.setColor(Color.BLUE);
    for (double u = 0; u <= 1; u += avance) {
      //Este ciclo itera sobre los puntos a dibujar y realiza el cálculo del siguiente punto de la curva
      double SumB=0;
      for (int k = 0; k < tamLista; k++) {
        double b = BersteinPoly(u, tamLista - 1, k);
        double w=pesosBezier.get(k);
        SumB=SumB+w*b;
      }
      
      for (int k = 0; k < tamLista; k++) {
        double b = BersteinPoly(u, tamLista - 1, k);
        double w=pesosBezier.get(k);
        double r = w*b/SumB;
        puntoX += puntos.get(k).getX() * r;
        puntoY += puntos.get(k).getY() * r;
      }
      Double d1 = new Double(puntoX);
      Double d2 = new Double(puntoY);
      //Se almacenan y se dibuja el punto calculado anteriormente
      anteriores.add(new int[] {d1.intValue(), d2.intValue()});           
      g.drawLine(d1.intValue(), d2.intValue(), d1.intValue(),d2.intValue());
      
      //Se dibuja la línea que va del punto anterior al recien calculado
      //de esa manera no tenemos que calcular punto por punto de toda la curva
      if (anteriores.size() > 1) {
        g.drawLine(anteriores.get(anteriores.size() - 2)[0], anteriores.get(anteriores.size() - 2)[1],d1.intValue(), d2.intValue());
        //Removemos el primer elemento que ya no se utiliza
        anteriores.remove(0);
      }
      //Borramos los valores anteriores para la siguiente iteración
      puntoX = puntoY = 0;
    }
    
    //Se dibuja el último trayecto de la curva
    g.drawLine((int) anteriores.get(anteriores.size() - 1)[0], (int) anteriores.get(anteriores.size() - 1)[1], (int) puntos.get(tamLista - 1).getX(), (int) puntos.get(tamLista - 1).getY());
  }
  
  public void dibujarBezier(Graphics g, ArrayList<Point> puntos, int numeroPuntos) {
    //Variables para almacenar el punto calculado
    double puntoX = 0, puntoY = 0;      
    //En esta lista se guardan los puntos anteriores que nos sirven para poder 
    //dibujar las líneas que van de punto a punto
    ArrayList<int[]> anteriores = new ArrayList<>();
    double avance = 1 / ((double) numeroPuntos);
    int tamLista = puntos.size();
    
    //Este ciclo realiza el número de iteraciones que el usuario desee en base 
    //al número de puntos que se desean
    g.setColor(Color.RED);
    for (double u = 0; u <= 1; u += avance) {
      //Este ciclo itera sobre los puntos a dibujar y realiza el cálculo del siguiente punto de la curva
      for (int k = 0; k < tamLista; k++) {
        double b = BersteinPoly(u, tamLista - 1, k);
        puntoX += puntos.get(k).getX() * b;
        puntoY += puntos.get(k).getY() * b;
      }
      Double d1 = new Double(puntoX);
      Double d2 = new Double(puntoY);
      //Se almacenan y se dibuja el punto calculado anteriormente
      anteriores.add(new int[] {d1.intValue(), d2.intValue()});           
      g.drawLine(d1.intValue(), d2.intValue(), d1.intValue(),d2.intValue());
      
      //Se dibuja la línea que va del punto anterior al recien calculado
      //de esa manera no tenemos que calcular punto por punto de toda la curva
      if (anteriores.size() > 1) {
        g.drawLine(anteriores.get(anteriores.size() - 2)[0], anteriores.get(anteriores.size() - 2)[1],d1.intValue(), d2.intValue());
        //Removemos el primer elemento que ya no se utiliza
        anteriores.remove(0);
      }
      //Borramos los valores anteriores para la siguiente iteración
      puntoX = puntoY = 0;
    }
    
    //Se dibuja el último trayecto de la curva
    g.drawLine((int) anteriores.get(anteriores.size() - 1)[0], (int) anteriores.get(anteriores.size() - 1)[1], (int) puntos.get(tamLista - 1).getX(), (int) puntos.get(tamLista - 1).getY());
  }
  
  private double BersteinPoly(double u, int n, int k) {
    return (combinatoria(n,k) * Math.pow(u, k) * Math.pow(1 - u, n - k));
  }

  private double combinatoria(int n,int k){
    return  (factorial(n) / (factorial(k) * factorial(n - k))); 
  }
  private double factorial(int n) {
      double facto = 1;
      if (n == 0 || n == 1) 
          return facto;
      else {
          return n*factorial(n-1); 
      }
  }
}
