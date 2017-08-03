# maPosition

## Objectif du projet
Présenter sur une unique carte les points d'intérêts de différents services/jeux.
Pour le démarrage, le projet est en PHP et utilisable depuis une console linux, mais à terme il est envisagé d'en faire une page web..

## Pré-requis
* GIT + PHP
* exemple avec un bash ubuntu
** `apt get install git php`

## Comment exécuter le projet ?
* `git clone`
* `php maPosition.php`

Des fonctions peuvent être activées via l'environnement
* utiliser `setEnv.sh`
** `cp setEnv.sh setEnv.private.sh`
** `vi setEnv.private.sh`
** `. setEnv.private.sh`


## Fonctions
* determine position from IP

from a given position and a distance in km :
* list Geokret (thx https://geokretymap.org/)
* list Munzees (thx https://github.com/CartoDB/labs-munzee/)

## Possibles évolutions
* ajouter des caches
* ajouter [waymarking](https://waymarking.com)
** piste: [waymarking-lib (Ruby)](https://github.com/pkubiak/waymarking-lib/blob/master/lib/waymarking/search_query.rb)
* ajouter d'autres POI
* déplacer les fonctions dans une page web
* ajouter un fond de carte
