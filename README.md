# ADA

**ADA** (Another Display Application, ou hommage à Ada Lovelace), est un programme permettant d'interpréter des fichiers `.mct` (Minimalist Content Tree) ainsi que des fichiers CSS simplifiés pour générer une interface graphique. L'objectif est de s'inspirer des avantages du HTML tout en ne conservant qu'une base épurée et minimaliste.

## Utilisation
```bash
ada <fichier.mct>
```

## Les fichiers .mct

Un fichier `.mct` est composé de balises, qui se divisent en deux catégories :

1. **Balises de contenu** : Elles représentent des éléments tels que du texte, des zones de saisie ou des boutons.
2. **Balises conteneur** : Ces balises servent à organiser les éléments enfants.

Dans ADA, il existe deux types de balises conteneur :
- **window** : définit une fenêtre. Elle ne peut contenir qu'un seul élément enfant, qui est généralement une balise `lst`.
- **lst** (liste) : contient plusieurs éléments enfants et les affiche les uns après les autres. Son comportement peut être modifié via le fichier CSS (par exemple, pour changer l'orientation de la liste).

## Les fichiers CSS

Les fichiers CSS utilisés par ADA sont simplifiés par rapport au CSS classique, afin de réduire la complexité. Les sélecteurs ne sont actuellement que des noms simples, sans possibilité de combinaisons complexes. De plus, certaines propriétés CSS ont été repensées pour plus de cohérence. Par exemple, au lieu d'utiliser `color` pour la couleur du texte et `background-color` pour la couleur de fond, ADA utilise respectivement `forecolor` et `backcolor`.

Ce genre de simplifications logiques guide le développement d'ADA.

## Exemple d'application

### app.mct
```xml
<window title="Ma fenêtre !" width="800" height="500" stylesheet="style.css">
    <lst style="main">
        <text style="main-text" value="Hello World">
        <button style="main-button" value="Cliquez-moi">
    </lst>
</window>
```

### style.css
```css
main {
    layout: column;
    padding: 25px;
}
main-text {
    width: 100%;
    height: 75%;
}
main-button {
    width: 100%;
    height: 25%;
    backcolor: green;
}
```