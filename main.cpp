#include <iostream>

#include "Graphe.h"

int main()
{
    Graphe g;
    std::string path("F:/Coding/C++/ProjetGraphe/grapheNO2.gr");
    if (g.lecture(path) == 0)
    {
        g.affichageMatrice();
    // Pour graphe non orienté
        //g.findWay(1, 13);
        //g.dijkstra(1);
        //g.comparer(400, 2);
        //g.kruskal();
    // Pour graphe orienté
        //g.tarjan();
    }
}
