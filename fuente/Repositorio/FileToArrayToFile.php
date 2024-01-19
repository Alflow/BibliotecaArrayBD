<?php


// ....

class FileToArrayToFile
{

    // Método para obtener los datos
    public function getArrayFromFile(string $archivo): array
    {
        //si no existe devuelve una excepción. (Manejaremos esa excepción en el try catch del controler)
        if (!file_exists($archivo)) {
            throw new Exception('No ha sido posible extraer el archivo' . $archivo);
        }

        //devolvemos el la información interna en forma de array
        $cadena = file_get_contents($archivo);
        $array = unserialize($cadena);
        return $array;
        // otra manera sería....return unserialize(file_get_contents($archivo));
    }
    public function saveFileWithArray(string $archivo, array $array)
    {
        if (file_put_contents($archivo, serialize($array)) == false) { //comprueba que si no fue posible, pero lo hace si no hay error
            throw new Exception('No fue posible guardar el array');
        }
    }
}
