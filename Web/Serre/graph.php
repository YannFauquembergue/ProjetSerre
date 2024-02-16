<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>SITE | Graphique de données</title>
  <meta content="width=device-width, initial-scale=1.0" name="viewport">
  <meta content="" name="keywords">
  <meta content="" name="description">

  <!-- Favicons -->
  <link href="img/favicon.png" rel="icon">
  <link href="img/apple-touch-icon.png" rel="apple-touch-icon">

  <!-- Google Fonts -->
  <link href="https://fonts.googleapis.com/css?family=Lato:300,400,700,300italic,400italic%7CRaleway:400,300,700" rel="stylesheet">

  <!-- Bootstrap CSS File -->
  <link href="lib/bootstrap/css/bootstrap.min.css" rel="stylesheet">

  <!-- Main Stylesheet File -->
  <link href="css/style.css" rel="stylesheet">

  <script type="text/javascript"></script>
</head>

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
        <a class="navbar-brand smothscroll" href="#Acceuil"><b>SERRE</b></a>
      </div>
      <div class="navbar-collapse collapse">
        <ul class="nav navbar-nav">
          <li><a href="accueil.php">Acceuil</a></li>
          <li><a href="table.php">Tableau</a></li>
          <li class="active"><a href="graph.php">Graphique</a></li>
          <!-- <li><a href="modification.php">Compte</a></li> -->
          <li><a href="Admin.php">Admin</a></li>
          <li><a href="fonctions/deconnexion.php">Deconnexion</a></li>
        </ul>
      </div>
    </div>
  </div>

  <section id="Acceuil">
    <div id="headerwrap">
      <div class="container">
        <div class="row centered">
          <div class="col-lg-12">
            <h3><b>Graphique des données</b></h3>
          </div>

          <div class="graphique">
            <h3><b>DONNÉE EN TEMPS RÉELLE</b></h3>
            <center>
              <?php
              (include 'api/graph1.php')
              ?>
            </center>
          </div>



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
              <li><a href="#">Acceuil</a></li>
              <li><a href="#">Tableau</a></li>
              <li><a href="#">Graphique</a></li>
              <li><a href="#">Compte</a></li>
              <li><a href="#">Admin</a></li>
              <li><a href="#">Deconnexion</a></li>
            </ul>
          </div>

          <div class="col-xs-6 col-md-3">
            <h6>Liens utiles</h6>
            <ul class="footer-links">
              <li><a href="#">A propos</a></li>
              <li><a href="#">Nous contacter</a></li>
              <li><a href="#">Contribuer</a></li>
              <li><a href="#">Conditions générales d'utilisation</a></li>
              <li><a href="#"">Politique de confidentialité</a></li>
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
    </script-->

    <!-- Template Main Javascript File -->
    <script src="js/main.js"></script>
  </section>
</body>

</html>