# Philosophers
The Dining Philosopher Problem

<!--
SUJET
Des philo autour d'une table : Mangent / Dorment / Pensent
Une seule action a la fois.
Les philo doivent manger avec deux fourchettes (une dans chaque main)
Ils ne doivent pas mourrir de faim et doivent tous manger.
Quand un philo mange, il laisse directement ses fourchettes et dors.

Ça stop quand 1 philosopher mort.
Chaque philo a un numero.
Les philo sont assis en cercle dans l'ordre.

Infos a afficher dans le tchat :
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Objectif, moins de 10ms de delta avec le vrai temps.
-->

<!--
FONCTIONS
USLEEP : mets en pause le thread, mais pas le gettimeofday
usleep, en 0.000001
le reste en 0.001, soit un facteur 1000

THREAD
pthread_create // cree le thread
pthread_join // attent poliement que le thread finisse et peut retourner un ptr de valeur exit du de la fonction du thread
pthread_detach // askip ne sert pas

Des Mutex pour temporiser les thread
pthread_mutex_init,
pthread_mutex_lock,
pthread_mutex_destroy, 
pthread_mutex_unlock
-->

<!--
IDEES OPTI
Penser a utiliser un gros buffer par ligne pour economiser de la puissance
-->

<!--
NEW SHORTCUT
ctrl - pour retourner a la derniere modif
ctrl shift - revenir
-->

<!--
WARNINGS
Attention aux variables qui peuvent etre manipules dans plusieurs threads en parallele

NOTIONS
>Rendre les threads Atomic avec les mutex pour qu'ils s'executent proprement sans interferences avec ds variables utiliser en parallele
>L'utilisation de mutex augmente considerablement le temps de compilation, privilegier les thread lorsque les operations ne se chevauchent pas
>L'utilisation de variables volatiles peut eviter au code de faire de mauvais raccourcis lors d'optimisations du compilateur
-->