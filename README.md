# POV
Ce dépot contient le code du Projet de systèmes embarqués **Persistance Of Vision**, de 3eme année robotique à l'Enseirb-Matmeca, donc l'objectif est d'afficher une horloge sur une barre de leds qui tourne (affichage POV). 

## Comment l'utiliser

### 1 - Dépendances 
Pour faire fonctionner ce projet il faut : 

- être sur microcontroleur Atmega328p, et travailler globalement sur le même hardware que le projet POV de l'enseirb
- avr-gcc 
- Doxygen si vous voulez générer la documentation

### Compilation
Pour compiler tout le projet dans build/ :
```bash
make
```
Pour flasher l'éxecutable produit dans le micro controleur : 
```bash 
make install
```
Pour supprimer tout le repertoire build/ :
```bash 
make clean
```
Pour réinstaller le binaire de démo du projet POV :
```bash
make backup 
```


## Comment ça fonctionne ? 


### 1 - Détection et mesure d'un tour 
À chaque fois que le **capteur HALL** passe devant l'aimant, il fait passer à 0V la tension sur le pin PD2 sur lequel il est branché. 

On configure l'interruption lié a un changement de PD2, **INT0_vect** pour se délencher sur un front descendant de PD2. 

Un gestionnaire d'interruption lié à INT0_vect se déclenche note la valeur de TCNT1, le compteur de clock du microcontroleur et le met à 0. On peut donc mesurer le période d'un tour en ticks en **lisant la valelur de TCNT1**. 

### 2 - Affichage d'un motif 
Le driver de la bande de 16 leds accepte un seul 
```c
uint_8t buffer[16] = {1 ,0 , 1 , 1,..., 0, 1} 
```
à la fois.

On dispose d'un affichage circulaire, de rayon 16, dans lequel on repère un pixel grâce a a ses **coordonnées (x, thêta)**.

On divise donc l'espace d'affichage en N (à maximiser), angles thêta de 16 pixels. 

Pour Afficher un buffer plein à un theta précis (comme une aiguille d'horloge) :
- on connait la période d'un tour en ticks
- on sait donc combien de ticks attendre à partir du passage de l'aimant avant d'afficher le buffer. 

### 3 - Fichiers 
Pour générer la Documentation : 
```bash 
doxygen Doxyfile
```
Voici le graphe des dépendances

![texte alternatif](docs/html/main_8c__incl.png)

hall_sensor.h est le driver du capteur hall 

MBI5024.h est le driver de la bande de leds

pattern.h permet de définir un pattern_t qui représente le répère dans l'espace d'affichage. 


### Membres du groupe : 

Lisa Fredon

Bouchra EZZAGMOUNY

César Larragueta. 

### Boites POV utilisées : 
14 et 22 et 23. 

