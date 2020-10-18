<html>
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link
      rel="stylesheet"
      href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
    />
    <link rel="stylesheet" href="/css/starter-sample.css" />
    <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
    <script
      src="https://unpkg.com/obniz@3.9.0/obniz.js"
      crossorigin="anonymous"
    ></script>
  </head>
  <body>
    
<div id="obniz-debug"></div>
<h1>obniz instant html</h1>
<button id="on">ON</button>
<button id="off">OFF</button>
<div id="print"></div>

<script>

var obniz = new Obniz("");

obniz.onconnect = async function(){
  obniz.plugin.onreceive = data => {
    console.log((new TextDecoder).decode(Uint8Array.from(data)));
  };


$('#on').on('click', function() {
    obniz.plugin.send("Obniz message");
  });
}

</script>
</body>
</html>
