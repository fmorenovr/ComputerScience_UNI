<%-- 
    Document   : menu
    Created on : May 24, 2016, 7:51:23 PM
    Author     : Felipe Moreno
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"
        import="java.sql.Connection"
        import="java.sql.DriverManager"
        import="java.sql.ResultSet"
        import="java.sql.Statement"
        import="java.sql.SQLException"
        import="AccesoDatos.AccesoCalidad"
        import="java.io.PrintWriter"
        %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Menu</title>
        <%-- CREAR ESTILOS     --%>
        <style type="text/css">
            * {
                padding:0px;
                margin:Opx;
            }
            <%-- CREAR ETIQUETAS  --%>
            #header{
                margin:auto;
                width:1200px;
                font-family: Arial, Helvetica,sans-serif;
            }
            #body,#header {
                padding-left:450px;
                float:left;
            }
            <%-- REGLAS, QUE NO TENGA ESTILO  --%>
            ul, ol{
                list-style: none;
            }
            <%-- CREAR ESTILOS PARA EL MENU  --%>
            .nav li a {
                background-color: #000;
                color: #fff;
                text-decoration: none;
                padding: 10px 15px;
                display: block;
            }
            <%-- DAR FORMA AL MENU  --%>
            .nav > li{
                float: left;
            }
            <%-- MAS ESTILO  --%>
            .nav li a:hover{
                background-color: #434343;
            }
            <%-- PARA DESAPARECER LOS SUB MENUS  --%>
            .nav li ul {
                display:none;
                position: absolute;
                min-width: 140px;
            }
            <%-- REGLAS, PARA Q APARESCA CADA Q EL MOUSE PASE  --%>
            .nav li:hover > ul {
                display: block;
            }
            <%-- PARA CAMBIAR POSICION DEL SUB MENU  --%>
            .nav li ul li {
                position: relative;
            }
            <%-- PROPIEDAD CAMBIO DE POSICION DEL SUB MENU  --%>
            .nav li ul li ul {
                right:-140px;
                top:0px;
            }
        </style>
    </head>
    <form action="SrvCalidad" method="post">
    <body>
        <h1 align="center">SISTEMA DE MENU</h1>
        <div id="header" align="center">
            <ul class="nav">
                <li><a href="">Gestion Base Datos</a>
                    <ul>
                        <li><a href="anadir.jsp">Anadir</a></li>
                        <li><a href="">Borrar</a>
<!--                            <ul>
                                <li><a href="">ejemplo 1</a></li>
                                <li><a href="">ejemplo 2</a></li>
                                <li><a href="">ejemplo 3</a></li>
                                <li><a href="">ejemplo 4</a>
                                    <ul>
                                        <li><a href="">uno</a></li>
                                        <li><a href="">dos</a></li>
                                        <li><a href="">tres</a></li>
                                        <li><a href="">cuatro</a></li>
                                    </ul>
                                </li>
                            </ul>-->
                        </li>
                    </ul>
                </li>
<!--                <li><a href="">Reporte</a>
                    <ul>
                        <li><a href="">Submenu 1</a></li>
                        <li><a href="">Submenu 2</a></li>
                        <li><a href="">Submenu 3</a></li>
                        <li><a href="">Submenu 4</a></li>
                    </ul> -->
                <li><a href="index.jsp">Salir</a></li>
            </ul>

        </div>
        <div id="body" align="center">
        <%
            ResultSet res;
            AccesoCalidad calidad = new AccesoCalidad();
            String Codigo ="";
            String Nombre ="";
            String apell="";
            String direc="";
            String telf="";
        %>
            <table align=center width=299 border=1 class=datos_form>
            <tr class=titulo_table><td colspan=5 align=\"center\">Listado de Alumnos</td></tr>
            <tr><td>Codigo</td><td>Alumnos</td><td>Apellido</td><td>Direccion</td><td>Telefono</td></tr>
            <%
            res=calidad.Listado();
            while(res.next()){
                Codigo = res.getString("codigo");
                Nombre = res.getString("nombre");
                apell = res.getString("apellido");
                telf = res.getString("telefono");
                direc = res.getString("direccion");
                %>
                <tr><td><%=Codigo%></td><td><%=Nombre%></td><td><%=apell%></td><td><%=telf%></td><td><%=direc%></td></tr>
            <%}
            %>
            </table>
<!--            <p align=\"center\"> Listado de informacion de los alumnos ... volver a la pagina principal <a href="index.jsp">regresar</a></p> -->
        </div>
    </body>
</html>
