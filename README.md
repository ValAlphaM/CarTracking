# Car Tracking

Ce projet vise à développer un système de suivi de voitures en utilisant des technologies de vision par ordinateur. Le système est capable de suivre une voiture à partir d’une image de celle-ci. Il permet d’extraire une vidéo avec un rectangle suivant la voiture demandée.

## Fonctionnalités

- Suivi de voitures à partir d’une image
- Extraction d’une vidéo avec un rectangle suivant la voiture demandée

## Installation

1. Clonez ce dépôt : `git clone https://github.com/votre-utilisateur/Car_Tracking.git`
2. Accédez au répertoire du projet : `cd Car_Tracking`
3. Créez un répertoire de build : `mkdir build && cd build`
4. Générez les fichiers de configuration avec CMake : `cmake ..`
5. Compilez le projet : `make`

## Utilisation

1. Modifier le fichier `main.cpp` pour changer le nom de l'image à traiter et le nom de la vidéo à générer
2. Compilez le projet : `make`
3. Exécutez le binaire généré : `./main`
4. Le résultat est disponible dans le répertoire `videos`

## Licence

Ce projet est sous licence MIT. Veuillez consulter le fichier [LICENSE](LICENSE) pour plus d'informations.
