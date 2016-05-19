<?php

//Variable der angiver hvor databasen kører
$db_server	 = "localhost";

//Database brugernavn
$db_username = "joha2514";

//Database password
$db_password = "P9HPUVM2GU";

//Navnet på databasen
$db_name	 = "joha2514";

//Vi initialiserer en database forbindelse med overstående parametre 
$db_con = mysqli_connect($db_server, $db_username, $db_password, $db_name);
?>