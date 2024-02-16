<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>Serre - La Providence</title>
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
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Exo&display=swap" rel="stylesheet">
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
          <li class="active"><a href="accueil.php">Acceuil</a></li>
          <li><a href="table.php">Tableau</a></li>
          <li><a href="graph.php">Graphique</a></li>
          <!-- <li><a href="modification.php">Compte</a></li> -->
          <li><a href="Admin.php">Admin</a></li>
          <lI><a href="fonctions/deconnexion.php">Deconnexion</a></li>
        </ul>
      </div>
    </div>
  </div>

  <section id="Acceuil">
    <!--<div id="headerwrap">
      <div class="container">
        <div class="row centered">
          <div class="col-lg-12">
            <img class="Logo-lapro" src="img/favicon.png" alt="">
            <h1>Bienvenue sur le site de <b>la Serre</b></h1>
            <h3>Le site Web qui permet aux usagers de<br>
              visionner les informations en provenance de la serre !
            </h3>
            <br>
            <img class="serre" src="img/serre.png" alt="">
          </div>
         
        </div>
      </div>
      
    </div>-->

    <section id="intro">
      <div class="info">
        <h1>Serre Automatisée</h1>
        <p>
          Explorez l'agriculture du futur avec notre serre automatisée. Cultivez intelligemment, économisez les ressources, maximisez les rendements. Bienvenue dans l'ère de l'agriculture innovante.
        </p>
        <a href="#" class="button explore">Voir plus</a>
      </div>
      <div class="split-beer">
        <img class="beer" src="img/gauche_serre.png" />
        <img class="beer" src="img/middle_serre.png" />
        <img class="beer" src="img/droite_serre.png" />
      </div>
    </section>

  </section>
  <script type="text/javascript">
    const modalOpenBtns = document.querySelectorAll(".modal-open");
    const modalCloseBtns = document.querySelectorAll(".modal-close");
    const body = document.querySelector("body");

    modalOpenBtns.forEach((btn) => {
      btn.addEventListener("click", () => {
        let modal = btn.getAttribute("data-modal");
        document.getElementById(modal).style.display = "block";
        body.classList.add("prevent-background-scroll");
      });
    });

    modalCloseBtns.forEach((btn) => {
      btn.addEventListener("click", () => {
        let modal = (btn.closest(".modal").style.display = "none");
        body.classList.remove("prevent-background-scroll");
      });
    });

    document.addEventListener("click", (e) => {
      if (e.target.classList.contains("modal")) {
        e.target.style.display = "none";
        body.classList.remove("prevent-background-scroll");
      }
    });
  </script>
  <section id="desc">
    <!-- INTRO WRAP -->

    <div id="desc_grid">
      <div class="grid">
        <div class="card"><img class="card__img" src="https://corporate.walmart.com/content/dam/corporate/images/global-responsibility/sustainability/planet/nature/businessfornature-banner.png" alt="Snowy Mountains">
          <div class="card__content">
            <h1 class="card__header">Responsable Technique</h1>
            <div class="card__text-wrapper">
              <p class="card__text">Sous la bienveillance du CP, le RT doit étudier et préparer la mise en place d’une solution PHP Orienté
                objet. Il doit mettre en place l’architecture du projet (serveur / BDD / paramétrage) </p>
            </div>
            <!-- <button class="card__btn">Explore <span>&rarr;</span></button> -->
          </div>
        </div>
        <div class="card"><img class="card__img" src="https://uicn.fr/wp-content/uploads/2023/03/couverture-_g.-karczewski-pnc_-min-scaled.jpeg" alt="Desert">
          <div class="card__content">
            <h1 class="card__header">Chef d'équipe</h1>
            <div class="card__text-wrapper">
              <p class="card__text">Suivi du projet avec une réunion régulièrement en compagnie des autres CP et de l’Enseignant. Rédaction
                du cahier des charges avec les recommandations techniques du RT</p>
            </div>
            <!-- <button class="card__btn">Explore <span>&rarr;</span></button> -->
          </div>
        </div>
        <div class="card"><img class="card__img" src="https://images.squarespace-cdn.com/content/v1/5feb6d2cab06677bba637eba/d72ddeeb-d2bd-4779-99be-8bbd6845fbc8/LAM+images+%284%29.jpg" alt="Canyons">
          <div class="card__content">
            <h1 class="card__header">Developeur</h1>
            <div class="card__text-wrapper">
              <p class="card__text">Développer le projet en se basant uniquement sur le cahier des charges en cours de validations par le CP.
                Il commencera donc à développer le site avecses connaissances puis avec l’aide du RT.</p>
            </div>
            <!-- <button class="card__btn">Explore <span>&rarr;</span></button> -->
          </div>
        </div>
      </div>
    </div>

    <section id="contact">
      <!-- <div id="footerwrap">
        <div class="container">
          <div class="col-lg-5">
            <p>
            <h3>Address</h3>
            Association ou organisation<br>
            146 Bd de Saint-Quentin<br>
            Amiens<br>
            2023<br>
            France
            </p>
          </div>
        </div>
      </div> -->
      <!-- Site footer -->
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
    </section>

    <!-- JavaScript Libraries -->
    <script src="lib/jquery/jquery.min.js"></script>
    <script src="lib/bootstrap/js/bootstrap.min.js"></script>
    <script src="lib/php-mail-form/validate.js"></script>
    <script src="lib/easing/easing.min.js"></script>

    <!-- Template Main Javascript File -->
    <script src="js/main.js"></script>
  </section>
</body>

</html>