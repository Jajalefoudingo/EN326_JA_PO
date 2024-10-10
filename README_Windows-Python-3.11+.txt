Pour les utilisateurs Windows qui ont déjà une installation Python 3.11/3.12 +, voici la procédure pour installer correctement Mbed :

 - "pipx install mbed-cli"
 - Télécharger et ouvrir Visual Studio Build tool  https://aka.ms/vs/17/release/vs_BuildTools.exe
 - Cocher "Desktop Development with C++"
 - Lancer l'installation ("Install" en bas à droite, ~20min à 30min)
 - Redémarrer le PC
 - "pipx runpip mbed-cli install --upgrade setuptools"
 - Faire "mbed import mbed-os-example-blinky" (erreur à la fin, normal).
 - Dans le fichier "requirement.txt" du dossier "mbed-os", modifier les lignes suivantes:
    - six>=1.16.0
    - urllib3[secure]>=1.26.5,<1.27
    - hidapi>=0.14.0;platform_system!="Linux"
 - Réinstaller les dépendances : "pipx runpip mbed-cli install --use-pep517 -r requirements.txt"
 - Retenter un "mbed compile" dans le dossier " mbed-os-example-blinky".
 - ... et là ca devrait être bon pour compiler.
 - Pas la peine de répéter la manip sur les "requirements.txt" à chaque nouveau projet, une fois c'est bon.