<?php

require_once __DIR__ . '/../Repositorio/GestionBdRepositorio.php';
require_once __DIR__ . '/../../app/utilidades/sanea.inc';

class AccessController
{
  public function checkLoginForm()
  {
    if (isset($_POST['ok'])) {
      //Recogemos en un array los datos introducidos por el usuario en el formulario de inicio de sesión.
      $inputs = $_POST['credentials'];
      foreach ($inputs as $input) {
        $input = sanea($input);
      }


      if (empty($inputs['userName']) || empty($inputs['password'])) {
        $errorEmptyData = true;
      } else {
        if (!filter_var($inputs['userName'], FILTER_VALIDATE_EMAIL)) {
          $errorIncorrectEmail = true;
        }
      }

      if (!isset($errorEmptyData) && !isset($errorIncorrectEmail)) {
        try {
          require_once __DIR__ . '/../Modelo/AppException.inc';
          require_once __DIR__ . '/../../core/ConexionBd.inc';
          require_once __DIR__ . '/../../fuente/Repositorio/GestionBdRepositorio.php';

          try {
          } catch (\PDOException $ex) {
            throw $ex;
          } catch (Exception $ex) {
            $errorDoNotExists = $ex->getMessage();
          } finally {
            if (isset($snt))
              unset($snt);
            if (isset($con))
              $con = null;
          }
          return [];
        } catch (Exception $ex) {
          // Lanzar una excepción con un mensaje informativo
          throw new Exception("Error procesando el login: ");
        }
      }
    }
    include __DIR__ . '/../../app/plantillas/login.inc';
  }



  public function logOut() //funcion para cerrar sesión. 
  {
    echo '<script> alert("Se cerrará su sesión") </script>';
    // Limpiamos el arreglo de sesión
    $_SESSION = array();
    //retrasa dos segundos el cierre de sesión.
    sleep(2);
    // Destruimos la sesión y redirigimos 
    session_destroy();
    header('Location: index.php');
    exit;
  }
}
