<?php
//index.php
session_start();
error_reporting(E_ALL);


//definimos las constantes de la ubicación de los archivos
define('LIBROS_FILE', __DIR__ . '/fuente/Repositorio/libros.txt');
define('LIBROS_PRESTADOS_FILE', __DIR__ . '/fuente/Repositorio/librosPrestados.txt');
define('SOCIOS_FILE', __DIR__ . '/fuente/Repositorio/socios.txt');


require_once __DIR__ . '/fuente/Controlador/DefaultController.inc'; /*controladores */
require_once __DIR__ . '/fuente/Controlador/AccessController.inc'; /*controladores */
require_once __DIR__ . '/fuente/Controlador/OrderReturnController.inc'; /*controladores */
require_once __DIR__ . '/app/conf/rutas.inc'; /*Ubicación del archivo de rutas*/

// Análisis de la ruta
if (isset($_GET['ctl'])) {
  if (isset($mapeoRutas[$_GET['ctl']])) {

    $ruta = $_GET['ctl'];
  } else {
    header('Status: 404 Not Found');
    echo '<html><body><h1>Error 404: No existe la ruta <i>' .
      $_GET['ctl'] .
      '</i></p></body></html>';
    exit;
  }
} else {
  $ruta = 'inicio';
}

$controlador = $mapeoRutas[$ruta];
// Ejecución del controlador asociado a la ruta

if (method_exists($controlador['controller'], $controlador['action'])) {
  call_user_func(array(new $controlador['controller'], $controlador['action']));
} else {
  header('Status: 404 Not Found');
  echo '<html><body><h1>Error 404: El controlador <i>' .
    $controlador['controller'] .
    '->' . $controlador['action'] .
    '</i> no existe</h1></body></html>';
}
