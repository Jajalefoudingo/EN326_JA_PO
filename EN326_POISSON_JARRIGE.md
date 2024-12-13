# Table des matières

- [REGLAGES PRELIMINAIRES](#reglages-preliminaires)
- [PARTIE 1 : TP - LED et Bouton](#partie-1-tp---led-et-bouton)
  - [Fonctionnalités](#fonctionnalites)
  - [Instructions](#instructions)
    - [1. Code](#1-code)
    - [2. Compilation et Flash](#2-compilation-et-flash)
    - [3. Utilisation](#3-utilisation)
  - [Remarques](#remarques)
  - [Exemple de sortie console](#exemple-de-sortie-console)
- [PARTIE 2 : TP - Com I2C](#partie-2-tp---com-i2c)
  - [Fonctionnalités](#fonctionnalites-1)
  - [Instructions](#instructions-1)
    - [1. Code](#1-code-1)
    - [2. Compilation et Flash](#2-compilation-et-flash-1)
    - [3. Utilisation](#3-utilisation-1)
    - [4. Détails Techniques](#4-details-techniques)
      - [Capteur de Température](#capteur-de-temperature)
      - [Capteur d'Humidité](#capteur-dhumidite)
      - [Capteur de Pression](#capteur-de-pression)
    - [5. Fonctions Utilisées](#5-fonctions-utilisees)
    - [6. Exemple de sortie console](#6-exemple-de-sortie-console)
  - [Observations et Difficultés](#observations-et-difficultes)
- [PARTIE 3 : TP - Ping Pong](#partie-3-tp---ping-pong)
  - [Fonctionnalités](#fonctionnalites-2)
  - [Instructions](#instructions-2)
    - [1. Code](#1-code-2)
    - [2. Compilation et Flash](#2-compilation-et-flash-2)
    - [3. Utilisation](#3-utilisation-2)
    - [4. Détails Techniques](#4-details-techniques-1)
    - [5. Fonctions Utilisées](#5-fonctions-utilisees-1)
    - [6. Exemple de sortie console](#6-exemple-de-sortie-console-1)
    - [7. Observations et Difficultés](#7-observations-et-difficultes)
- [Projet : Envoi de Données Température via LoRaWAN](#projet---envoi-de-donnees-temperature-via-lorawan)
  - [Fonctionnalités Clés](#fonctionnalites-cles)
  - [Instructions](#instructions-3)
    - [1. Code](#1-code-3)
    - [2. Compilation et Flash](#2-compilation-et-flash-3)
  - [Code Implémenté](#code-implimente)
  - [Explications Techniques](#explications-techniques)
  - [Envoi des Données vers ThingsBoard](#envoi-des-donnees-vers-thingsboard)


# REGLAGES PRELIMINAIRES

Activer l'environement virtuel :
```bash
source <env_name>/bin/activate
```

Récupérer le projet  
```bash
$git clone https://github.com/Jajalefoudingo/EN326_JA_PO.git
$git switch master
$cd EN326_JA_PO
$mbed deploy
```


# PARTIE 1 : TP - LED et Bouton

Cette partie du TP permet de contrôler une LED connectée à un microcontrôleur à l'aide d'un bouton poussoir. La LED clignote à une fréquence ajustable, et cette fréquence augmente à chaque relâchement du bouton.

## Fonctionnalités

- La LED clignote à une fréquence initiale de 1 Hz.
- Appuyer sur le bouton mesure la durée d'appui.
- Relâcher le bouton augmente la fréquence de clignotement de 0,5 seconde.
- La durée d'appui est affichée sur la console série.

## Instructions

### 1. **Code** :
Le code se situe sur GIT.
   - Telecharger le dernier commit ici : https://github.com/Jajalefoudingo/EN326_JA_PO.git
   - Décommenter **PARTIE 1 TP : Led - Bouton** (ligne 4 à 71)

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash 
  $mbed compile
  $sixtron_flash

### 3. **Utilisation**
1. Connectez-vous à la console série via un terminal en utilisant la commande suivante :
   ```bash
   $minicom -D /dev/ttyUSB0 -b 115200

- **Baud rate** : 115200
- Observez les données collectées affichées sur la console série.

## Remarques

- La fréquence de clignotement augmente indéfiniment si le bouton est pressé et relâché plusieurs fois.
- Il est possible de modifier la valeur initiale de la fréquence de clignotement en ajustant la variable `led_rate`.

## Exemple de sortie console
The time taken was 1271 milliseconds  
The time taken was 187 milliseconds  
The time taken was 225 milliseconds  


# PARTIE 2 : TP - Com I2C

Cette partie du TP explore la communication avec des capteurs via le protocole I2C en utilisant un microcontrôleur. Il permet de lire les données de température, d'humidité et de pression à partir de capteurs connectés.

## Fonctionnalités

- Communication I2C avec des capteurs pour recueillir des données :
  - Température
  - Humidité
  - Pression
- Les données sont affichées sur la console série.
- Détection automatique des périphériques I2C connectés (via `scan_I2C`).

## Instructions

### 1. **Code**
Le code est disponible sur GIT :
- Téléchargez le dernier commit ici : https://github.com/Jajalefoudingo/EN326_JA_PO.git
- Décommentez la section **PARTIE 2 TP : Com I2C** (lignes 75 à 115) pour activer le code lié à ce TP. Ne pas oublier de recommenter le code de la Partie 1 du TP.

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash 
  $mbed compile
  $sixtron_flash

### 3. **Utilisation**
1. Connectez-vous à la console série via un terminal en utilisant la commande suivante :
   ```bash
   $minicom -D /dev/ttyUSB0 -b 115200

- **Baud rate** : 115200
- Observez les données collectées affichées sur la console série.

### 4. **Détails Techniques**

#### Capteur de Température
- **Adresse 7 bits** : 0x48
- **Adresse 8 bits** : 0x48 << 1
- **Registre** : 0xE3

#### Capteur d'Humidité
- **Adresse 7 bits** : 0x40
- **Adresse 8 bits** : 0x40 << 1
- **Registre** : 0xE5

#### Capteur de Pression
- **Adresse** : 0x70 << 1 | 1
- **Registre** : 0xF7

### 5. **Fonctions Utilisées**

- `Print_temp_I2C` : Lit et affiche la température.
- `Print_humid_I2C` : Lit et affiche l'humidité.
- `Print_pressure_I2C` : Lit et affiche la pression.

Ces fonctions sont rangées dans le fichier utils.c

### 6. **Exemple de sortie console**


Temperature = 25.52 C                                                                  
Humidite = 41.38 % HR                                                                  
Temperature = 25.51 C                                                                  
Humidite = 41.53 % HR                                                                  
Temperature = 25.53 C                                                                  
Humidite = 41.76 % HR     

Nous avons eu de grosse difficultés à afficher la pression et nous n'y sommes pas parvenu. Nous avons fait une fonction lors du debuggage afin de verifier le registre dans lequel la valeur de pression s'affiché. Nous n'avons trouvé aucun registre de ceux mentionné dans la documentation ou la valeur de pression en raw venait s'ecrire.

# PARTIE 3 : TP - Ping Pong

Cette partie du TP explore la gestion des threads en utilisant le microcontrôleur pour implémenter un programme "Ping Pong". Deux threads travaillent de manière concurrente pour afficher des messages, avec synchronisation à l'aide de mutex.

## Fonctionnalités

- Deux threads exécutant les fonctions `ping` et `pong`.
- Synchronisation des threads via un mutex pour éviter les conflits d'accès.
- Un compteur partagé `cpt` permet de suivre le nombre total de messages.
- Arrêt des threads après que le compteur atteint une limite donnée (200).

## Instructions

### 1. **Code**
Le code est disponible sur GIT :
- Téléchargez le dernier commit ici : https://github.com/Jajalefoudingo/EN326_JA_PO.git
- Décommentez la section **PARTIE 3 TP : Ping Pong** pour activer le code lié à cette partie du TP.
- renommer mbed_app.json en __mbed_app.json (pour ne pas le prendre en compte) 

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash
  $mbed compile
  $sixtron_flash
  ```

### 3. **Utilisation**
1. Connectez-vous à la console série via un terminal en utilisant la commande suivante :
   ```bash
   $minicom -D /dev/ttyUSB0 -b 9600
   ```
2. Observez les messages "Ping" et "Pong" affichés en alternance sur la console série.
3. Lorsque le compteur `cpt` atteint 200, le programme s'arrête automatiquement avec le message "Done".

### 4. **Détails Techniques**

- **Thread `ping`** : Affiche "Ping" toutes les 100 ms.
- **Thread `pong`** : Affiche "Pong" toutes les 100 ms.
- **Mutex** : Utilisé pour protéger l'accès concurrent au compteur partagé `cpt`.
- **Drapeaux d'arrêt (`STOP_FLAG`)** : Permettent d'arrêter proprement les threads lorsque le compteur atteint 200.
- **Fréquence d'affichage** : 10 messages par seconde pour chaque thread.

### 5. **Fonctions Utilisées**

- `ping` :
  - Incrémente le compteur `cpt`.
  - Affiche "Ping" sur la console série.
  - Attend 100 ms avant la prochaine itération.

- `pong` :
  - Incrémente le compteur `cpt`.
  - Affiche "Pong" sur la console série.
  - Attend 100 ms avant la prochaine itération.

### 6. **Exemple de sortie console**


Ping  
Pong  
Ping  
Pong  
...  
Done  


### 7. **Observations et Difficultés**

- **Gestion des Threads** : Le programme fonctionne correctement en multitâche grâce à l'utilisation de threads.
- **Arrêt propre** : Le programme s'arrête comme prévu après 200 itérations, grâce aux drapeaux d'arrêt (`STOP_FLAG`).

# Projet : Envoi de Données Température via LoRaWAN


Cette section du projet détaille l'envoi des données de température collectées par le capteur **2SMPB02E** vers la plateforme cloud ThingsBoard en utilisant le protocole LoRaWAN.

## Fonctionnalités Clés

- Lecture de la température via le capteur **2SMPB02E**.
- Formatage des données en payload JSON pour les transmettre au serveur.
- Transmission des données vers le serveur ThingsBoard via LoRaWAN.

## Instructions

### 1. **Code**
Le code est disponible sur GIT :
- Téléchargez le dernier commit ici : https://github.com/Jajalefoudingo/EN326_JA_PO.git
- Décommentez la section **PROJET** (ligne 180 à EOF) pour activer le code lié à cette partie du TP.

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash
  $ mbed compile
  $ sixtron_flash
  ```

## Code Implémenté

### Envoi de la Température
Voici l'extrait de code qui formate et envoie les données de température :

```c
// Lecture et formatage de la température
snprintf(payload, sizeof(payload), "{\"temperature\":%.2f}", smp.temperature() / 256);
printf("%s", payload);

// Copie du payload dans le buffer de transmission
memcpy(tx_buffer, payload, strlen(payload));
packet_len = strlen(payload);
```

### Explications Techniques
1. **Lecture de la Température** :
   - La méthode `smp.temperature()` récupère la température brute.
   - La conversion est effectuée en divisant par 256 pour obtenir la valeur en degrés Celsius.

2. **Buffer de Transmission** :
   - Les données formatées sont copiées dans le buffer `tx_buffer`, qui sera envoyé via LoRaWAN.

### Envoi des Données vers ThingsBoard
- Le payload JSON est transmis au serveur ThingsBoard via le protocole LoRaWAN.
- Les informations d'identification (clé et jeton) sont gérées en amont dans la configuration du module LoRa.

