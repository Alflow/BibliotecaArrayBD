<?php
// Ejemplo de controlador para página home de la aplicación
require_once __DIR__ . '/../Repositorio/FileToArrayToFile.php';
require_once __DIR__ . '/../../app/utilidades/sanea.inc';

class OrderReturnController
{
    public function returnUserBooks() //Función para devolver los libros. 
    {
        $checker = new FileToArrayToFile();

        if (isset($_SESSION['usuario'])) {

            if (isset($_POST['okReturn'])) {

                //insertamos en una variable los inputs de libros a devolver y la saneamos
                $booksForReturn = $_POST['booksForReturn'];
                foreach ($booksForReturn as &$bookForReturn) {
                    $bookForReturn = sanea($bookForReturn);
                }
                // Rompemos la referencia después del bucle
                unset($bookForReturn);

                //Extraemos los arrays
                $borrowedBooks = $checker->getArrayFromFile(LIBROS_PRESTADOS_FILE);
                $library = $checker->getArrayFromFile(LIBROS_FILE);

                //eliminamos del libros prestados la entrada
                foreach ($booksForReturn as $bookForReturnCode) {
                    foreach ($borrowedBooks as $index => $borrowedBookdetails) {
                        if ($borrowedBookdetails[0] == $bookForReturnCode) {
                            //elimina la posición del array de libros prestados
                            unset($borrowedBooks[$index]);
                            //actualiza el estado prestado de librería
                            if (isset($library[$bookForReturnCode])) {
                                $library[$bookForReturnCode]['prestado'] = 0;
                            }
                            break;
                        }
                    }
                }
                //reindexamos el array de libros prestados
                $borrowedBooks = array_values($borrowedBooks);
                //guarda y actualiza el fichero de libros prestados 
                $checker->saveFileWithArray(LIBROS_PRESTADOS_FILE, $borrowedBooks);
                //guarda y actualiza el fichero de existencias de libros 
                $checker->saveFileWithArray(LIBROS_FILE, $library);
            } else {

                //Extraemos el array de Libros prestados y el array de libros general para tener los titulos, autores etc para la vista
                $borrowedBooks = $checker->getArrayFromFile(LIBROS_PRESTADOS_FILE);
                $library = $checker->getArrayFromFile(LIBROS_FILE);

                //Preparamos un array para mostrar al usuario sus libros prestados
                $userBooks = [];

                foreach ($borrowedBooks as $borrowedBooksDetails) {
                    if ($borrowedBooksDetails[1] == $_SESSION['usuario']) {
                        $userBooks[] = $borrowedBooksDetails[0];
                    }
                }
                if (empty($userBooks)) {
                    echo '<script> alert("No tienes libros prestados!") </script>';
                }
            }
        }
        include __DIR__ . '/../../app/plantillas/return.inc';
    }

    public function askForBooks() //función para pedir los libros deseados. 
    {
        //instanciamos el checker
        $checker = new FileToArrayToFile();

        $library = $checker->getArrayFromFile(LIBROS_FILE);
        $borrowedBooks = $checker->getArrayFromFile(LIBROS_PRESTADOS_FILE);

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

                    //Cambiar estado en librería.
                    foreach ($booksForAsk as $code) {
                        //Verifica que exista ese código en el inventario
                        if (isset($library[$code]) && $library[$code]['prestado'] == 0) {
                            $library[$code]['prestado'] = 1;
                            var_dump("MODIFICADO ESTADO");
                            $borrowedBooks[] = [$code, $_SESSION['usuario']];
                        }
                    }
                    //guarda y actualiza el fichero de libros prestados 
                    $checker->saveFileWithArray(LIBROS_PRESTADOS_FILE, $borrowedBooks);
                    //guarda y actualiza el fichero de existencias de libros 
                    $checker->saveFileWithArray(LIBROS_FILE, $library);
                } else {
                    echo '<script> alert("No has solicitado libros!!!!") </script>';
                }
            }
        }
        include __DIR__ . '/../../app/plantillas/askForBooks.inc';
    }
}
