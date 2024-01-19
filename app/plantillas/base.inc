<!DOCTYPE html>
<html>

<head>
  <title>Biblioteca Lorem Ipsum</title>
  <meta charset="utf-8">

  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" type="text/css" href='web/css/estilos.css' />
  <link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@500&display=swap" rel="stylesheet">

</head>

<body>
  <header>
    <p class="titulo">Biblioteca Lorem Ipsum</p>
    <p class="subtitulo">Dode leer cunde</p>
    <?php
    if (isset($_SESSION['usuario'])) {
      echo '<p class="test">Bienvenido! ' . $_SESSION['usuario'] . '</p>';
    }
    ?>
    <nav>
      <a href="index.php?ctl=inicio">Inicio</a>
      <!-- MANEJAMOS EL ACCESO A LOS BOTONES EN FUNCIÓN DE SI ESTÁ SESIÓN INICIADA -->
      <?php if (isset($_SESSION['usuario'])) : ?>
        <a href="index.php?ctl=askForBooks">Pedir libros</a>
        <a href="index.php?ctl=returnUserBooks">Devolver libros</a>
        <a href="index.php?ctl=logOut">Cerrar Sesión</a>
      <?php else : ?>
        <a href="index.php?ctl=login">Iniciar Sesion</a>
      <?php endif; ?>
    </nav>

  </header>

  <div id="contenido">
    <?= $contenido ?>
  </div>
  
  <footer>
    <hr>
    <p style="text-align:center">- Pie de página -</p>
  </footer>
</body>

</html>