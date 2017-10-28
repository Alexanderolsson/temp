<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "temp_db";
// Ansluter till databas
$conn = new mysqli($servername, $username, $password, $dbname);
// Kollar ifall den lyckas anslutas
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM tempLog";
$result = $conn->query($sql);
//Loopar enbart om det är mer än 0 rader från sökningen
if ($result->num_rows > 0) {
    //Loopar igenom resultaten från sökningen
    while($row = $result->fetch_assoc()) {
        echo "time: " . $row["datetime"]. " - temp: " . $row["temperature"]."<br>";
    }
} else {
    echo "0 results";
}
$conn->close();
?>
