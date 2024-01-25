<?php

use FTP\Connection;

class GestionBdRepositorio
{
    public static function obtenerConexion()
    {
        require_once __DIR__ . '/../../core/ConexionBd.inc';
        return (new ConexionBd())->getConexion();
    }

    public function getLibros(): array
    {
        $sql = 'SELECT codigo, titulo, autor, genero, prestado
                    FROM libro ';


        try {
            $con = GestionBdRepositorio::obtenerConexion();
            $snt = $con->prepare($sql);
            $snt->execute();

            //almacenamos en templibrary los datos de la tabla para poder modificar su disposición a la original de ficheros
            $tempLibrary = $snt->fetchAll(PDO::FETCH_ASSOC);

            $finalLibrary = [];
            foreach ($tempLibrary as $book => $details) {
                $finalLibrary[$details['codigo']] = ['titulo' => $details['titulo'], 'autor' => $details['autor'], 'genero' => $details['genero'], 'prestado' => $details['prestado']];
            }

            return $finalLibrary;
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


    public function getSocios(): array
    {
        $sql = 'SELECT eCorreo, pwd
                    FROM socio ';

        require_once __DIR__ . '/../../core/ConexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $users = [];

            // preparamos el array con la estructura original de socios
            while ($fila = $snt->fetch(pdo::FETCH_ASSOC)) {
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

            // Iniciar una transacción
            $con->beginTransaction();
            foreach ($librosParaDevolver as $codigo) {
                $snt = $con->prepare($sql_1); //Preparo la segunda sentencia

                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute(); //ejecuto

                $snt = $con->prepare($sql_2); //Preparo la segunda sentencia
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute(); //ejecuto
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

            foreach ($librosParaPedir as $codigo) {
                $snt = $con->prepare($sql_1); // Preparar la sentencia
                $snt->bindParam(':codigo', $codigo, PDO::PARAM_STR);
                $snt->execute();
                $snt = $con->prepare($sql_2);
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





    public function getSocioByEcorreo(string $eCorreo): array
    {
        $sql = 'SELECT idSocio, eCorreo, pwd FROM socio WHERE eCorreo = :eCorreo';
        require_once __DIR__ . '/../../core/ConexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindParam(':eCorreo', $eCorreo);
            $snt->execute();
            $fila = $snt->fetch(PDO::FETCH_ASSOC);
            if ($fila === false) {
                throw new Exception('No hay socios con ese eCorreo', 100);
            } else {
                return $fila;
            }
        } catch (\PDOException $ex) {
            throw $ex;
        }
    }

    // Función que devuelve un array con los libros prestados que tiene el usuario.
    public function getLibrosPrestadosPorSocio(string $eCorreo): array
    {
        $sql = 'SELECT libro.codigo, eCorreo, titulo, autor FROM libroPrestado LEFT JOIN libro on (libro.codigo = libroPrestado.codigo) WHERE eCorreo = :eCorreo';
        require_once __DIR__ . '/../../core/ConexionBd.inc';

        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindParam(':eCorreo', $eCorreo);
            $snt->execute();
            $librosPrestados = [];
            $librosPrestados = $snt->fetchAll(PDO::FETCH_ASSOC);
            if ($librosPrestados === false) {
                throw new Exception('No hay libros prestados de este usuario', 100);
            } else {
                return $librosPrestados;
            }
        } catch (\PDOException $ex) {
            throw $ex;
        }
    }
}

// Tenemos que conseguir devolver leyendo de la base de datos.
