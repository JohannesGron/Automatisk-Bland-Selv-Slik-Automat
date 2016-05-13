<?php
include("dbconnect.php");

$result = mysqli_query($db_con, 'SELECT * FROM `bestillinger` WHERE `hentet` = 0');
$first = mysqli_fetch_array($result);
if ($first) {
	echo $first["id"] . ';';
	echo $first["kundenavn"] . ';';
	echo $first["pinocchio"] . ';';
	echo $first["mm"] . ';';
	echo $first["jellybeans"];
} else {
	echo "ingen nye bestillinger.";
}

mysqli_close($db_con);
?>