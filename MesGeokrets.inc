<?php
class MesGeokrets {
   var $dev = true;

   function getGKNear($position, $distKm) {
     if ($distKm < 1 || $distKm > 50) {
       throw new Exception("la distance doit être comprise entre 1 et 50 km");
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

     $target = "https://api.geokretymap.org/geojson?latTL=$tlLat&lonTL=$tlLon&latBR=$brLat&lonBR=$brLon&limit=500&daysFrom=0&daysTo=-1";
     // echo "ask to $target\n";
     $json = file_get_contents($target);
     $obj = json_decode($json);
     $gkCount = count($obj->features);
     echo "$gkCount geokrets\n";
     foreach ($obj->features as &$gk) {
       $gkId = $gk->properties->gkid;
       $gkAge = $gk->properties->age;
       // https://stackoverflow.com/questions/4423272/how-to-extract-links-and-titles-from-a-html-page
       $gkHtml = $gk->properties->popupContent;
       $dom = new DOMDocument;
       @$dom->loadHTML($gkHtml);
       $links = $dom->getElementsByTagName('a');
       $gkName = $links[0]->nodeValue;
       $pluriel = $gkAge > 1 ? "s":"";

       echo " * géokret $gkName #$gkId depuis $gkAge jour$pluriel\n";
     }
     // var_dump($obj);
   }
}
