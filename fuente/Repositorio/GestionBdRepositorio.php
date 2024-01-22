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
                var_dump('TEST FINAL LIBRARY');
                var_dump($finalLibrary);

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
    }


    // public function getSocios(): array
    // {
    // }

    // public function getLibrosPrestados(): array
    // {
    // }
}


// Tenemos que conseguir devolver leyendo de la base de datos.
