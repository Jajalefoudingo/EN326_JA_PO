# PARTIE 1 TP : Led - Bouton

Ce projet permet de contrôler une LED connectée à un microcontrôleur à l'aide d'un bouton poussoir. La LED clignote à une fréquence ajustable, et cette fréquence augmente à chaque relâchement du bouton.

## Fonctionnalités

- La LED clignote à une fréquence initiale de 1 Hz.
- Appuyer sur le bouton mesure la durée d'appui.
- Relâcher le bouton augmente la fréquence de clignotement de 0,5 seconde.
- La durée d'appui est affichée sur la console série.

## Instructions

### 1. **Code** :
Le code se situe sur GIT.
   - Telecharger le dernier commit ici :
   - Décommenter PARTIE 1 TP : Led - Bouton (ligne 5 à 72)

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash 
  $mbed compile
  $sixtron_flash

### 3. **Utilisation**
1. Connectez-vous à la console série via un terminal en utilisant la commande suivante :
   ```bash
   $minicom -D /dev/ttyUSB0 -b 9600

- **Baud rate** : 9600
- Observez les données collectées affichées sur la console série.

## Remarques

- La fréquence de clignotement augmente indéfiniment si le bouton est pressé et relâché plusieurs fois.
- Modifiez la valeur initiale de la fréquence de clignotement en ajustant la variable `led_rate`.

## Exemple de sortie
The time taken was 1271 milliseconds
The time taken was 187 milliseconds
The time taken was 225 milliseconds
The time taken was 206 milliseconds                                                    
The time taken was 248 milliseconds 





# PARTIE 2 TP : Com I2C

Ce projet explore la communication avec des capteurs via le protocole I2C en utilisant un microcontrôleur. Il permet de lire les données de température, d'humidité et de pression à partir de capteurs connectés.

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
- Téléchargez le dernier commit ici :
- Décommentez la section **PARTIE 2 TP : Com I2C** pour activer le code pertinent.

### 2. **Compilation et Flash**
- Ouvrez un terminal et exécutez les commandes suivantes :
  ```bash 
  $mbed compile
  $sixtron_flash

### 3. **Utilisation**
1. Connectez-vous à la console série via un terminal en utilisant la commande suivante :
   ```bash
   $minicom -D /dev/ttyUSB0 -b 9600

- **Baud rate** : 9600
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

### 3. **Fonctions Utilisées**

- `Print_temp_I2C` : Lit et affiche la température.
- `Print_humid_I2C` : Lit et affiche l'humidité.
- `Print_pressure_I2C` : Lit et affiche la pression.

### 4. *Exemple de Fonctionnement*

Une sortie typique sur la console série pourrait être :
Temperature = 25.52 C                                                                  
Humidite = 41.38 % HR                                                                  
Temperature = 25.51 C                                                                  
Humidite = 41.53 % HR                                                                  
Temperature = 25.53 C                                                                  
Humidite = 41.76 % HR     

difficulté pour la pression


partie ping pong
renommer mbed_app.json en __mbed_app.json (pour ne pas le prendre en compte) et repasser le minicom en baudrate 9600

partie 3 9600 sinon 115200

Pong
Ping
Pong
