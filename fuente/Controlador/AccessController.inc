<?php

require_once __DIR__ . '/../../fuente/Repositorio/GestionBdRepositorio.php';
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

          $listadoUsuarios = (new GestionBdRepositorio())->getSocioByECorreo($inputs['userName']);

          if (password_verify($inputs['password'], $listadoUsuarios['pwd'])) {
            // PASS COINCIDE
            echo '<script> alert("BIENVENIDO!")</script>';
            $_SESSION['usuario'] = $listadoUsuarios['eCorreo']; // Guarda el correo del usuario en la sesión
            header('Location: index.php');
            exit();
          }
          //Preparación de variable error en login
          $errorLogin = true;
        } catch (PDOException $ex) {
          $errorNoExiste = $ex->getMessage();
        } catch (Exception $ex) {
          if ($ex->getCode() === 100) {
            $errorNoExiste = $ex->getMessage();
          }
        }
      }
    }

    include __DIR__ . '/../../app/plantillas/login.inc';
  }


  //funcion para cerrar sesión. 
  public function logOut()
  {
    //Método para desLogar al usuario
    echo '<script> alert("Se cerrará su sesión") </script>';

    // Limpiamos el arreglo de sesión de usuario
    unset($_SESSION['usuario']);
    // Destruimos la sesión y redirigimos 
    session_destroy();
    header('Location: index.php');
    exit;
  }
}
