package automataCadenas;

public class Automata {
  private int[] S = {0,1,2}; // denota los estados
  private int[] F = new int[2]; // los estados de aceptacion
  private int s0=S[0]; // estado inicial
  private char[] I = {'0','1'}; // lenguaje
  
  Automata(){}
  public int funcionTransicion(int s,char a){
    if(s==S[0] && a=='0'){
      s=S[1];
      System.out.println("\nVa del estado S"+S[0]+" al estado S"+s+"\n");
      return s;
    }
    else if (s==S[0] && a=='1'){
      s=S[2];
      System.out.println("\nVa del estado S"+S[0]+" al estado S"+s+"\n");
      return s;
    }
    else if(s==S[1] && a=='0'){
      s=S[1];
      System.out.println("\nVa del estado S"+S[1]+" al estado S"+s+"\n");
      return s;
    }
    else if(s==S[1] && a=='1'){
      s=S[2];
      System.out.println("\nVa del estado S"+S[1]+" al estado S"+s+"\n");
      return s;
    }
    else if(s==S[2] && (a=='0' || a=='1')){
      s=S[2];
      System.out.println("\nVa del estado S"+S[2]+" al estado S"+s+"\n");
      return s;
    }
    System.out.println("\nError\n");
    return -1;
  }
  public void aceptadoRechazado(int s){
    if(s==S[0] || s==S[1]){
      System.out.println("\n\nLa cadena SI fue aceptada!!\n\n");
    }
    else if(s==S[2]){
      System.out.println("\n\nLa cadena NO fue aceptada!!\n\n");
    }
    else if(s==-1){
      System.out.println("\n\nLa cadena es erronea!!\n\n");
    }
  }
  public void start(String w){
    int len = w.length();
    int estado = s0;
    char[] cadena = w.toCharArray();
    char a;
    int transicion;
    for(int i=0;i<len;i++){
      a=cadena[i];
      System.out.println(a);
      transicion = funcionTransicion(estado,a);
      estado = transicion;
      if( i == len-1) aceptadoRechazado(estado);
    }
  }
}
