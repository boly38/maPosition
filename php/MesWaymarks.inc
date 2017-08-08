<?php
class MesWaymarks {
   var $dev = true;

   function MesWaymarks() {
   }

   function getWMNear($position, $distKm) {
     if ($distKm < 1 || $distKm > 50) {
       throw new Exception("la distance doit être comprise entre 1 et 50 km");
     }
	 
	 $page=1;
	
	 $nbP = $this->getWMNearByPage($position, $distKm, $page++);
	 $total=$nbP;
	 while ($nbP > 0) {
		$total = $total + $nbP;
		$nbP = $this->getWMNearByPage($position, $distKm, $page++);
	 }
	 echo "$total waymarks\n";
	}
 
   function getWMNearByPage($position, $distKm, $page) {
     $lat = $position->lat;
     $lon = $position->lon;
     $city = $position->city;

	 $target = "http://www.waymarking.com/wm/search.aspx?f=1&lat=$lat&lon=$lon&t=6&id=lat:$lat%20lon:$lon&wo=True&r=$distKm&st=2";
	 if ($page > 1) {
		$target = "$target&p=$page";
	 }
     echo "appel de $target (page $page)\n";
     $wmHtml = file_get_contents($target);
     $dom = new DOMDocument;
     @$dom->loadHTML($wmHtml);
     $links = $dom->getElementsByTagName('a');
	 
	 $nbWm = 0;
	 foreach ($links as $lk) {
		 $lkHref = $lk->getAttribute('href');
		 if ($this->isWMLink($lk)) {
		   $wmName = $lk->nodeValue;
		   $nbWm++;
		   echo " * wm $wmName\n";
		 }
     }
	 return $nbWm;
   }
   
   function isWMLink($lk) {
		$lkHref = $lk->getAttribute('href');
		$wmPrefix = "http://www.waymarking.com/waymarks/WM";
		if (substr($lkHref, 0, strlen($wmPrefix)) === $wmPrefix) {
			$wmName = $lk->nodeValue;
			return ($wmName != '');
		}
   }

}