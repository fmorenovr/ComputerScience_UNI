<%-- 
    Document   : nn
    Created on : 04/05/2016, 07:38:41 PM
    Author     : jbot
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Listado de Alumnos</title>
    </head>
    <form action="SrvCalidad" method="post">
    <body>
            <table algin="center" width="289" border="1" class="datos_form">
                <tr>
                    <td>Codigo Alumno</td>
                    <td>Nombre Alumno</td>
                </tr>
                <tr>
                    <td><input type="text" name="Codigo" class="texto"></td>
                    <td><input type="text" name="Nombre" class="texto"></td>
                    <td><input type="submit" name="Consultar" class="texto"></td>
                </tr>
            </table>
    </body>
</html>
