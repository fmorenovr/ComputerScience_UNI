package automataCadenas;

import java.util.*;

public class Problema1 {
    static Scanner cadena = new Scanner(System.in);
    static Automata auto = new Automata();
    public static void main(String[] args) {
      String str;
      System.out.println("\nIngrese Cadena a procesar por Automata ...:\n");
      str = cadena.nextLine();
      System.out.println("\nProcesando ...\n");
      auto.start(str);
    }
}
