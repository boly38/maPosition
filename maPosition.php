<?php
include "externalLib.inc";

include "MaPosition.inc";
include "MesGeokrets.inc";
include "MesMunzees.inc";
include "MesWaymarks.inc";

// comportement général
	$distKm = 5;
	$gk = true;	// activer la recherche de géokrets
	$mz = true;	// activer la recherche de munzees
	$wm = true;	// activer la recherche de waymarks

// geokrets par rapport à une position et une distance en km
	function gk($mp, $distKm) {
	  $mgk = new MesGeokrets();
	  if ($mp != null) {
		  $mgk->getGKNear($mp, $distKm);
	  }
	  $mgk->getGKNear(MaPosition::getGrenoble(), $distKm);
	}

	function mz($mp, $distKm) {
	  $mmz= new MesMunzees();
	  $mmz->getMzNear(MaPosition::getGrenoble(), $distKm);
	}

	function wm($mp, $distKm) {
	  $mwm= new MesWaymarks();
	  $mwm->getWmNear(MaPosition::getGrenoble(), $distKm);
	}

try {
	if (isset($argv[1])) {
		$distKm = $argv[1];
	}
    // position pays/ville/lat/lon par rapport à une ip
	$ip = ""; // php execution server ip (if public)
	// $ip = "8.8.8.8"; // google DNS @ Mountain View
	$mp = new MaPosition($ip);
	$mp->locateMyIP();
	if (!$mp->isLocated()) {
		$mp = null;
	}
	if ($gk) { gk($mp, $distKm); }
	if ($mz) { mz($mp, $distKm); }
	if ($wm) { wm($mp, $distKm); }

} catch (Exception $e) {
    echo ' XXX Exception : ',  $e->getMessage(), "\n";
		echo ' Utilisation: ',  $argv[0], " <distanceKm>\n";
}
?>
