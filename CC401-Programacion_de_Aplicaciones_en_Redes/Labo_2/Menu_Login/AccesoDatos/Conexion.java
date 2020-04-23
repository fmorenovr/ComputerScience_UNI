/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package AccesoDatos;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.*;
/**
 *
 * @author jbot
 */
public class Conexion {
    protected Connection con;
    protected Statement atmt;
    private String serverName = "localhost";
    private String portNumber="3306";
    private String databaseName="MeowDB";
    private String url = "jdbc:mysql://localhost:3306/"+databaseName;
    private String userName = "root";
    private String password ="";
    private String errString;
    
    public Conexion(){
    }
    private String getConnectionUrl(){
        return this.url;
    }
    public Connection Conectar(){
// throws SQLException,IOException {
        con = null;
        try{
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            con = DriverManager.getConnection(getConnectionUrl(),userName,password);
            atmt = con.createStatement();
            System.out.println("Conectado");
        } catch(Exception e){
            errString = "Error Mientras se conectaba a la Base de Datos";
            System.out.println(errString+":" +e);
            return null;
        }
        return con;
    }
    // Mostrar las propiedades del controlador y lo detalles de la basde de datos
    public void Desconectar(){
        try{
            atmt.close();
            con.close();
        }catch(Exception e){
            errString = "Error Mientras se Cerraba la Conexion a la Base de Datos";
        }
    }
    
    public Statement getStmt(){
        return this.atmt;
    }
}
