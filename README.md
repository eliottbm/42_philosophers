# 🍴​ Philosophers

![42_philosophers](https://github.com/user-attachments/assets/01f2a442-d021-4255-a586-db52b6af449f)

## Présentation
Philosophers est un projet de l’École 42, dont l’objectif est d’implémenter une simulation inspirée du problème des philosophes, en utilisant des threads et des mécanismes de synchronisation.
Il met l’accent sur la gestion concurrente de processus légers, l’utilisation de mutex pour éviter les conditions de compétition, et la maîtrise des problématiques liées au parallélisme.

## Utilisation
```
make
# compile l’exécutable 'philo'

./philo 5 800 200 200 7
# lance la simulation avec 5 philosophes,
# un temps de mort de 800 ms,
# un temps de repas de 200 ms,
# un temps de sommeil de 200 ms,
# une condition d’arrêt après 7 repas par philosophe
```
