<?php
include "MaPosition.inc";
include "MaCache.inc";

	$mp = new MaPosition();
	$mp->locateMe();
	if (!$mp->isLocated()) {
		return;
	}
	
	$mc = new MaCache();
	$mc->getCacheNear($mp->lat, $mp->lon);
?>