<?php
function sanea(string $cadena): string
{
  $cad = $cadena;
  $cad = htmlspecialchars(stripslashes(trim($cadena)));
  return $cad;
}
