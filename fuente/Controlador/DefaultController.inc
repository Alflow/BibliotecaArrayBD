<?php
// Ejemplo de controlador para página home de la aplicación
require_once __DIR__ . '/../Repositorio/FileToArrayToFile.php';

class DefaultController
{
  public function inicio() //Función que extrae el array de existencias y se lo lleva a la vista del index.php con el header
  {
    //Creamos el objeto bibliotecaRepositorio.
    $checker = new FileToArrayToFile();
    //guardamos en una variable lo que que nos devuelve el método del objeto.
    $library = $checker->getArrayFromFile(LIBROS_FILE);

    // incluimos a la vista del inicio
    include __DIR__ . '/../../app/plantillas/inicio.inc';
  }
}
