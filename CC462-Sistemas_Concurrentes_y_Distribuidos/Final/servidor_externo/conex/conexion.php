<?php

	function conectar(){
                error_reporting(E_COMPILE_ERROR|E_ERROR|E_CORE_ERROR);
		//mysql_connect("mysql.hostinger.com.ar", "u879094972_cccp", "pokegocc");
                mysql_connect("localhost", "u879094972_cccp", "pokegocc");
		mysql_select_db("u879094972_venta");
		mysql_query("SET NAMES 'utf8'");
	}

	function desconectar(){
		mysql_close();
	}

?>