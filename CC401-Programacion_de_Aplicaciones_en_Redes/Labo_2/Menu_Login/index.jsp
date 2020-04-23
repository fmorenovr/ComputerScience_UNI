<%-- 
    Document   : login
    Created on : 17/05/2016, 02:08:18 PM
    Author     : user
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <h1 align="center">Login</h1>
         <center>
            <form action="validad.jsp" method="Post">
                <table border="1">
                    
                    <tbody>
                        <tr>
                            <td>Nombre</td>
                            <td><input type="text" name="f_nombre" value="" /></td>
                        </tr>
                        <tr>
                            <td>Password</td>
                            <td><input type="password" name="f_clave" value="" /></td>
                        </tr>
                        <tr>
                            <td><input type="submit" value="Enviar" /></td>
                            
                        </tr>
                    </tbody>
                </table>
            </form>
        </center>
    </body>
</html>
