<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);
header('Content-Type: application/json');

$currentDateTime = date('Y-m-d H:i:s');
echo json_encode(['time' => $currentDateTime]);
?>