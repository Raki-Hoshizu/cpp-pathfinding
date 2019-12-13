#include <iostream>
#include "Graphe.h"

int main()
{
    Graphe g;
    if (g.lecture("F:/Coding/C++/ProjetGraphe/graphe.txt") == 0)
    {
        g.affichageMatrice();
        g.afficheQuartier();
        g.trouverChemin(1,5);
    }
}
