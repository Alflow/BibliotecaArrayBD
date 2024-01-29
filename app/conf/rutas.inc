<?php
$mapeoRutas =
  [
    'inicio' => ['controller' => 'DefaultController', 'action' => 'inicio'],
    'login' => ['controller' => 'AccessController', 'action' => 'checkLoginForm'],
    'logOut' => ['controller' => 'AccessController', 'action' => 'logOut'],
    'returnUserBooks' => ['controller' => 'OrderReturnController', 'action' => 'returnUserBooks'],
    'askForBooks' => ['controller' => 'OrderReturnController', 'action' => 'askForBooks'],
    'showBookDetails' => ['controller' => 'DefaultController', 'action' => 'showBookDetails'],
  ];
