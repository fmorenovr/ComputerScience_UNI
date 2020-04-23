<?php
session_start(); //to ensure you are using same session
include("../conex/conexion.php");
if($_SESSION['logueado'] == 'estaadentro'){}
else{desconectar();header('Location:../index.php');}
session_destroy(); //destroy the session
header("location:../index.php"); //to redirect back to "index.php" after logging out
exit();
?>