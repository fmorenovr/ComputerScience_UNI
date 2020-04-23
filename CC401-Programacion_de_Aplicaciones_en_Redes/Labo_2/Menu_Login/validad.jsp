<%-- 
    Document   : validad
    Created on : 17/05/2016, 02:08:36 PM
    Author     : user
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"
        import="java.sql.Connection"
        import="java.sql.DriverManager"
        import="java.sql.ResultSet"
        import="java.sql.Statement"
        import="java.sql.SQLException"
        %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
        <%
            String s_nombre;
            String s_clave;
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
    }
        %>
    </head>
    <body>
        <%
            s_nombre=request.getParameter("f_nombre");
            s_clave=request.getParameter("f_clave");
            if(s_nombre.equals("admin") && s_clave.equals("123456")){
                response.sendRedirect("menu.jsp");
            
            }
            else
            {
                out.print("Usuario no existe o campos incorrectos");
                response.sendRedirect("index.jsp");
            }
        %>
    </body>
</html>