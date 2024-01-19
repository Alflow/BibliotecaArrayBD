<?php ob_start(); ?>
<!-- Tabla que muestra las existencias de la biblioteca -->
<div class="tabla">
  <table>
    <thead>
      <tr>
        <th>Título</th>
        <th>Autor</th>
        <th>Género</th>
        <th>Estado</th>
      </tr>
    </thead>
    <tbody>
    <?php
      foreach ($library as $codigo => ['título' => $titulo, 'autor' => $autor, 'género' => $genero, 'prestado' => $disponible]){
        echo ($disponible==0? '<tr><td><a href="#">'.$titulo.'</a></td>': '<td>'.$titulo.'</td>');
        echo '<td>'. $autor . '</td><td>'. $genero . '</td><td>'. ($disponible==1? 'prestado':'Disponible') . '</td></tr>';
      } 
    ?>
    </tbody>
  </table> 
</div>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.inc' ?>