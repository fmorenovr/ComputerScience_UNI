<%-- 
    Document   : Conexion
    Created on : 04/05/2016, 04:25:37 PM
    Author     : jbot
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"
        import="java.sql.Connection"
        import="java.sql.DriverManager"
        import="java.sql.ResultSet"
        import="java.sql.Statement"
        import="java.sql.SQLException"
        %>
<% 
    Connection conex=null;
    String connectionURL = "jdbc:mysql://localhost:3306/MeowDB";
    String userName = "root";
    String password = "";
    Statement sql = null;
    try{
        Class.forName("com.mysql.jdbc.Driver").newInstance();
        conex = (Connection) DriverManager.getConnection(connectionURL,userName,password);
        sql = conex.createStatement();
        out.print("Conexion establecida");
    } catch(Exception e){
        out.print("Error en la conexion "+ e );
    } %>
<%--
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <h1>Hello World!</h1>
    </body>
</html>
--%>