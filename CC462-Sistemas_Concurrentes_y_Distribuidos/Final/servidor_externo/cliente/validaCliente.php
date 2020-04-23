<?php
    session_start();
    include("../conex/conexion.php");
    conectar();

    //validar usuario e ingreso al sistema
    $user=$_POST["usrCl"];
    $password=$_POST["pwdCl"];

    $rol=1; //para clientes

    $match="select * from cliente where usuario='".$user."' and pass='".$password."' and rol='".$rol."';";
    
	$qry=mysql_query($match);
    $num_rows=mysql_num_rows($qry);

    if ($num_rows<=0){
        header ("Location:../?error=1");
    }

    else{
        //consulta para nombre de inventariador
        $qqacc= mysql_fetch_array($qry);                
        
        $idCliente= $qqacc['idc'];
        $nombreCliente= $qqacc['nombre'];           
 
        $_SESSION['logueado']='estaadentro';
        $_SESSION['idCliente']=$idCliente;
        $_SESSION['user']=$user;
        $_SESSION['nombreCliente']=$nombreCliente;              
        //$_SESSION['subbienvenida']='<p>Bienvenido al Panel de Administraci&oacute;n</p>';

        header("location:vistaCliente.php");
    }   
?>