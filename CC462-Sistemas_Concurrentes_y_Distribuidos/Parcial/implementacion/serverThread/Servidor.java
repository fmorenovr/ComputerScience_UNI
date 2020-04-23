import java.io.*;
import java.net.*;
import java.util.*;
import java.util.logging.*;
public class Servidor extends Thread{
    private ServerSocket ss;
    private boolean estado=false;
    public Servidor(int s){
        System.out.print("Inicializando servidor... ");
        try{
            ss = new ServerSocket(s);
            estado=true;
            System.out.println("socket:"+s+"\t[OK]");
            
        } catch (IOException ex) {
            Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void run(){
        int idSession = 0;
        while (estado) {
            try {                
                Socket socket;
                socket = ss.accept();
                System.out.println("Nueva conexión entrante: "+socket);
                ((ServidorHilo) new ServidorHilo(socket, idSession)).start();
                idSession++;
            } catch (IOException ex) {
            Logger.getLogger(Persona.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    
    }
    //public void setSocket(boolean e){estado=e;}
    public ServerSocket getSocket(){return ss;}
    
    public void setEstado(boolean e){estado=e;}
    public boolean getEstado(){return estado;}
    
    
}
