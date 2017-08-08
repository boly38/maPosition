<?php
class MesMunzees {
   var $dev = true;

   var $apiUser = null;
   var $apiToken = null;

   function MesMunzees() {
	  $this->apiUser  = getenv("MUNZEE_USER");
	  $this->apiToken = getenv("MUNZEE_TOKEN");
   }

   function isAvailable() {
      return ($this->apiUser != null && $this->apiToken != null);
   }

   function getMzNear($position, $distKm) {
     if (!$this->isAvailable()) {
		echo "Munzee is not available for you, please set MUNZEE_USER and MUNZEE_TOKEN\n";
		return;
	 }
     if ($distKm < 1 || $distKm > 50) {
       throw new Exception("la distance doit �tre comprise entre 1 et 50 km");
     }
     $lat = $position->lat;
     $lon = $position->lon;
     $city = $position->city;

     echo "Calcul d'une zone de $distKm km autour de $lat, $lon ($city)...\n";
     $box = boundingBox($lat, $lon, $distKm);
     // var_dump($box);
     $brLat = $box[0];
     $brLon = $box[1];
     $tlLat = $box[2];
     $tlLon = $box[3];
	 $apiUser = $this->apiUser;
	 $apiToken = $this->apiToken;

     $target = "https://api.munzee.com/map/cartodb?username=$apiUser&mhq_token=$apiToken&longitude1=$tlLon&latitude1=$brLat&longitude2=$brLon&latitude2=$tlLat";
     // echo "appel de $target\n";
     $json = file_get_contents($target);
     $obj = json_decode($json);
     $mzCount = count($obj->data);
     echo "$mzCount munzees\n";
     foreach ($obj->data as &$mz) {
       $mzId = $mz->munzee_id;
       echo " * munzee #$mzId\n";
     }
     // var_dump($obj);
   }
}
