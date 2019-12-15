# ProjetGraphe
Coustance Nathan
Coyle Matthew

Pour compiler le projet :
	g++ -std=c++14 -Wall main.cpp Graphe.cpp -o projetGraphe.exe
	./projetGraphe.exe -h pour accéder au manuel

main.cpp
	-> Gestion des arguments passés en paramètres

Graphe.h
	-> Déclaration de la classe Maison
	-> Déclaration de la classe Graphe

Graphe.cpp
	-> Code des fonctions de Graphe

Fichiers .gr
	-> Fichiers de graphe sous la forme :
		o no  		// go pour orienté, autre pour non orienté
		v x			// x pour le nombre de sommets (vertex)
		m i x y		//Ligne pour ajouter une maison
						i: entier identifiant une maison
						x: Coordonnée x de la maison
						y: Coordonnée y de la maison
		e m n w 	//Ligne pour ajouter un arc
						m: identifiant de la maison source
						n: identifiant de la maison destination
						w: poids de l'arc
	-> grapheNO1.gr
		Graphe non orienté avec 500 maisons qui ont chacunes +- 10 liaisons
	-> grapheNO2.gr
		Graphe non orienté avec 15 maisons qui ont chacune +- 3 liaisons
	-> grapheTarjan.gr
		Graphe orienté pour expérimenter l'algorithme Tarjan

comparaison.png
	-> Tableau de comparaison de l'exécution de A* et de Dijkstra pour grapheNO1.gr
		/!\ Si le temps d'exécution est anormalement long pour A* sur 400 -> 2
			c'est à cause des cout inclus dans la fonctions, en les enlevant
			on gagne +- 3ms

genGraphe.py
	-> Script python pour générer un graphe.gr
	Commande :
		python genGraphe.py nbSommets nbArcsParSommets >> fichier.gr

A*
	-> Graphe::calcHCost()
		Calcule la distance de la maison actuelle à la maison destination
	-> Graphe::findWay()
		hCost : distance jusqu'à la maison destination
		gCost : distance depuis la maison source
		fCost = hCost + gCost
		Choisis parmi les maisons "ouvertes" celle avec le fCost le plus bas
			Si deux fCost sont égaux, on choisi celle avec le plus bas hCost
		On enlève la maison choisie des "ouvertes" et on l'ajoute aux "visitées"
		Si maison choisie = maison destination
			Affiche le chemin parcouru
			return
		On parcoure la liste des voisins de la maison choisie
			Si voisin est dans "visitées" alors on passe au suivant
			Si le voisin n'est pas dans "ouvertes" ou que le nouveau gCost est plus court que l'ancien
				On met à jour les gCost et hCost du voisin
				On défini son parent = la maison actuelle
				Si le voisin n'est pas dans "ouvertes", on l'y ajoute
		On continue tout ça tant que la liste "ouvertes" n'est pas vide ou qu'on a pas trouvé la destination
	-> Graphe::comparer()
		Exécuter à la fois A* puis Dijkstra et affiche leur temps d'exécution respectif

Tarjan
	-> Graphe::findComponent()
		Parcours les sommets
		Une fois qu'il a trouvé un sommet déjà visité, il trouve sa racine
		Affiche le SCC à l'aide d'une pile que l'on pop
	-> Graphe::tarjan()
		Créé une pile, des tableaux stockant la numérotation de la visite
		On initialise tout à -1 pour indiquer que rien n'a été visité
		On exécute findComponent pour chacun des sommets non visités

Kruskal
	-> find()
		Va chercher le plus ancien prédecesseur d'un sommet passé en paramètre
	-> unite()
		Créé une union entre deux sommets passés en paramètre
	-> Graphe::kruskal()
		Initialise la liste des prédecesseurs
		On récupère la liste des arcs et leur poids dans un vector
		On trie le vector
		On affiche 0 à nbSommets-1 arcs
			on parcourt le vector
			avec find on vérifie si l'union des deux noeuds créé un cycle
			si ça n'en créé pas, on les unis puis on affiche l'arc

