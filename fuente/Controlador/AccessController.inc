<?php

require_once __DIR__ . '/../Repositorio/FileToArrayToFile.php';
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

          //Instanciamos un FileToArrayToFile
          $baseUsuarios = new FileToArrayToFile;

          //Extraemos el array de usuarios del archivo. 
          $listadoUsuarios = $baseUsuarios->getArrayFromFile(SOCIOS_FILE);

          //Recorremos el array de usuarios de la "base de datos" 
          foreach ($listadoUsuarios as $user) {
            if ($user['eCorreo'] == $inputs['userName']) {
              // CORREO COINCIDE
              if (password_verify($inputs['password'], $user['pwd'])) {
                // PASS COINCIDE
                echo '<script> alert("BIENVENIDO!")</script>';
                $_SESSION['usuario'] = $user['eCorreo']; // Guarda el correo del usuario en la sesión
                header('Location: index.php');
                exit();
              } else {
                //Preparación de variable error en login
                $errorLogin = true;
              }
              break;
            } else {
              $errorLogin = true;
            }
          }
        } catch (Exception $ex) {
          // Lanzar una excepción con un mensaje informativo
          throw new Exception("Error procesando el login: " . $ex->getMessage());
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
