<?php

class MaCache {
   var $dev = true;
   
   function getCacheNear($lat, $lon) {
     $distKm = 4;
	 echo "get cache $distKm km near $lat, $lon ...\n";

   }
}