<?php

//Inkluderer php-scriptet "dbconnect.php" der initialiserer en database forbindelse
include("dbconnect.php");

//Vi henter alle bestillinger som ikke er udført endnu
$result = mysqli_query($db_con, 'SELECT * FROM `bestillinger` WHERE `hentet` = 0');

//Vi tager den øverste bestilling først (den med det laveste id)
$first = mysqli_fetch_array($result);
if ($first) {
	//Vi skriver nu værdierne ud for den første bestilling
	echo $first["id"] . ';';
	echo $first["kundenavn"] . ';';
	echo $first["pinocchio"] . ';';
	echo $first["mm"] . ';';
	echo $first["jellybeans"];
} else {
	echo "ingen nye bestillinger.";
}

//Vi lukker for database forbindelsen
mysqli_close($db_con);
?>