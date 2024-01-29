<?php

$titulo = $_GET['tituloDetalles'];

$tituloApi = str_replace(" ", "%20", $titulo);


$urlBase = 'https://www.googleapis.com/books/v1/volumes?q=intitle:';
$content = file_get_contents($urlBase . $tituloApi);
$data = json_decode($content, true);
$img = $data['items'][9]['volumeInfo']['imageLinks']['thumbnail'];
$description = ($data['items'][9]['volumeInfo']['description']);

?>
<?php ob_start(); ?>


<!-- PÁGINA QUE MUESTRA LOS DETALLES DEL LIBRO  -->
<div class="libroContainer">
    <div class="portada">
        <?php
        echo '<img src="' . $img . '" alt="portada de libro"';
        ?>
    </div>


</div>
<div class="datosLibro">
    <h1>
        Título : <?= $titulo  ?>
    </h1>
    <h2> Descripción </h2>
    <p> <?= $description   ?></p>
</div>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.inc' ?>