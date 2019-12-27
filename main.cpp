#include <iostream>
#include <unistd.h>

#include "Graphe.h"

int main(int  argc, char* argv[])
{
    int opt;
    std::string fichierGraphe(""), functionNumber("-1");
    std::string source("1"), destination("1");
    if(argc == 1) { printHelp(); return -1; }
    while ((opt = getopt(argc, argv, "g:f:s:d:h")) != -1)
    {
        switch(opt)
        {
        case 'h':
            printHelp();
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
            std::cerr << "Argument invalide : " << optarg;
            std::cout << "\n";
            exit(EXIT_FAILURE);
        }
    }
    start(fichierGraphe, functionNumber, source, destination);
}
