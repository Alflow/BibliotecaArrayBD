<?php

class GestionBdRepositorio
{
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
                $tempLibrary = $snt->fetchAll(PDO::FETCH_ASSOC);
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
}


// Tenemos que conseguir devolver leyendo de la base de datos.
