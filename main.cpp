#include <iostream>
#include "Graphe.h"

int main()
{
    Graphe g;
    g.lecture("F:/Coding/C++/Graphe/graphe.txt");
    g.affichageMatrice();
    g.afficheQuartier();
    g.trouverChemin(1,5);
}
