<?php
include("dbconnect.php");

if (!empty($_GET["id"])) {
	$bestilling = $_GET["id"];
	if (!mysqli_query($db_con, 'UPDATE `bestillinger` SET `hentet` = 1 WHERE `id` = ' . $bestilling)) {
		echo "bestilling ikke opdateret";
	}
}

mysqli_close($db_con);
?>