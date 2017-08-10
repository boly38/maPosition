# maPosition

## Objectif du projet
Présenter sur une unique carte les points d'intérêts de différents services/jeux.
Pour le démarrage, le projet est en PHP et utilisable depuis une console linux, mais à terme il est envisagé d'en faire une page web..

## Pré-requis
* soit un apache
* soit un bash avec GIT + PHP

Exemple avec un bash ubuntu
* `apt get install git php`

## Comment exécuter le projet ?
* `git clone`

PHP:

* `cd php && php maPosition.php`

Des fonctions peuvent être activées via l'environnement (utiliser `setEnv.sh`):
* `cp setEnv.sh setEnv.private.sh`
* `vi setEnv.private.sh`
* `. setEnv.private.sh`

Web:
* service le dossier web/ par apache
* rendrez-vous sur index.html (en https si vous ne voulez pas que ggchrome bloque la localisation)


## Fonctions
* détermine une position via l'IP (php) ou via le browser (web)

depuis une position et une distance en KM:
* lister les Géokrets (merci à [geokretymap](https://geokretymap.org/))
* lister les Waymarks (merci à [waymarking](https://waymarking.com) et à [waymarking-lib (Ruby)](https://github.com/pkubiak/waymarking-lib/blob/master/lib/waymarking/search_query.rb) )
* lister les Munzees (merci à [labs-munzee](https://github.com/CartoDB/labs-munzee/))

## Possibles évolutions
* ajouter des caches
* ajouter d'autres POI
* ajouter un fond de carte
