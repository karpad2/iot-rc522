<?php

$string = file_get_contents("test.json");
$array=json_decode($string,true);
//var_dump($array);
if(isset($_GET["set"]) && isset($_GET["val"]))
{
    header("Content-Type", "application/x-www-form-urlencoded");
  if(is_numeric(intval($_GET["set"])) &&  is_numeric(intval($_GET["set"]))) $array[$_GET["set"]]["val"]=$_GET["val"];
    else die($string);
$string=json_encode($array);
$f=fopen('test.json','w');
fwrite($f,$string);
fclose($f);
die("k");
}
elseif(isset($_GET["status"]))
{header('Content-type: text/plain; charset=utf-8');
    $stat=true;

    foreach($array as $item) $stat=($item["val"]==1&&$stat);
    
    if($stat) die("unlock");
    else die("locked");
}
else 
{header('Content-type: text/plain; charset=utf-8');
    foreach($array as $item) {
      //  var_dump($item);
        echo "Switch: {$item["name"]}, val: {$item["val"]}\n";}
    
}
