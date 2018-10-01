compile rules:

make rules:
  - make: compile
  - make run: compile+run
  - make clean: nettoie le dossier

Toutes les classes sont décrites dans le fichier headers.cpp.

  Les méthodes associées à chaque composants sont dans <composant>.cpp. les
constructeurs y sont décris. Les méthodes ne correspondants pas à une grande
classe de composant sont dans methods.cpp.

  Le fichier PROG.txt contient le code assembleur que l'on souhaite assembler.

  Les fichiers <composants>.txt décrivent les composants ainsi que leur lien avec
les autres composants de la plateforme (via SOURCE). Les exemples sont là pour
montrer comment il faut les remplir (pour lier un composant à un autre, il suffit
de mettre dest.SOURCE=source.LABEL)

  Le fichier platform.txt permet de dire quels sont les composants à, créer
(via leur nom ou arborescence). L'ordre de déclaration des composants est a
priori important (non testé). Il faut les instancier dans l'ordre de parcours
de l'information (CPU>>BUS>>MEMORY>>BUS>>DISPLAY)


  Etat du projet au moment du rendu : les composants ont tous un read/simulate
qui fonctionne (testé séparément). Le lien entre les composants est établi
(via la fonction platform.load()). Le simulate n'est pas défini.
