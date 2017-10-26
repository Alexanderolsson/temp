<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "temp_db";
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM tempLog";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "time: " . $row["datetime"]. " - temp: " . $row["temperature"]."<br>";
    }
} else {
    echo "0 results";
}
$conn->close();
?>
