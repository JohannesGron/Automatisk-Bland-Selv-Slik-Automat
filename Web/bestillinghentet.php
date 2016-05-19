<?php

//Inkluderer php-scriptet "dbconnect.php" der initialiserer en database forbindelse
include("dbconnect.php");

//Vi tjekker om der er vedlagt en HTTP GET parameter kaldt "id"
if (!empty($_GET["id"])) {

	//Vi sætter variablen "bestilling lig med værdien af HTTP GET parameteren "id"
	$bestilling = $_GET["id"];

	//Vi opdaterer databasen 
	mysqli_query($db_con, 'UPDATE `bestillinger` SET `hentet` = 1 WHERE `id` = ' . $bestilling)
}

//Vi lukker for database forbindelsen
mysqli_close($db_con);
?>