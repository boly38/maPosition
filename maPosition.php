<?php
include "externalLib.inc";

include "MaPosition.inc";
include "MesGeokrets.inc";
include "MesMunzees.inc";

try {
  // position pays/ville/lat/lon par rapport à une ip
	$ip = ""; // php execution server ip (if public)
	$ip = "8.8.8.8"; // google DNS @ Mountain View
	$mp = new MaPosition($ip);
	$mp->locateMyIP();
	if (!$mp->isLocated()) {
		$mp = null;
	}

  // geokrets par rapport à une position et une distance en km
  $distKm = 10;
  if (isset($argv[1])) {
  	$distKm = $argv[1];
  }
  $mgk = new MesGeokrets();
  if ($mp != null) {
	  $mgk->getGKNear($mp, $distKm);
  }
  $mgk->getGKNear(MaPosition::getGrenoble(), $distKm);
  
  $mmz= new MesMunzees();
  $mmz->getMzNear(MaPosition::getGrenoble(), $distKm);
  
  
} catch (Exception $e) {
    echo ' XXX Exception : ',  $e->getMessage(), "\n";
		echo ' Usage: ',  $argv[0], " <distanceKm>\n";
}
?>
