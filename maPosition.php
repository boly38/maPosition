<?php

include "MaPosition.inc";

include "MaCache.inc";

/*
$query = @unserialize (file_get_contents('http://ip-api.com/php/'));
if ($query && $query['status'] == 'success') {
echo 'Hey user from ' . $query['country'] . ', ' . $query['city'] . '!';
}
foreach ($query as $data) {
    echo $data . "<br>";
}
*/
	$mp = new MaPosition();
	$mp->locateMe();
	if (!$mp->isLocated()) {
		return;
	}
	
	$mc = new MaCache();
	$mc->getCacheNear($mp->lat, $mp->lon);
?>