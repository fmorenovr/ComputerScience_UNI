<?php
    session_start();
    include("../conex/conexion.php");
    conectar();

    //validar usuario e ingreso al sistema
    $user=$_POST["usrDs"];
    $password=$_POST["pwdDs"];

    $rol=0; //para despachador

    $match="select * from cliente where usuario='".$user."' and pass='".$password."' and rol='".$rol."';";

	$qry=mysql_query($match);
    $num_rows=mysql_num_rows($qry);

    if ($num_rows<=0){
        header ("Location:../?error=2");
    }

    else{
        //consulta para nombre de inventariador
        $qqacc= mysql_fetch_array($qry);                
        
        $idDespachador= $qqacc['idc'];
        $nombreDespachador= $qqacc['nombre'];           
 
        $_SESSION['logueado']='estaadentro';
        $_SESSION['idDespachador']=$idDespachador;
        $_SESSION['user']=$user;
        $_SESSION['nombreDespachador']=$nombreDespachador;              
        //$_SESSION['subbienvenida']='<p>Bienvenido al Panel de Administraci&oacute;n</p>';

        header("location:vistaDespachador.php");
    }   
?>