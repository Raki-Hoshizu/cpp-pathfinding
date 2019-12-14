#include <iostream>

#include "Graphe.h"

int main()
{
    Graphe g;
    if (g.lecture("F:/Coding/C++/ProjetGraphe/grapheGenere.gr") == 0)
    {
        g.affichageMatrice();
    // Pour graphe non orienté
        //g.findWay(150,350);
        //g.dijkstra(1);
        g.comparer(150, 350);
    // Pour graphe orienté
        //g.tarjan();
    }
}
