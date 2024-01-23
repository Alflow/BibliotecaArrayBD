<?php ob_start(); ?>

<h1>Devolución de Libros</h1>
<?php
if (empty($userBooks)) {
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
        <?php if (isset($_POST['ok'])) : ?>
            <?php foreach ($borrowedBooks as $code) : ?>
                <?php if ($code[1] == $_SESSION['usuario']) : ?>
                    <?php foreach ($library as $book => $bookData) : ?>
                        <?php if ($code[0] === $book) : ?>
                            <tr>
                                <td><?= htmlspecialchars($bookData['titulo']) ?></td>
                                <td><?= htmlspecialchars($bookData['autor']) ?></td>
                                <td><input type="checkbox" name="booksForReturn[]" value="<?= htmlspecialchars($code[0]) ?>"></td>
                            </tr>
                        <?php endif; ?>
                    <?php endforeach; ?>
                <?php endif; ?>
            <?php endforeach; ?>
        <?php else : ?>
            <?php foreach ($borrowedBooks as $code) : ?>
                <?php if ($code[1] == $_SESSION['usuario']) : ?>
                    <?php foreach ($library as $book => $bookData) : ?>
                        <?php if ($code[0] === $book) : ?>
                            <tr>
                                <td><?= htmlspecialchars($bookData['titulo']) ?></td>
                                <td><?= htmlspecialchars($bookData['autor']) ?></td>
                                <td><input type="checkbox" name="booksForReturn[]" value="<?= htmlspecialchars($code[0]) ?>"></td>
                            </tr>
                        <?php endif; ?>
                    <?php endforeach; ?>
                <?php endif; ?>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
    <input type="submit" name="okReturn" value="Devolver libros seleccionados">
</form>


<?php $contenido = ob_get_clean() ?>

<?php include 'base.inc' ?>