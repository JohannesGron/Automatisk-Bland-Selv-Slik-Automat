<?php

//Inkluderer php-scriptet "dbconnect.php" der initialiserer en database forbindelse
include("dbconnect.php");

//Vi henter de værdier som brugeren ønsker at bestille og laver stk. om til gram
$mm = 2 * $_POST["mm"];
$jb = 2 * $_POST["jb"];
$pk = 2 * $_POST["pk"];

//Vi indsætter værdierne samt navn på brugeren i databasen
mysqli_query($db_con, "INSERT INTO `joha2514`.`bestillinger` (`kundenavn`, `pinocchio`, `mm`, `jellybeans`) VALUES ('" . $_POST["name"] . "', '" . $pk . "', '" . $mm . "', '" . $jb . "');");

//Vi lukker for database forbindelsen
mysqli_close($db_con);

//Vi sender brugeren tilbage til forsiden med "#done" i urlen for at fortælle forsiden at den skal vise en besked
header("LOCATION: http://webhotel.herningsholm.dk/joha2514/slikautomat/#done");
?>