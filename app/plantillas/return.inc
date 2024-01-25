<?php ob_start(); ?>

<h1>Devolución de Libros</h1>
<?php
if (empty($borrowedBooks)) {
    echo '<h2> No tienes ningún libro prestado! </h2>';
} else {
    echo '<h2>Libros prestados de ' . $_SESSION['usuario'] . '</h2>';
}
?>
<!-- Formulario con checkbox que muestra los libros que el usuario tiene prestados -->
<form method="post">
    <legend>Selecciona los libros que quieres devolver:</legend>
    <table>
        <tr>
            <th>Título</th>
            <th>Autor</th>
            <th>Seleccionar</th>
        </tr>
        <?php
        // var_dump($borrowedBooks);

        ?>
        <?php if (isset($_POST['ok'])) : ?>
            <?php foreach ($borrowedBooks as $code) : ?>
                <tr>
                    <td><?= htmlspecialchars($code['titulo']) ?></td>
                    <td><?= htmlspecialchars($code['autor']) ?></td>
                    <td>
                        <input type="checkbox" name="booksForReturn[]" value="<?= htmlspecialchars($code['codigo']) ?>">
                    </td>
                </tr>
            <?php endforeach; ?>
        <?php else : ?>
            <?php foreach ($borrowedBooks as $code) : ?>
                <tr>
                    <td><?= htmlspecialchars($code['titulo']) ?></td>
                    <td><?= htmlspecialchars($code['autor']) ?></td>
                    <td>
                        <input type="checkbox" name="booksForReturn[]" value="<?= htmlspecialchars($code['codigo']) ?>">
                    </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
    <input type="submit" name="okReturn" value="Devolver libros seleccionados">
</form>


<?php $contenido = ob_get_clean() ?>

<?php include 'base.inc' ?>