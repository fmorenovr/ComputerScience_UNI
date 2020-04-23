<?php
	session_start(); 
	$cadenasegura='segura';

	if(isset($_SESSION['idDespachador']) and isset($_SESSION['nombreDespachador']) and isset($_SESSION['user'])){
		
		include("../conex/conexion.php");
		conectar();

		include("../conex/consultas.php");
?>

<html>

<head>
	<meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
	
	<link rel="icon" href="../../favicon.ico">
	<title>Concurrentes</title>
	
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

	<link href="../css/bootstrap.min.css" rel="stylesheet">

	<!-- Mi CSS -->
    <link href="../css/mystyle.css" rel="stylesheet">

    <!--********************************************************************************************-->
	<script type="text/javascript">

		function verPedidos(){
			if(document.getElementById('pedidos').style.display == 'none'){
				document.getElementById('pedidos').style.display = 'block';
				document.getElementById('menu').style.display = 'none';
			}
		}

		function volver(){
			if(document.getElementById('pedidos').style.display == 'block'){
				document.getElementById('pedidos').style.display = 'none';

				document.getElementById('menu').style.display = 'block';
			}
		}
	</script>
	<!--********************************************************************************************-->

</head>

<body>


	<div class="container">

                </br></br>

		<div class="row">
			<div class="col-xs-8">
				<h2>Bienvenido:<?php echo $_SESSION['nombreDespachador']; ?></h2>
			</div>
		</div>

		</br><hr></br></br>



		<!--****************MENU*************************************-->
		<div class="col-xs-10" id="menu">

			<div class="col-xs-1"></div>
			<button type="button" class="btn btn-success col-xs-10" onclick="verPedidos()">Ver todos los pedidos</button>

			</br></br></br></br>

			<div class="col-xs-1"></div>
			<a href="logout.php"><button type="button" class="btn btn-success col-xs-10">Salir</button></a>
		</div>
		<!--********************************************************************************************-->



		<div class="col-xs-0 row" id="pedidos" style="display:none">

			<button type="button" class="btn btn-success" onclick="volver()">Volver</button>
			</br></br></br>
			<?php consultar_detalles_del_recibo(); ?>
		</div>

	</div>



	<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.2.0/js/tether.min.js" integrity="sha384-Plbmg8JY28KFelvJVai01l8WyZzrYWG825m+cZ0eDDS1f7d/js6ikvy1+X+guPIB" crossorigin="anonymous"></script>

</body>
</html>

<?php
}

else{
	echo ("<html><head><META HTTP-EQUIV='Refresh' CONTENT='3; URL=logout.php'></head>
		<body><table align='center'><tr><td><table align='center'><tr><td><div><strong>
		<span style='color:red;'> Mucho Tiempo de Inactividad. <br/>
		<center>Vuelva a Loguearse.</center></span></div></td></tr></table></td></tr>
		</table></body></html>");
}

?>