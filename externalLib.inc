<?php
######################################## 
## SOURCE https://stackoverflow.com/questions/238260/how-to-calculate-the-bounding-box-for-a-given-lat-lng-location
######################################## 
# objet: obtenir une boîte de coordonnées par rapport à une position et une distance
######################################## 
#
# Semi-axes of WGS-84 geoidal reference
$WGS84_a = 6378137.0;  # Major semiaxis [m]
$WGS84_b = 6356752.3;  # Minor semiaxis [m]

# Earth radius at a given latitude, according to the WGS-84 ellipsoid [m]
function WGS84EarthRadius($lat)
{
    global $WGS84_a, $WGS84_b;

    $an = $WGS84_a * $WGS84_a * cos($lat);
    $bn = $WGS84_b * $WGS84_b * sin($lat);
    $ad = $WGS84_a * cos($lat);
    $bd = $WGS84_b * sin($lat);

    return sqrt(($an*$an + $bn*$bn)/($ad*$ad + $bd*$bd));
}

# Bounding box surrounding the point at given coordinates,
# assuming local approximation of Earth surface as a sphere
# of radius given by WGS84
function boundingBox($latitudeInDegrees, $longitudeInDegrees, $halfSideInKm)
{
    $lat = deg2rad($latitudeInDegrees);
    $lon = deg2rad($longitudeInDegrees);
    $halfSide = 1000 * $halfSideInKm;

    # Radius of Earth at given latitude
    $radius = WGS84EarthRadius($lat);
    # Radius of the parallel at given latitude
    $pradius = $radius*cos($lat);

    $latMin = $lat - $halfSide / $radius;
    $latMax = $lat + $halfSide / $radius;
    $lonMin = $lon - $halfSide / $pradius;
    $lonMax = $lon + $halfSide / $pradius;

    return array(rad2deg($latMin), rad2deg($lonMin), rad2deg($latMax), rad2deg($lonMax));
}