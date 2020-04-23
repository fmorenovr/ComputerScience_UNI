<!DOCTYPE html>
<html>
 <head>
   <!--Import Google Icon Font-->
   <link href="http://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
   <!--Import materialize.css-->
   <link type="text/css" rel="stylesheet" href="static/css/materialize.min.css"  media="screen,projection"/>
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
          <span class="card-title grey-text text-darken-4">Distributed Chat (with multicast)</span>
        </div>
      </div>
    </div>
  </div>
  <div class="row">
    <div class="input-field col s12 m6 l5">
      <form class="col s12" action="/send" method="POST">
        <div class="row">
          <div class="input-field col s12 m12 l12">
            <i class="material-icons prefix">account_circle</i>
            %if name != None:
            <input value="{{name}}" name="name" id="name" type="text" class="validate" required="validate">
            %else:
            <input name="name" id="name" type="text" class="validate" required="validate">
            %end
            <label for="name">Name</label>
          </div>
        </div>
        <div class="row">
          <div class="input-field col s12 m12 l12">
            <i class="material-icons prefix">message</i>
            <textarea name="message" id="message" class="materialize-textarea" required="validate"></textarea>
            <label for="message">Message</label>
          </div>
        </div>
        <div class="row">
          <div class="col offset-s4 offset-m4 offset-l4">
            <button class="btn waves-effect waves-light" type="submit" name="action">Submit
              <i class="material-icons right">send</i>
            </button>
          </div>
        </div>
      </form>
    </div>
    <div id="chat" class="input-field col s12 m6 l7">
      <div id="intChat" class="card teal">
        <div class="card-content white-text">
          <span class="card-title">Chat:</span>
          <p>
            %for (nme, message) in chatContent:
            <div style="word-wrap: break-word">
              <li> <b>{{nme}}:</b> {{message}} </li>
            </div>
            %end
          </p>
        </div>
      </div>
    </div>
  </div>
  <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
  <script type="text/javascript" src="static/js/materialize.min.js"></script>
  <!-- To reload only the chat div: using AJAX and realoading every 1000 milliseconds -->
  <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script type="text/javascript">
    var auto_refresh = setInterval(function (){ $("#chat").load("/chat #intChat");}, 1000);
  </script>
</body>
</html>
