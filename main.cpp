#include <iostream>
#include <unistd.h>

#include "Graphe.h"

// For GetCurrentWorkingDir
#include <stdio.h>
#include <unistd.h>
#define GetCurrentDir getcwd

// Retourne le chemin absolu de ce fichier
std::string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

void start(std::string fichier, std::string fonction, std::string source, std::string destination)
{
    std::string path(GetCurrentWorkingDir()+"/"+fichier);
    int numFonction = std::stoi(fonction);
    int src = std::stoi(source);
    int dst = std::stoi(destination);
    Graphe g;
    if (g.lecture(path) == 0)
    {
        switch(numFonction)
        {
        case -1:
        case 0:
            g.affichageMatrice();
            break;
        case 1:
            if (src == -1 or dst == -1) { std::cout << "Please enter source and destination number (-s and -d args)\n"; return; }
            g.findWay(src, dst);
            break;
        case 2:
            if (src == -1) { std::cout << "Please enter source number (-s arg)\n"; return; }
            g.dijkstra(src);
            break;
        case 3:
            if (src == -1 or dst == -1) { std::cout << "Please enter source and destination number (-s and -d args)\n"; return; }
            g.comparer(src, dst);
            break;
        case 4:
            g.tarjan();
            break;
        case 5:
            g.kruskal();
            break;
        default:
            std::cerr << "Unknown function number (-f) : " << numFonction << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

int main(int  argc, char* argv[])
{
    int opt;
    std::string fichierGraphe(""), functionNumber("-1");
    std::string source("-1"), destination("-1");
    while ((opt = getopt(argc, argv, "g:f:s:d:h")) != -1)
    {
        switch(opt)
        {
        case 'h':
            std::cout << "How to execute :\n";
            std::cout << "\t./projetGraphe.exe -g fichierGraphe.gr -f functionNumber -s sourceNode -d destinationNode\n";
            std::cout << "Function numbers :\n";
            std::cout << "\t0: affichageMatrice()\n";
            std::cout << "\t1: findWay(sourceNode, destinationNode)\n";
            std::cout << "\t2: dijkstra(sourceNode)\n";
            std::cout << "\t3: comparer(sourceNode, destinationNode)\n";
            std::cout << "\t4: tarjan()\n";
            std::cout << "\t5: kruskal()\n";
            return -1;
        case 'g':
            fichierGraphe = optarg;
            break;
        case 'f':
            functionNumber = optarg;
            break;
        case 's':
            source = optarg;
            break;
        case 'd':
            destination = optarg;
            break;
        default:
            std::cerr << "Argument invalide : " << optarg << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    start(fichierGraphe, functionNumber, source, destination);
}
