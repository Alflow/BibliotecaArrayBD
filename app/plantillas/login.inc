<?php ob_start(); ?>
<!-- formulario de login -->
<form method="post">
    <label>Nombre de usuario
        <input type="text" placeholder="Inserte nombre de usuario" name="credentials[userName]">
    </label> <br>
    <label>Contraseña:
        <input type="password" placeholder="Inserte contraseña" name="credentials[password]">
    </label> <br>
    <?php if (isset($errorEmptyData)) {
        echo '<span> No puede dejar campos vacíos</span><br>';
    }
    if (isset($errorLogin)) {
        echo '<span> El usuario o contraseña son incorrectos</span><br>';
    }
    if (isset($errorIncorrectEmail)) {
        echo '<span> El corro electrónico introducido no es válido</span><br>';
    }
    ?>
    <input type="submit" name="ok" value="ENTRAR">
</form>

<?php $contenido = ob_get_clean() ?>

<?php include 'base.inc' ?>