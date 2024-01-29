<?php
// Ejemplo de controlador para página home de la aplicación
require_once __DIR__ . '/../Repositorio/GestionBdRepositorio.php';

class DefaultController
{
  public function inicio() //Función que extrae el array de existencias y se lo lleva a la vista del index.php con el header
  {
    //Creamos el objeto GestionBDRepositorio.
    $library = (new GestionBdRepositorio())->getLibros();



    // incluimos a la vista del inicio
    include __DIR__ . '/../../app/plantillas/inicio.inc';
  }

  public function showBookDetails() //Función que extrae el array de existencias y se lo lleva a la vista del index.php con el header
  {
    //Creamos el objeto GestionBDRepositorio.
    $library = (new GestionBdRepositorio())->getLibros();



    // incluimos a la vista del inicio
    include __DIR__ . '/../../app/plantillas/bookDetails.inc';
  }
}
