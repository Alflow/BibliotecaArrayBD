<?php ob_start(); ?>
<?php
// var_dump($library);
?>
<h1>Solicitud de libros </h1>

<form method="post">
    <legend>Selecciona los libros que quieres pedir:</legend>
    <table>
        <tr>
            <th>Título</th>
            <th>Autor</th>
            <th>Seleccionar</th>
        </tr>
        <?php if (isset($_POST['okAsk'])) : ?>
            <?php foreach ($library as $code => $bookData) : ?>
                <?php if ($bookData['prestado'] == 0) : ?>
                    <tr>
                        <td><?= htmlspecialchars($bookData['título']) ?></td>
                        <td><?= htmlspecialchars($bookData['autor']) ?></td>
                        <td><input type="checkbox" name="booksForAsk[]" value="<?= htmlspecialchars($code) ?>"></td>
                    </tr>
                <?php endif; ?>
            <?php endforeach; ?>
        <?php else : ?>
            <?php foreach ($library as $code => $bookData) : ?>
                <?php if ($bookData['prestado'] == 0) : ?>
                    <tr>
                        <td><?= htmlspecialchars($bookData['título']) ?></td>
                        <td><?= htmlspecialchars($bookData['autor']) ?></td>
                        <td><input type="checkbox" name="booksForAsk[]" value="<?= htmlspecialchars($code) ?>"></td>
                    </tr>
                <?php endif; ?>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
    <input type="submit" name="okAsk" value="Pedir libros">
</form>


<?php $contenido = ob_get_clean() ?>

<?php include 'base.inc' ?>