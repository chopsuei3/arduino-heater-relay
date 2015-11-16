<?php

header("Refresh: 15");
exec("sudo python /home/pi/read-state.py", $current);
exec("sudo python /home/pi/read-temp.py", $temp);

if (isset($_POST["rcmd"]))
{
  $rcmd = $_POST["rcmd"];
  switch($rcmd)
  {
case "On":
  exec("sudo python /home/pi/read-state.py", $current);
  if($current[0]=="OFF"){
  exec("sudo python /home/pi/write-state.py");}
  header("Refresh:0");
  break;
case "Off":
  exec("sudo python /home/pi/read-state.py", $current);
  if($current[0]=="ON"){
  exec("sudo python /home/pi/write-state.py");}
  header("Refresh:0");
  break;
case "Refresh":
  header("Refresh:0");
  break;
default:
  die('Crap, something went wrong. The page just puked.');
}
}


?>
<html>
<body>

<center><h1>Heater Control</h1></center>

<form method="post" action="heater.php">
<input type="submit" value="On" name="rcmd">
<input type="submit" value="Off" name="rcmd">
<input type="submit" value="Refresh" name="rcmd">
</form>
<h3>Current Date Time = <?php echo date("F j, Y, g:i:s a"); ?></h3>
<h3>Current State = <?php echo $current[0]; ?></h3>
<h3>Temperature (deg F) = <?php echo $temp[0]; ?></h3>
</body>
</html>