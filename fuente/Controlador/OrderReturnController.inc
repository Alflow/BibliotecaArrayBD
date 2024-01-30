<?php
// Ejemplo de controlador para página home de la aplicación
require_once __DIR__ . '/../Repositorio/GestionBdRepositorio.php';

require_once __DIR__ . '/../../app/utilidades/sanea.inc';

class OrderReturnController
{
    public function returnUserBooks() //Función para devolver los libros. 
    {

        //instanciamos un gestor de Base de datos
        $gestorBD = new GestionBdRepositorio();

        if (isset($_SESSION['usuario'])) {
            $correoUsuario = $_SESSION['usuario'];

            if (isset($_POST['okReturn'])) {

                //insertamos en una variable los inputs de libros a devolver y la saneamos
                $booksForReturn = $_POST['booksForReturn'];
                foreach ($booksForReturn as &$bookForReturn) {
                    $bookForReturn = sanea($bookForReturn);
                }
                // Rompemos la referencia después del bucle
                unset($bookForReturn);

                //extraemos el array de libros que están prestados
                $borrowedBooks =  $gestorBD->getLibrosPrestadosPorSocio($correoUsuario);

                $gestorBD->devolverLibrosPrestados($booksForReturn);
                header('location: index.php?ctl=returnUserBooks');
            } else {

                //Extraemos el array de Libros prestados y el array de libros general para tener los titulos, autores etc para la vista
                $borrowedBooks =  $gestorBD->getLibrosPrestadosPorSocio($correoUsuario);


                if (empty($borrowedBooks)) {
                    echo '<script> alert("No tienes libros prestados!") </script>';
                }
            }
        }
        include __DIR__ . '/../../app/plantillas/return.inc';
    }

    public function askForBooks() //función para pedir los libros deseados. 
    {
        //instanciamos un gestor de Base de datos
        $gestorBD = new GestionBdRepositorio();

        //extraemos el array de libros que están prestados
        $borrowedBooks =  $gestorBD->getLibrosDisponibles();
        //extraemos el array de librería
        $library = $gestorBD->getLibros();

        if (isset($_SESSION['usuario'])) {
            if (isset($_POST['okAsk'])) {
                //insertamos en una variable los inputs de libros a devolver y la saneamos
                if (isset($_POST['booksForAsk'])) {
                    $booksForAsk = $_POST['booksForAsk'];
                    foreach ($booksForAsk as &$bookForAsk) {
                        $bookForAsk = sanea($bookForAsk);
                    }
                    // Rompemos la referencia después del bucle
                    unset($bookForAsk);
                    // var_dump($booksForAsk); FUNCIONA!

                    $gestorBD->pedirLibrosPrestados($booksForAsk);
                    //pido y redirijo
                    header('location: index.php?ctl=askForBooks');
                } else {
                    echo '<script> alert("No has solicitado libros!!!!") </script>';
                }
            }
        }
        include __DIR__ . '/../../app/plantillas/askForBooks.inc';
    }
}
