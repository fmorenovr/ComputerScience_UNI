<!DOCTYPE html>

<head>
	<title>BuscaMinas</title>
	<meta lang="pt-br">
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1" >

	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">

	<!-- Latest compiled and minified JavaScript -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>

	<script src="https://code.jquery.com/jquery-3.2.1.min.js" integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4=" crossorigin="anonymous"></script>
	
	<style type="text/css">
		.pnHead{
			height: 70px;
		}
		.divJogada{
			border: solid 1px black;
			border-radius:10px;
			background-color: #ddd;
		}
		#perdeuJogo{
			color: red;
			font-size: 20px;
		}
		strong{
			float: right;
			margin-right: 5px;
		}
		.table2{
		    position: fixed;
		    top: 5px;
		    text-align: center;
		    padding: 20px;
		    border: solid 1px black;
		    width: 30%;
		    left: 5px;
		    color: darkslateblue;
			
		}
		td, th { text-align: center }
		
	</style>

	<script>
		$(document).ready(function(){
			$("#formJogada").hide();
		});
	
		function jogada(jog) {
			
			var linha, col;
			
			linha = jog.parentElement.parentElement.rowIndex;
			col = jog.parentElement.cellIndex;
			
			$("#linha").val(linha);
			$("#coluna").val(col);
			
			$("#btnJogada").trigger("click");
			
			
			return;
			
		}
		function block(){
			$("#table").attr("disabled", "disabled");
			alert("sdsdsd");
		}
	
		(function(window) { 
		  'use strict'; 
		 
			var noback = { 
			 
			//globals 
			version: '0.0.1', 
			history_api : typeof history.pushState !== 'undefined', 
			 
			init:function(){ 
				window.location.hash = '#no-back'; 
				noback.configure(); 
			}, 
			 
			hasChanged:function(){ 
				if (window.location.hash == '#no-back' ){ 
					window.location.hash = '#BLOQUEIO';
					//mostra mensagem que não pode usar o btn volta do browser
					if($( "#msgAviso" ).css('display') =='none'){
						$( "#msgAviso" ).slideToggle("slow");
					}
				} 
			}, 
			 
			checkCompat: function(){ 
				if(window.addEventListener) { 
					window.addEventListener("hashchange", noback.hasChanged, false); 
				}else if (window.attachEvent) { 
					window.attachEvent("onhashchange", noback.hasChanged); 
				}else{ 
					window.onhashchange = noback.hasChanged; 
				} 
			}, 
			 
			configure: function(){ 
				if ( window.location.hash == '#no-back' ) { 
					if ( this.history_api ){ 
						history.pushState(null, '', '#BLOQUEIO'); 
					}else{  
						window.location.hash = '#BLOQUEIO';
						//mostra mensagem que não pode usar o btn volta do browser
						if($( "#msgAviso" ).css('display') =='none'){
							$( "#msgAviso" ).slideToggle("slow");
						}
					} 
				} 
				noback.checkCompat(); 
				noback.hasChanged(); 
			} 
			 
			}; 
			 
			// AMD support 
			if (typeof define === 'function' && define.amd) { 
				define( function() { return noback; } ); 
			}  
			// For CommonJS and CommonJS-like 
			else if (typeof module === 'object' && module.exports) { 
				module.exports = noback; 
			}  
			else { 
				window.noback = noback; 
			} 
			noback.init();
		}(window));
	</script>

</head>

<body>

	<div class="container">	

		<div class="container">
 				
 		<div class="panel panel-primary col-sm-offset-4 col-sm-8">
 			<div class="panel-heading pnHead">
				<h3>BuscaMinas <strong class="text-right" id="pontos">Puntos : {{pontos}}</strong></h3>
				  	
			</div >
			<table class="table" id="table" disabled="">
				<thead><tr><th></th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>10</th></tr></thead>
				<tbody>
					%i=0
					%cont=0
					%for (i) in range (len(tabuleiroView)):
						<tr><th>{{i+1}}</th>
							%j=0
							%for (j) in range (len(tabuleiroView)):
    							
    								%if tabuleiroView[i][j] == "*":
    									%cont=1
    									<td id="perdeuJogo">&#10037;</td>
    									
    								%else :
    									%if tabuleiroView[i][j] == -1 :
    										%tabuleiroView[i][j]=0
    									%end
    									%if estado == "jogando":
    										<td><button class="btn" onclick="jogada(this)">{{tabuleiroView[i][j]}}</button></td>	
    									%else:
    										<td>{{tabuleiroView[i][j]}}</td>
    									%end				
									%end
									
							%end

						</tr>
						
					%end
						
				</tbody>
			</table>
					
			
		
		</div>

		<div class="col-sm-3">
			<table class="table table2">
				<thead><tr><th>Jogador</th><th>Puntos/Estado</th></tr></thead>
				<tbody>			
					%for key in hash:
						<tr><td>{{key}}</td><td>{{hash[key]}}</td></tr>	
					%end
				</tbody>
			</table>		
		</div>			
		</div>		

	<div class="container col-sm-6 col-sm-offset-4 divJogada" id="formJogada">
			<h4 class="text-primary">Ingrese XY:</h4>
			<form class="form-horizontal" action="/jogada" method=POST>
				<div class="form-group">
					<label class="col-sm-4" for="linha">Pos linea:</label>
					<input class="col-sm-8" id="linha" name="x" type="number" required autofocus="on" max="10" min="1"/> 
				</div>
				<div class="form-group">
					<label class="col-sm-4" for="coluna">Pos Columna :</label>
					<input class="col-sm-8" id="coluna" name="y" type="number" required max="10" min="1"/>
				</div>
				<div class="form-group">
					<input class="col-sm-4 col-sm-offset-4 btn btn-sm btn-success" value="Enviar" type="submit" id="btnJogada" />
				</div>
			</form>
		</div> 	
	</div>	
</body>

<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script type="text/javascript">
    	var auto_refresh = setInterval(function (){ $("#table").load("/tabuleiro #table");}, 500);
		var auto_refresh3 = setInterval(function (){ $("#pontos").load("/tabuleiro #pontos");}, 100);
		var auto_refresh2 = setInterval(function (){ $(".table2").load("/tabuleiro .table2");}, 100);
</script>

</html>
