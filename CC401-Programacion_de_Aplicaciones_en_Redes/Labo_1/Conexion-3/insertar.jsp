<%-- 
    Document   : insertar
    Created on : 04/05/2016, 03:20:48 PM
    Author     : jbot
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@include file="Conexion.jsp"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <h1>Insertar</h1>
        <%
            String nombre1 = request.getParameter("Nombre");
            String apellido1 = request.getParameter("Apellido");
            String telefono1 = request.getParameter("Telefono");
            if(nombre1!=null&&apellido1!=null&&telefono1!=null){
                String cc = "insert into Usuarios(nombre,apellido,telefono) values('"
+nombre1+"','"+apellido1+"','"+telefono1+"')";
                sql.executeUpdate(cc);
out.print("Usuario Registrado "+"<a href='index.jsp'>REGRESAR</a>");
            }
             else{
            
        %>
        <form name="frmuser" method="post" action="insertar.jsp">
            Nombre:<input type="text" name="Nombre"><br/>
            Apellido:<input type="text" name="Apellido"><br/>
            Telefono:<input type="text" name="Telefono"><br/>
            <input type="submit" value="Guardar"/>
        </form>
        <%}%>
    </body>
</html>
