<!DOCTYPE html>
<html>
  <head>
    <!--Import Google Icon Font-->
    <link href="http://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <!--Import materialize.css-->
    <link type="text/css" rel="stylesheet" href="static/css/materialize.min.css"  media="screen,projection"/>
    <link type="text/css" rel="stylesheet" href="static/css/chat.css"/>
    <!--Let browser know website is optimized for mobile-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Chat</title>
  </head>

  <body>
    <div class="row">
      <div class="input-field col s12 m12 l12">
        <div class="card">
          <div class="card-image">
            <img src="static/teal.jpg">
          </div>
          <div class="card-content">
            <span class="card-title grey-text text-darken-4">Task 1</span>
          </div>
        </div>
      </div>
    </div>
    <div class="row">
      <form class="col s12 m6" action="send" method="post">
        <div class="row">
          <div class="input-field col s12">
      	    <select name="select" id="select" required>
      	      <option value="" disabled selected>Choose an option</option>
      	      <option value="c">Create variable</option>
      	      <option value="r">Remove variable</option>
      	      <option value="a">Add variable to variable</option>
      	      <option value="ai">Add integer to Variable</option>
      	    </select>
      	    <label>Option</label>
      	  </div>
        </div>
        <div class="row">
	         <div class="input-field col s12 m6">
              <input name="par1" placeholder="Parâmetro 1" id="par1" type="text" class="validate" required>
              <label for="par1">Parameter 1</label>
          </div>
          <div class="input-field col s12 m6">
            <input name="par2" placeholder="Parâmetro 2" id="par2" type="text">
            <label for="par2">Parameter 2</label>
          </div>
        </div>
        <div class="row">
          <div class="col offset-s5">
            <button class="btn waves-effect waves-light" type="submit" name="action" style="margin-top: 2em">Send
              <i class="material-icons right">send</i>
            </button>
          </div>
        </div>
      </form>
      <div id="chat" class="col s12 m6">
        <div id="inchat">
          <strong>Variables of BD:</strong>
          <ul>
           %for k in dados.keys():
          <li><b>{{k}}</b>: {{dados[k]}}</li>
          %end
          </ul>
        </div>
      </div>
    </div>
    <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
    <script type="text/javascript" src="static/js/materialize.min.js"></script>
    <!-- To reload only the chat div: using AJAX and realoading every 1000 milliseconds -->
    <script type="text/javascript">
      var auto_refresh = setInterval(function (){ $("#chat").load("/ #inchat"); }, 1000);
    </script>
    <script>
      $(document).ready(function() {
      $('select').material_select();
      });
    </script>
  </body>
</html>
