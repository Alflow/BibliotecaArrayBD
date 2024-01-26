<?php

namespace App\Respository;

class GestionBdRepositorio
{
    use MiniBiblioteca\Core;

    public function getLibros(): array
    { {
            $sql = 'SELECT codigo, titulo, autor, genero, prestado
                    FROM libro ';

            require_once __DIR__ . '/../../core/ConexionBd.inc';
            try {
                $con = (new ConexionBd())->getConexion();
                $snt = $con->prepare($sql);
                $snt->execute();

                //almacenamos en templibrary los datos de la tabla para poder modificar su disposición a la original de ficheros
                $tempLibrary = $snt->fetchAll(\PDO::FETCH_ASSOC);
                // var_dump('TEST TEMP LIBRARY');
                // var_dump($tempLibrary);

                $finalLibrary = [];
                foreach ($tempLibrary as $book => $details) {
                    $finalLibrary[$details['codigo']] = ['titulo' => $details['titulo'], 'autor' => $details['autor'], 'genero' => $details['genero'], 'prestado' => $details['prestado']];
                }
                // var_dump('TEST FINAL LIBRARY');
                // var_dump($finalLibrary);

                return $finalLibrary;



                // OTRA MANERA
                // $library = [];
                // while ($fila = $snt->fetch(pdo::FETCH_ASSOC)) {
                //     $library[$fila['codigo']['titulo']] = $fila['titulo'];
                //     $library[$fila['codigo']['autor']] = $fila['autor'];
                //     $library[$fila['codigo']['genero']] = $fila['genero'];
                //     $library[$fila['codigo']['prestado']] = $fila['prestado'];
                // }


            } catch (\PDOException $ex) {
                throw $ex;
            } finally {
                if (isset($snt))
                    unset($snt);
                if (isset($con))
                    $con = null;
            }
            return [];
        }
    }


    public function getSocios(): array
    { {
            $sql = 'SELECT eCorreo, pwd
                    FROM socio ';

            require_once __DIR__ . '/../../core/ConexionBd.inc';
            try {
                $con = (new ConexionBd())->getConexion();
                $snt = $con->prepare($sql);
                $snt->execute();
                $users = [];

                // preparamos el array con la estructura original de socios
                while ($fila = $snt->fetch(\PDO::FETCH_ASSOC)) {
                    $users[] = ['eCorreo' => $fila['eCorreo'], 'pwd' => $fila['pwd']];
                }
                return $users;
            } catch (\PDOException $ex) {
                throw $ex;
            } finally {
                if (isset($snt))
                    unset($snt);
                if (isset($con))
                    $con = null;
            }
            return [];
        }
    }

    public function getLibrosPrestados(): array
    {
        $sql = 'SELECT codigo, eCorreo FROM libroPrestado';
        require_once __DIR__ . '/../../core/ConexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $borrowedBooks = [];

            // preparamos el array con la estructura original de socios
            while ($fila = $snt->fetch(pdo::FETCH_ASSOC)) {
                $borrowedBooks[] = [$fila['codigo'], $fila['eCorreo']];
            }

            return $borrowedBooks;
        } catch (\PDOException $ex) {
            throw $ex;
        } finally {
            if (isset($snt))
                unset($snt);
            if (isset($con))
                $con = null;
        }
        return [];
    }


    public function devolverLibrosPrestados(array $librosParaDevolver)
    {
        require_once __DIR__ . '/../../core/ConexionBd.inc';

        // preparo sentencia de modificación en LIBROS.
        $sql_1 = 'UPDATE libro SET prestado = 0 WHERE codigo = :codigo';

        // preparo sentencia de modificación en LIBROS PRESTADOS (ELIMINACIÓN).
        $sql_2 = 'DELETE FROM libroPrestado WHERE codigo = :codigo';

        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction(); // Iniciar una transacción
            $snt = $con->prepare($sql_1); // Preparar la sentencia

            foreach ($librosParaDevolver as $codigo) {
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute();
            }

            //Pido a snt que prepare la segunda Query
            $snt = $con->prepare($sql_2);
            foreach ($librosParaDevolver as $codigo) {
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute();
            }

            $con->commit(); // Confirmar la transacción
        } catch (\PDOException $ex) {
            if (isset($con)) {
                $con->rollback(); // Revertir la transacción en caso de error
            }
            throw $ex;
        } finally {
            if (isset($snt)) {
                $snt = null; // Cierra el statement
            }
            if (isset($con)) {
                $con = null; // Cierra la conexión
            }
        }
    }

    public function pedirLibrosPrestados(array $librosParaPedir)
    {
        require_once __DIR__ . '/../../core/ConexionBd.inc';

        // preparo sentencia de modificación en LIBROS.
        $sql_1 = 'UPDATE libro SET prestado = 1 WHERE codigo = :codigo';

        // preparo sentencia de modificación en LIBROS PRESTADOS (ELIMINACIÓN).
        $sql_2 = 'INSERT INTO libroPrestado (codigo, eCorreo) VALUES (:codigo ,:eCorreo)';

        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction(); // Iniciar una transacción
            $snt = $con->prepare($sql_1); // Preparar la sentencia

            foreach ($librosParaPedir as $codigo) {
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute();
            }

            //Pido a snt que prepare la segunda Query
            $snt = $con->prepare($sql_2);
            foreach ($librosParaPedir as $codigo) {
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $correo = $_SESSION['usuario'];
                $snt->bindParam(':eCorreo', $correo, PDO::PARAM_STR,);
                $snt->execute();
            }

            $con->commit(); // Confirmar la transacción


        } catch (\PDOException $ex) {
            if (isset($con)) {
                $con->rollback(); // Revertir la transacción en caso de error
            }
            throw $ex;
        } finally {
            if (isset($snt)) {
                $snt = null; // Cierra el statement
            }
            if (isset($con)) {
                $con = null; // Cierra la conexión
            }
        }
    }
}

// Tenemos que conseguir devolver leyendo de la base de datos.
