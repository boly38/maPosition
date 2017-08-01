<?php

class MaPosition {
   var $dev = true;

   var $country;
   var $city;
   var $lon;
   var $lat;
   var $ip;
   var $locTime;

   function MaPosition($ip = "") {
	  if ($ip != "") {
		// ip address to check: not mandatory, will use php server ip if null
		$this->ip = $ip;
	  }
   }
   
   function locateMe() {
		$this->locateMeIpApi(); // moins fiable ?
		if ($this->isLocated()) {
			$this->hello();
			return;
		}
		$this->locateMeFreegeoip();
		if ($this->isLocated()) {
			$this->hello();
			return;
		}
		$this->locateMeGoPlugin();
		if ($this->isLocated()) {
			$this->hello();
			return;
		}
   }
   
   function hello() {
	  echo "Hey $this->ip from " . $this->country . ", " . $this->city . " [$this->lat,$this->lon]! ($this->locTime ms)\n";
   }
   
   function _toMs($end,$start) {
     return number_format($end-$start, 3)*1000;
   }
   
   function isLocated() {
		return ($this->city != "") && ($this->lat != "") && ($this->lon != "");
   }
   
   function locateMeFreegeoip() {
     $timestart=microtime(true);
     $target = 'https://freegeoip.net/json/' . $this->ip;
	 echo "ask to $target\n";
	 $json = file_get_contents($target);
	 $obj = json_decode($json);
	 $this->country = $obj->country_name;
	 $this->city = $obj->city;
	 $this->lat = $obj->latitude;
	 $this->lon = $obj->longitude;
	 $this->ip = $obj->ip;
	 // var_dump($obj);
	 $timeend=microtime(true);
	 $this->locTime=$this->_toMs($timeend,$timestart);
   }
   
   function locateMeIpApi() {
     $timestart=microtime(true);
     $target = 'http://ip-api.com/php/' . $this->ip;
	 echo "ask to $target\n";
	 $query = @unserialize (file_get_contents($target));
	 if ($query && $query['status'] == 'success') {
		// echo 'Hey user from ' . $query['country'] . ', ' . $query['city'] . '!';
		$this->country = $query["country"];
		$this->city = $query["city"];
		$this->lat = $query["lat"];
		$this->lon = $query["lon"];
		$this->ip = $query["query"];
	 }
	 $timeend=microtime(true);
	 $this->locTime=$this->_toMs($timeend,$timestart);
	 if ($this->dev && $this->city == "") {
		var_dump($query);
	 }
   }
   
   function locateMeGoPlugin() {
     $timestart=microtime(true);
	 $target = 'http://www.geoplugin.net/php.gp';
	 if (isset($this->ip)) {
		$target = "http://www.geoplugin.net/php.gp?ip=" . $this->ip;
	 }
	 echo "ask to $target\n";
	 $geo = unserialize(file_get_contents($target));
	 // var_dump($geo);
	 $this->country = $geo["geoplugin_countryName"];
	 $this->city = $geo["geoplugin_city"];
	 $this->lat = $geo["geoplugin_latitude"];
	 $this->lon = $geo["geoplugin_longitude"];
	 $this->ip = $geo["geoplugin_request"];
	 $timeend=microtime(true);
	 $this->locTime=$this->_toMs($timeend,$timestart);
   }
}