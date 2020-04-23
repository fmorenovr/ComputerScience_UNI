<?php
	error_reporting(E_ALL ^ E_NOTICE);

	if($_GET["error"]==null){
		$error=0;
	}
	else{
		$error=$_GET["error"];
	} 

?>

<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
	
	<link rel="icon" href="../../favicon.ico">
	<title>Concurrentes</title>
	
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

	<link href="css/bootstrap.min.css" rel="stylesheet">

	<!-- Mi CSS -->
    <link href="css/cover.css" rel="stylesheet">
    <link href="css/mystyle.css" rel="stylesheet">


    <!--********************************************************************************************-->
	<script type="text/javascript">

		function mostrarCliente(){
			if(document.getElementById('secCliente').style.display == 'none'){
				document.getElementById('secCliente').style.display = 'block';
				document.getElementById('main').style.display = 'none';
			}
		}

		function mostrarDespachador(){
			if(document.getElementById('secDespachador').style.display == 'none'){
				document.getElementById('secDespachador').style.display = 'block';
				document.getElementById('main').style.display = 'none';
			}
		}

		function volver(){
			if(document.getElementById('secCliente').style.display == 'block' || document.getElementById('secDespachador').style.display == 'block'){
				document.getElementById('secCliente').style.display = 'none';
				document.getElementById('secDespachador').style.display = 'none';

				document.getElementById('main').style.display = 'block';
			}
		}
	</script>
	<!--********************************************************************************************-->

</head>
<body>

	<div class="site-wrapper">

      <div class="site-wrapper-inner">

        <div class="cover-container" style="background:">

          <div class="masthead clearfix">
            <div class="inner">
              <h3 class="masthead-brand">Concurrentes</h3>
              <nav class="nav nav-masthead">
                <a class="nav-link active" href="#">Home</a>
                <!--
                <a class="nav-link" href="#">Features</a>
                <a class="nav-link" href="#">Contact</a>
            	-->
              </nav>
            </div>
          </div>

          <div class="inner cover" id="main" style="display:block">
            <h1 class="cover-heading">Inicie Sesión</h1>
            <p class="lead">Ingrese con su cuenta.</p>
            <p class="lead">
              <a href="#" class="btn btn-lg btn-secondary" onclick="mostrarCliente()">Cliente</a>
              <span>&nbsp;</span>
              <a href="#" class="btn btn-lg btn-secondary" onclick="mostrarDespachador()">Despachador</a>
            </p>
          </div>



          <!--****************************************************CLIENTE***************************************************************-->
          <!--**************************************************************************************************************************-->
          <div class="row" id="secCliente" style="display:none">
	          <div class="col-xs-2"></div>
	          <div class="cliente col-xs-8">
	          	<form action="cliente/validaCliente.php" method="POST">
	          		<h1>Login Cliente</h1></br>
		          	<div class="input-group">
		          		<span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
		          		<input type="text" class="form-control" placeholder="Usuario" name="usrCl" id="usrCl">
		          	</div>
		          	</br>
		          	<div class="input-group">
		          		<span class="input-group-addon"><i class="glyphicon glyphicon-lock"></i></span>
		          		<input type="password" class="form-control" placeholder="Contrase&ntilde;a" name="pwdCl" id="pwdCl">
		          	</div>
		          	</br>

		          	<div class="col-xs-2"></div>
	          		<input type="submit" class="btn btn-primary col-xs-8 " value="Ingresar">
	          		<div class="col-xs-2"></div>
	          		</br></br>
	          		<div class="col-xs-2"></div>
	          		<button type="button" class="btn btn-primary col-xs-8 " onclick="volver()">Volver</button>

	          		<?php 
						if($error=='1'){echo("</br></br><span style='color:red;'>Usuario incorrecto.</span>");}else{}
					?>

	          	</form>
	          </div>
	          <div class="col-xs-2"></div>
      	 </div>
      	 <!--**************************************************************************************************************************-->
       




      	 <!--****************************************************DESPACHADOR***********************************************************-->
         <!--**************************************************************************************************************************-->
      	 <div class="row" id="secDespachador" style="display:none">
	          <div class="col-xs-2"></div>
	          <div class="cliente col-xs-8">
	          	<form action="despachador/validaDespachador.php" method="POST">
	          		<h1>Login Despachador</h1></br>
		          	<div class="input-group">
		          		<span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
		          		<input type="text" class="form-control" placeholder="Usuario" name="usrDs" id="usrDs">
		          	</div>
		          	</br>
		          	<div class="input-group">
		          		<span class="input-group-addon"><i class="glyphicon glyphicon-lock"></i></span>
		          		<input type="password" class="form-control" placeholder="Contrase&ntilde;a" name="pwdDs" id="pwdDs">
		          	</div>
		          	</br>

		          	<div class="col-xs-2"></div>
	          		<input type="submit" class="btn btn-primary col-xs-8" value="Ingresar">
	          		<div class="col-xs-2"></div>
	          		</br></br>
	          		<div class="col-xs-2"></div>
	          		<button type="button" class="btn btn-primary col-xs-8" onclick="volver()">Volver</button>

	          		<?php 
						if($error=='2'){echo("</br></br><span style='color:red;'>Usuario incorrecto.</span>");}else{}
					?>

	          	</form>
	          </div>
      	</div>
      	<!--**************************************************************************************************************************-->


        </div>

      </div>

    </div>




<!--
<?php

	//include("consultas.php");

	consultar_detalles_del_recibo();

?>
-->





	<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.2.0/js/tether.min.js" integrity="sha384-Plbmg8JY28KFelvJVai01l8WyZzrYWG825m+cZ0eDDS1f7d/js6ikvy1+X+guPIB" crossorigin="anonymous"></script>

</body>
</html>
