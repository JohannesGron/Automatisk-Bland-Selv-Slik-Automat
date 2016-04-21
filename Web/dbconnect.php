<?php
$db_server	 = "localhost";
$db_username = "root";
$db_password = "";
$db_name	 = "slikautomat";

$db_con = mysqli_connect($db_server, $db_username, $db_password, $db_name);
if (!$db_con) {
	echo "fejl i at forbinde til database" . PHP_EOL;
	echo "fejlkode: " . mysqli_connect_errno() . PHP_EOL;
	echo "fejlbesked: " . mysqli_connect_error() . PHP_EOL;
	exit;
}
?>