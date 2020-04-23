<%-- 
    Document   : index
    Created on : 04/05/2016, 06:19:45 PM
    Author     : jbot
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Registro</title>
    </head>
    <body>
        <h1>Agregar Nuevos Alumnos</h1>
        <form action="Visualizar" method="Post">
            Codigo:<input type="text" name="codigo"><br/>
            Nombre:<input type="text" name="nombre"><br/>
            Apellido:<input type="text" name="apellido"><br/>
            Telefono:<input type="text" name="telefono"><br/>
            Direccion:<input type="text" name="direccion"><br/>
            <input type="submit" value="Grabar">
        </form>
    </body>
</html>
