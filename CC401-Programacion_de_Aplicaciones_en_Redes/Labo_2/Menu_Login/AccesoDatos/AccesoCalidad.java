/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package AccesoDatos;

import AccesoDatos.Conexion;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.sql.ResultSet;

/**
 *
 * @author jbot
 */
public class AccesoCalidad extends Conexion{
    private ResultSet resultado;
    
    public AccesoCalidad(){
        Conectar();
    }

    public ResultSet Listado() throws Exception {
        try{
    //        con = new Conexion();
    //        Connection trab = con.Conectar();
    //        Statement set1 = trab.createStatement();
            getStmt();
            String query = "select * from Usuarios";
            resultado = atmt.executeQuery(query);
            return resultado;
        } catch (Exception ex){
            System.err.println("SQLException: "+ ex.getMessage());
            return null;
        }
    }
    
    public void eliminarCodigo(String Cod) throws Exception {
        try{
    //        con = new Conexion();
    //        Connection trab = con.Conectar();
    //        Statement set1 = trab.createStatement();
            getStmt();
            String query = "delete from usuarios where codigo like '"+Cod+"%'";
            resultado = atmt.executeQuery(query);
        } catch (Exception ex){
            System.err.println("SQLException: "+ ex.getMessage());
        }
    }
    
    public ResultSet buscarExistencia(String Cod) throws Exception {
        try{
            //con = new Conexion();
            //Connection trab = con.Conectar();
            //Statement set1 = trab.createStatement();
            getStmt();
            String query = "select * from usuarios where codigo like '"+Cod+"%'";
            resultado = atmt.executeQuery(query);
            return resultado;
        } catch (Exception ex){
            System.err.println("SQLException: "+ ex.getMessage());
            return null;
        }
    }
    
    public ResultSet buscarPorNombre(String Nom) throws Exception{
        try{
            //con = new Conexion();
            //Connection trab = con.Conectar();
            //Statement set1 = trab.createStatement();
            getStmt();
            String query = "select * from usuarios where nombre like '"+Nom+"%'";
            resultado = atmt.executeQuery(query);
            return resultado;
        } catch (Exception ex){
            System.err.println("SQLException: "+ ex.getMessage());
            return null;
        }
    }
}
