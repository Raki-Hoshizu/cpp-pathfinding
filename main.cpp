#include <iostream>
#include <chrono>

#include "Graphe.h"

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();

    Graphe g;
    if (g.lecture("F:/Coding/C++/ProjetGraphe/grapheGenere2.gr") == 0)
    {
        g.affichageMatrice();
        //g.afficheQuartier();
    // Pour graphe non orienté
        g.findWay(1,7);
        //g.dijkstra(1);
    // Pour graphe orienté
        //g.tarjan();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end-begin;
    std::cout << "\n" << elapsed/std::chrono::microseconds(1) << " microsecondes" << std::endl;
}
