import java.io.*;
import java.net.Socket;
import java.util.*;
import java.util.logging.*;
class Persona extends Thread{
    protected Socket sk;
    protected DataOutputStream dos;
    protected DataInputStream dis;
    private int id;
    private int socket;
    public Persona(int id, int s) {
        this.id = id;
        socket=s;
    }
    @Override
    public void run() {
        try {
            while(true){
                sk = new Socket("localhost", socket);
                dos = new DataOutputStream(sk.getOutputStream());
                dis = new DataInputStream(sk.getInputStream());
                System.out.println(id + " envía saludo");
                dos.writeUTF("hola");
                String respuesta="";
                respuesta = dis.readUTF();
                dormir();
                System.out.println(id + " Servidor devuelve saludo: " + respuesta);
                dis.close();
                dos.close();
                sk.close();
                dormir();
            }
            
        } catch (IOException ex) {
            Logger.getLogger(Persona.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void dormir(){
        try
        {
            Thread.sleep(1000);
        }catch(InterruptedException e){}
    }
}
public class Cliente {
    public static void main(String[] args) {
        ArrayList<Persona> clients = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            clients.add(new Persona(i,10578+i));
        }
        for (Persona p : clients) {
            p.start();
        }
    }
}
