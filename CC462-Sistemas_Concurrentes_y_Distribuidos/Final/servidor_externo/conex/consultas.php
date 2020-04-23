<?php
	/*
	function conectar(){
		mysql_connect("localhost", "root", "root");
		mysql_select_db("u879094972_venta");
		mysql_query("SET NAMES 'utf8'");
	}

	function desconectar(){
		mysql_close();
	}
	*/
	function consultar_productos(){
		$query = " SELECT * FROM producto WHERE iddr='1'; ";
		$sql = mysql_query($query);
	}


	function consultar_detalles_del_recibo(){
		conectar();

		$query = " SELECT * FROM recibo; ";
		$sql = mysql_query($query);

		$cont = mysql_num_rows($sql);

		if($cont>0){

			/****************************************************************************************************************/
			while($row1=mysql_fetch_array($sql)){
				$idr = $row1['idr'];
		        $idc = $row1['idc'];
		        $total = $row1['total'];
		        $cod_banco = $row1['idcodbanco'];
		        $estado = $row1['estado'];

		        if($estado==0) $std="No se ha pagado con una transacci&oacute;n bancaria";
		        if($estado==1) $std="Se ha pagado por transferencia bancaria";
		        if($estado==2) $std="Producto entregado";

		        $consl = mysql_query(" SELECT * FROM cliente WHERE idc = '".$idc."'; ");
		        $fila=mysql_fetch_array($consl);
		        $nombre = $fila['nombre'];

		        echo ("</br>
		        <div class='col-xs-0' style='background:'>
		        <h3>Cliente: ".$nombre."</h3>
		        <h5>C&oacute;digo bancario: ".$cod_banco."</h5>
		        <h5>Estado: ".$std."</h5>
		        </br>
				<table class='table-bordered table-condensed table-hover miTabla'>
				<tr>
					<th></th>
					<th>Producto</th>
					<th>Cantidad</th>
					<th>Precio</th>
				</tr>");

		        $sql2 = mysql_query(" SELECT * FROM detalle_recibo WHERE iddr = '".$idr."'; ");

		        $total_cm = 0;
		        $i = 1;
		        while($row2=mysql_fetch_array($sql2)){

		        	$idp = $row2['idp'];
		        	$cant = $row2['idr'];

		        	$sql3 = mysql_query(" SELECT * FROM producto WHERE idp = '".$idp."'; ");
			        $row3=mysql_fetch_array($sql3);
			        $nombre_p = $row3['nomp'];
			        $precio_p = $row3['prep'];
			        $cant_p = $row3['cantp'];


			        $prc = $cant * $precio_p;
			        $total_cm = $prc + $total_cm;

			        echo "
			        <tr>
			        	<th>".$i.")</th>
			        	<th>".$nombre_p."</th>
			        	<th>".$cant."</th>
			        	<th>".$prc."</th>
			        </tr>";

			        $i = $i + 1;
		        }

		        echo ("
		        	<tr>
			        	<th>Total</th>
			        	<th></th>
			        	<th></th>
			        	<th>".$total_cm."</th>
			        </tr>
		        </table>");
		     	
		        echo "</br></br><HR>";
		        echo "</div>";
			}
			/****************************************************************************************************************/

			echo ("</br></br>");
		}

		else{
			echo "Todavia no cuenta con pedidos.";
		}

	}

?>