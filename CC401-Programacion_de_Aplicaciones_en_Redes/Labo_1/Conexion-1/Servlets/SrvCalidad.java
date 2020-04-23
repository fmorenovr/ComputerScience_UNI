/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlets;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import AccesoDatos.AccesoCalidad;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.sql.ResultSet;
/**
 *
 * @author jbot
 */
@WebServlet(name = "SrvCalidad", urlPatterns = {"/SrvCalidad"})
public class SrvCalidad extends HttpServlet{
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    }
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        processRequest(request,response);
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try{
            ResultSet res;
            AccesoCalidad calidad = new AccesoCalidad();
            String Codigo ="";
            String Nombre ="";
            String apell="";
            String direc="";
            String telf="";
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Listado de Alumnos</title>");
            out.println("<link href=Estilo.css rel=stylesheet type=text/css>");
            out.println("</head>");
            out.println("<body>");
            out.println("<table align=center width=299 border=1 class=datos_form>");
            out.println("<tr class=titulo_table><td colspan=5 align=\"center\">Listado de Alumnos</td></tr>");
            out.println("<tr><td>Codigo</td><td>Alumnos</td><td>Apellido</td><td>Direccion</td><td>Telefono</td></tr>");
            res=calidad.Listado();
            if((request.getParameter("Codigo")=="")&&(request.getParameter("Nombre")!=""))
                res = calidad.buscarPorNombre(request.getParameter("Nombre"));
            else if((request.getParameter("Codigo")!="")&&(request.getParameter("Nombre")==""))
                res = calidad.buscarExistencia(request.getParameter("Codigo"));
            else if((request.getParameter("Codigo")=="")&&(request.getParameter("Nombre")==""))
                res = calidad.Listado();
            
            while(res.next()){
                Codigo = res.getString("codigo");
                Nombre = res.getString("nombre");
                apell = res.getString("apellido");
                telf = res.getString("telefono");
                direc = res.getString("direccion");
                out.println("<tr><td>"+Codigo+"</td><td>"+Nombre+"</td><td>"+apell+"</td><td>"+direc+"</td><td>"+telf+"</td></tr>");
            }
            out.println("</table>");
            out.println("<p align=\"center\"> Listado de informacion de los alumnos ... volver a la pagina principal "+"<a href=\"index.jsp\"><input type=\"submit\" value=\"regresar\"></a></p>");
            out.println("</body>");
            out.println("</html>");
            out.close();
        }catch(Exception e){
            Logger.getLogger(SrvCalidad.class.getName()).log(Level.SEVERE,null,e);
        }
    }
    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
