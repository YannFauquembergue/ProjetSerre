<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>SITE | Tableau de données</title>
  <meta content="width=device-width, initial-scale=1.0" name="viewport">
  <meta content="" name="keywords">
  <meta content="" name="description">

  <!-- Favicons -->
  <link href="img/favicon.png" rel="icon">
  <link href="img/apple-touch-icon.png" rel="apple-touch-icon">
  <link href="https://fonts.googleapis.com/css2?family=Exo&display=swap" rel="stylesheet">

  <!-- Google Fonts -->
  <link href="https://fonts.googleapis.com/css?family=Lato:300,400,700,300italic,400italic%7CRaleway:400,300,700" rel="stylesheet">

  <!-- Bootstrap CSS File -->
  <link href="lib/bootstrap/css/bootstrap.min.css" rel="stylesheet">

  <!-- Main Stylesheet File -->
  <link href="css/style.css" rel="stylesheet">
  <script type="text/javascript"> </script>

  <!-- réact commande pour récupérer le dernier buid : scp -r debian@192.168.64.215:/home/debian/front/build/static /var/www/html/Serre -->
  <script defer="defer" src="static/js/main.6f0cf976.js"></script>
  <link href="static/css/main.e56fedbd.css" rel="stylesheet">


</head>
<style>
  /* Styles for the root element */
  /* Styles for the configuration section */
  #headerwrap {
    background-color: #fff;
  }

  #headerwrap h1 {
    color: black;
  }

  @media(max-width: 400px) {
    #headerwrap h1 {
      font-size: 18px;
    }

  }

  .configuration {
    margin-bottom: 20px;
    user-select: text;
  }

  /* Styles for the WebSocket input */
  .configuration input {
    padding: 8px;
    width: 200px;
    margin-right: 10px;
  }

  /* Styles for the "Go" button */
  .configuration button {
    padding: 8px 15px;
    background-color: #4caf50;
    color: white;
    border: none;
    cursor: pointer;
  }

  /* Styles for the IP paragraphs */
  .configuration p {
    margin-top: 10px;
  }

  /* Specific styles for IP paragraphs */
  .configuration p:nth-child(2) {
    color: #2196f3;
  }

  .configuration p:nth-child(3) {
    color: #f44336;
  }

  /* Styles for the sensors and actuators section */
  .capteurs,
  .actionneurs {
    margin-bottom: 10px;
  }

  .capteurs-span,
  .actionneurs-span {
    font-weight: bold;
    margin-right: 10px;
  }

  /* Specific styles for individual actuators */
  .actionneurs-Brumisation span,
  .actionneurs-Chauffage1 span,
  .actionneurs-HumidifierSerre span,
  .actionneurs-PompeBac span,
  .actionneurs-VanneReseauEau span,
  .actionneurs-VanneReseauPluie span,
  .actionneurs-VerinFenetre span {
    color: #555;
  }

  /* Styles for the App-link */
  .App-link {
    color: #61dafb;
    text-decoration: none;
  }

  .App-link:hover {
    text-decoration: underline;
  }
</style>

<body data-spy="scroll" data-offset="0" data-target="#navigation">
  <!-- Fixed navbar -->
  <div id="navigation" class="navbar navbar-default navbar-fixed-top">
    <div class="container">
      <div class="navbar-header">
        <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button>
        <a class="navbar-brand smothscroll" href="#Accueil"><b>SERRE</b></a>
      </div>
      <div class="navbar-collapse collapse">
        <ul class="nav navbar-nav">
          <li><a href="accueil.php">Accueil</a></li>
          <li class="active"><a href="table.php">Tableau</a></li>
          <li><a href="graph.php">Graphique</a></li>
          <!-- <li><a href="modification.php">Compte</a></li> -->
          <li><a href="Admin.php">Admin</a></li>
          <li><a href="fonctions/deconnexion.php">Déconnexion</a></li>
        </ul>
      </div>
    </div>
  </div>

  <section id="Accueil">
    <div id="headerwrap">

      <div class="container">
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">Informations de connexion WebSocket</h5>
            <p class="card-text">
            <h1 id="adresses">IP Production : </h1><code>wss://serre.tspro.fr/ws</code>
            <!-- <span id="paddingleftspan"></span> -->
            <br>
            <h1 id="adresses">IP Test : </h1><code>wss://serre.tspro.fr/wsTest</code>
            </p>
          </div>
        </div>

        <div id="root">

        </div>
      </div>
      <!--/ .container -->
    </div>
    <!--/ #headerwrap -->
  </section>

  <section id="contact">
    <footer class="site-footer">
      <div class="container">
        <div class="row">
          <div class="col-sm-12 col-md-6">
            <h6>La Serre</h6>
            <p class="text-justify">Transformez votre façon de cultiver avec notre serre automatisée intelligente. Cultivez sans effort, maximisez les rendements. </p>
          </div>

          <div class="col-xs-6 col-md-3">
            <h6>Catégories</h6>
            <ul class="footer-links">
              <li><a href="#">Accueil</a></li>
              <li><a href="#">Tableau</a></li>
              <li><a href="#">Graphique</a></li>
              <li><a href="#">Compte</a></li>
              <li><a href="#">Admin</a></li>
              <li><a href="#">Déconnexion</a></li>
            </ul>
          </div>

          <div class="col-xs-6 col-md-3">
            <h6>Liens utiles</h6>
            <ul class="footer-links">
              <li><a href="#">A propos</a></li>
              <li><a href="#">Nous contacter</a></li>
              <li><a href="#">Contribuer</a></li>
              <li><a href="#">Conditions générales d'utilisation</a></li>
              <li><a href="#">Politique de confidentialité</a></li>
              </ul>
            </div>
          </div>
          <hr>
        </div>
        <div class=" container">
                  <div class="row">
                    <div class="col-md-8 col-sm-6 col-xs-12">
                      <p class="copyright-text">Copyright &copy; 2023 All Rights Reserved by
                        <a target="_blank" href="https://www.la-providence.net/fr/">La Providence Amiens</a>.
                      </p>
                    </div>
                  </div>
          </div>
    </footer>

    <!-- JavaScript Libraries -->
    <script src="lib/jquery/jquery.min.js"></script>
    <script src="lib/bootstrap/js/bootstrap.min.js"></script>
    <script src="lib/php-mail-form/validate.js"></script>
    <script src="lib/easing/easing.min.js"></script>

    <!--<script>
    setInterval(getDonnees, 1000);
  </script>-->

    <!-- Template Main Javascript File -->
    <script src="js/main.js"></script>
  </section>



  <!--<script>
    const socket = new WebSocket('ws://192.168.64.179:12345');
    //const socket = new WebSocket('ws://192.168.65.32:12345');

    socket.onmessage = function(event) {
      // On parse la chaîne JSON en objet JavaScript
      const data = JSON.parse(event.data);

      // On affiche la valeur de la propriété "ma_valeur" de l'objet
      console.log('Ma valeur : ', data.HumidInt);
      // On peut également afficher la valeur sur la page web
      var div = document.getElementById('capHumInt');
      div.innerHTML = data.HumidInt;

      console.log('Ma valeur : ', data.TempInt);
      div = document.getElementById('capTempInt');
      div.innerHTML = data.TempInt;

      console.log('Ma valeur : ', data.HumidSol1);
      div = document.getElementById('capHumBac1');
      div.innerHTML = data.HumidSol1;

      console.log('Ma valeur : ', data.HumidSol2);
      div = document.getElementById('capHumBac2');
      div.innerHTML = data.HumidSol2;

      console.log('Ma valeur : ', data.HumidSol3);
      div = document.getElementById('capHumBac3');
      div.innerHTML = data.HumidSol3;

      console.log('Ma valeur : ', data.TempExt);
      div = document.getElementById('capTempExt');
      div.innerHTML = data.TempExt;

      console.log('Ma valeur : ', data.ConsoElec);
      div = document.getElementById('consoElec');
      div.innerHTML = data.ConsoElec;

      console.log('Ma valeur : ', data.ConsoEauPluie);
      div = document.getElementById('consoEauPluie');
      div.innerHTML = data.ConsoEauPluie;

      console.log('Ma valeur : ', data.ConsoEauCourante);
      div = document.getElementById('consoEauCourante');
      div.innerHTML = data.ConsoEauCourante;

      console.log('Ma valeur : ', data.NiveauEau);
      div = document.getElementById('NiveauEau');
      div.innerHTML = data.NiveauEau;

    };


    socket.onerror = function(error) {
      console.error('WebSocket Error: ', error);
    };

    socket.onclose = function(event) {
      console.log('WebSocket Closed with code: ', event.code);
    };

    async function getDateFromTimeService() {
      try {
        const response = await fetch('https://worldtimeapi.org/api/ip');
        const data = await response.json();
        const date = new Date(data.datetime);
        const options = {
          weekday: 'long',
          year: 'numeric',
          month: 'long',
          day: 'numeric'
        };
        const dateDuJour = date.toLocaleDateString('fr-FR', options);
        document.getElementById('date').textContent = dateDuJour;
      } catch (error) {
        console.error('Erreur lors de la récupération de la date depuis le service de temps :', error);
      }
    }

    getDateFromTimeService();;
  </script>-->
</body>

</html>