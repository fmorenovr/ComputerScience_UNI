import java.io.*;
import java.net.Socket;
import java.util.*;
import java.util.logging.*;

public class Router{
    
    public static void main(String[] args){
        ArrayList<Servidor> servers = new ArrayList<>();
        for(int i=0; i<5; i++)
            servers.add(new Servidor(10578+i));
        for(Servidor server:servers)
            server.start();
            
        new Thread(new Runnable() {
             public void run() {
                  while(true){
                    for(Servidor server:servers) {
                        System.out.println("estado del "+server.getSocket()+" es:"+server.getEstado());
                    }
                    dormir();
                  }
             }
             public void dormir(){
                try
                {
                    Thread.sleep(5000);
                }catch(InterruptedException e){}
            }
        }).start();
    }
    
    
    
}
