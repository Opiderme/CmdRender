# CmdRender

**CmdRender** est un moteur de rendu 2D fonctionnant directement dans votre terminal. Écrit en C++ (C++17), il vous permet de dessiner des formes géométriques (points, lignes, polygones, cercles, carrés, etc.) avec des couleurs RGB personnalisées et même d'animer des éléments à une fréquence d'images (FPS) définie, en utilisant les codes d'échappement ANSI.

## Fonctionnalités

- **Rendu graphique dans le terminal** : Affichage fluide grâce à des séquences d'échappement ANSI (`\033[...`).
- **Formes 2D (`Shape2d`)** : Création, positionnement et animation (déplacement X, Y) de formes.
- **Support des couleurs RGB** : Couleur de contour et couleur de remplissage pour les formes et l'arrière-plan.
- **Primitives de dessin (dans `CmdRender`)** : `drawPoint`, `drawLine`, `drawPolygon`, `drawCircle`.
- **Boucle de jeu basique** : Méthode `show(fps)` intégrée pour cadencer l'affichage, et `clearScreen()` pour réinitialiser le canvas.

## Structure du Projet

- `CmdRender/CmdRender.h` & `CmdRender/CmdRender.cpp` : Le moteur principal qui gère la grille de pixels (le "screen") et l'affichage ANSI.
- `CmdRender/2dEntity/Shape2d.h` & `CmdRender/2dEntity/Shape2d.cpp` : Gestion des entités 2D, pour manipuler et dessiner des formes complexes.
- `main.cpp` : Un exemple d'utilisation (un "Hello World") qui montre comment utiliser la bibliothèque.
- `Makefile` : Fichier de construction pour compiler le projet facilement sous Linux/macOS.

## Compilation

Un `Makefile` est fourni pour simplifier la compilation. Assurez-vous d'avoir `g++` ou un compilateur compatible C++17 installé.

### Sur Windows (Recommandé)

1. Ouvrez votre terminal (PowerShell ou Invite de commandes) à la racine du projet.
2. Compilez le projet en exécutant le script fourni :
   ```powershell
   .\lauch.bat
   ```
3. Exécutez le programme généré :
   ```powershell
   .\main.exe
   ```

### Sur Linux/macOS avec Make

1. Ouvrez votre terminal à la racine du projet.
2. Compilez le projet en tapant :
   ```bash
   make
   ```
3. Exécutez le programme généré :
   ```bash
   ./main
   ```

Pour nettoyer les fichiers de build (via Make), exécutez :
```bash
make clean
```

### Compilation manuelle avec g++

Si vous n'avez ni `make` ni `lauch.bat`, vous pouvez compiler directement (exemple) :
```bash
g++ -Wall -Wextra -std=c++17 -o main main.cpp CmdRender/CmdRender.cpp CmdRender/2dEntity/Shape2d.cpp CmdRender/utils/fileInteract.cpp
```

## Exemple d'Utilisation

Voici le fonctionnement du code d'exemple fourni dans `main.cpp` :

```cpp
#include "CmdRender/CmdRender.h"
#include "CmdRender/2dEntity/Shape2d.h"

int main() {
    // Crée une fenêtre de rendu nommée "HelloWorld" de 629x320 pixels
    // avec une couleur de fond rouge (255, 0, 0).
    CmdRender renderer("HelloWorld", 629, 320, {255, 0, 0});

    // Crée un carré (x=50, y=40, largeur=100, hauteur=100)
    // avec un contour vert (0, 255, 0) et un remplissage vert (0, 255, 0).
    Shape2d square("square", 50, 40, 100, 100, {0, 255, 0}, {0, 255, 0});

    // Boucle d'animation infinie
    while (true){
        square.mouvX(4); // Déplace le carré horizontalement de 4 "pixels"
        square.drawShape(renderer); // Dessine le carré dans le buffer de la fenêtre

        renderer.show(30); // Affiche le contenu du buffer à 30 FPS
        renderer.clearScreen({255, 0, 0}); // Efface l'écran (fond rouge) pour la prochaine frame
    }
    return 0;
}
```
Ce code crée un carré vert qui se déplace horizontalement sur un fond rouge à 30 images par seconde.
test
