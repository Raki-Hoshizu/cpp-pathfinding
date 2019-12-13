#include "Graphe.h"

Graphe::Graphe():  _oriente(false), _nbSommets(0)
{}

bool operator==(Maison const& m1, Maison const& m2)
{
    return (m1._x == m2._x && m1._y == m2._y);
}

void Graphe::initMatrice(int nbS)
{
    _nbSommets = nbS;
    for (int i(0); i<_nbSommets; ++i)
    {
        for (int j(0); j<_nbSommets; ++j)
        {
            _matrice[i][j] = 0;
        }
    }
    std::cout << "Graphe initialise" << std::endl;
}

void Graphe::ajoutRoute(int origine, int destination, double poids)
{
    if (!_oriente) _matrice[destination-1][origine-1] = poids;
    _matrice[origine-1][destination-1] = poids;
}

void Graphe::ajoutMaison(Maison m)
{
    for (Maison i : _maisons)
    {
        if(i == m or i.getId() == m.getId())
            return;
    }
    _maisons.push_back(m);
    std::cout << "\tMaison ajoutee\n";
}

int Graphe::lecture(std::string input)
{
    std::ifstream fichier(input);

    if (fichier)
    {
        unsigned int nbLignes(0);
        std::string ligne("");
        while(getline(fichier, ligne))
        {
            ++nbLignes;
            if (ligne[0] == 'o')
            {
                //Parsing des arguments
                unsigned int i(1);
                std::vector<std::string> args;
                while ((i < ligne.length()) and (args.size()<1))
                {
                    std::string arg = "";
                    while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
                    while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
                    if (arg.length() > 0) args.push_back(arg);
                }
                if (args.size() > 1)
                {
                    std::cout << "Trop d'arguments à la ligne " << nbLignes << std::endl;
                    return 1;
                }
                setOriente(!args[0].compare("go"));
            }
            else if (ligne[0] == 'v')
            {
                //Parsing des arguments
                unsigned int i(1);
                std::vector<std::string> args;
                while ((i < ligne.length()) and (args.size()<1))
                {
                    std::string arg = "";
                    while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
                    while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
                    if (arg.length() > 0) args.push_back(arg);
                }
                if (args.size() > 1)
                {
                    std::cout << "Trop d'arguments à la ligne " << nbLignes << std::endl;
                    return 1;
                }
                int nbSommets;
                try
                {
                    nbSommets = stoi(args[0]);
                }
                catch (const std::invalid_argument& ia)
                {
                    std::cerr << "Argument invalide : " << ia.what() << " Ligne " << nbLignes << std::endl;
                    nbSommets = 0;
                }
                initMatrice(nbSommets);
            }
            else if (ligne[0] == 'm')
            {
                unsigned int i(1);
                std::vector<std::string> args;
                while ((i < ligne.length()) and (args.size()<3))
                {
                    std::string arg = "";
                    while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
                    while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
                    if (arg.length() > 0) args.push_back(arg);
                }
                if (args.size() != 3)
                {
                    std::cout << args.size() << std::endl;
                    std::cout << "Nombre d'arguments incorrects ligne " << nbLignes << std::endl;
                    return 1;
                }
                int id;
                unsigned int x, y;
                try
                {
                    id = stoi(args[0]);
                    x = stoi(args[1]);
                    y = stoi(args[2]);
                }
                catch (const std::invalid_argument& ia)
                {
                    std::cerr << "Argument invalide : " << ia.what() << " Ligne " << nbLignes << std::endl;
                    id = 0;
                    x = 0;
                    y = 0;
                }
                ajoutMaison(Maison(id, x, y));
            }
            else if (ligne[0] == 'e')
            {
                unsigned int i(1);
                std::vector<std::string> args;
                while ((i < ligne.length()) and (args.size()<3))
                {
                    std::string arg = "";
                    while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
                    while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
                    if (arg.length() > 0) args.push_back(arg);
                }
                if (args.size() > 3)
                {
                    std::cout << "Trop d'arguments ligne " << nbLignes << std::endl;
                    return 1;
                }
                else if (args.size() < 3)
                {
                    std::cout << "Pas assez d'arguments ligne " << nbLignes << std::endl;
                    return 1;
                }
                int origine, destination;
                double poids;
                try
                {
                    origine = stoi(args[0]);
                    destination = stoi(args[1]);
                    poids = stod(args[2]);
                }
                catch (const std::invalid_argument& ia)
                {
                    std::cerr << "Argument invalide : " << ia.what() << " Ligne " << nbLignes << std::endl;
                    origine = 0;
                    destination = 0;
                    poids = -1;
                }
                ajoutRoute(origine, destination, poids);
            }
            else if (ligne[0] != 'c')
            {
                std::cout << "Ligne " << nbLignes << " non reconnue : " << ligne << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier " << input << std::endl;
        return -1;
    }
    return 0;
}

void Graphe::affichageMatrice()
{
    std::cout << "Matrice d'adjacence des arcs :" << std::endl;
    std::vector<int> largeurColonne;
    for (int i=0; i<_nbSommets; ++i)
    {
        int max=0;
        for (int j=0; j<_nbSommets; ++j)
        {
            std::ostringstream tmp;
            tmp << _matrice[j][i];
            if (tmp.tellp() > max) {max=tmp.tellp();}
        }
        largeurColonne.push_back(max);
    }
    std::cout << "    ";
    for (int i=0; i<_nbSommets; ++i)
        printf("%*d ",largeurColonne[i],i+1);
    std::cout << std::endl;
    for (int i=0; i<_nbSommets; ++i){
        printf("%3d|",i+1);
        for (int j=0; j<_nbSommets; ++j)
        {
            printf("%*.*g ",largeurColonne[j],largeurColonne[j],_matrice[i][j]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graphe::afficheQuartier()
{
    std::cout << "Affichage du quartier :" << std::endl;
    int minX(std::numeric_limits<int>::infinity()), minY(std::numeric_limits<int>::infinity());
    int maxX(0), maxY(0);
    const int maxMatrice(200);
    for (Maison i : _maisons)
    {
        if (i.getX() < minX) { minX = i.getX(); }
        if (i.getX() > maxX) { maxX = i.getX(); }
        if (i.getY() < minY) { minY = i.getY(); }
        if (i.getY() > maxY) { maxY = i.getY(); }
    }
    //std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
    std::array<std::array<std::string, maxMatrice>, maxMatrice> matrice;
    for (int y(minY); y<=maxY-minY+1; ++y)
    {
        for (int x(minX); x<=maxX-minX+2; ++x)
        {
            matrice[x][y] = ".";
        }
    }
    for (Maison i : _maisons)
    {
        matrice[i.getX()][i.getY()] = std::to_string(i.getId());
    }
    for (int y(maxY-minY+1); y>=minY; --y)
    {
        for (int x(minX); x<=maxX-minX+2; ++x)
        {
            std::cout << matrice[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// Algorithme A*
double Graphe::estimerDistance(int id1, int id2) const
{
    //Estimation en vol d'oiseau
    int x1(0), x2(0), y1(0), y2(0);
    for (Maison i : _maisons)
    {
        if (i.getId() == id1) { x1 = i.getX(); y1 = i.getY(); }
        if (i.getId() == id2) { x2 = i.getX(); y2 = i.getY(); }
    }
    return (sqrt(pow(x2-x1,2)+pow(y2-y1, 2)));
}

int Graphe::choisirRoute(int origine, int destination) const
{
    int resId(origine);
    double move(1000), valeurTrans(0), distRoute(0);
    for (unsigned int i(1); i<=_nbSommets; ++i)
    {
        std::cout << "Transition entre " << origine << " et " << i << "...\n";
        distRoute = _matrice[i-1][origine-1];
        if (distRoute > 0)
        {
            valeurTrans = distRoute + estimerDistance(i, destination);
            std::cout << "\tDistance: " << distRoute << std::endl;
            std::cout << "\tValeur de la transition: " << valeurTrans << std::endl;
            if (move > valeurTrans)
            {
                move = valeurTrans;
                resId = i;
            }
        }
        else
        {
            std::cout << "\tPas de transition." << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Transition de " << origine << " vers " << resId << " choisie.\n\n";
    return resId;
}

void Graphe::trouverChemin(int origine, int destination) const
{
    std::cout << "Recherche du chemin de la maison " << origine << " a la maison " << destination << "...\n\n";
    int curseur(origine), tmpCurseur(0);
    double move(0);
    std::vector<int> parcourus;
    parcourus.push_back(origine);
    while (curseur != destination)
    {
        tmpCurseur = choisirRoute(curseur, destination);
        move += _matrice[curseur-1][tmpCurseur-1];
        curseur = tmpCurseur;
        parcourus.push_back(curseur);
    }
    std::cout << "Recapitulatif du parcours :" << std::endl;
    std::cout << "\t";
    for (unsigned int i(0); i<parcourus.size(); ++i)
    {
        std::cout << parcourus[i];
        if(i != parcourus.size()-1) { std::cout << " -> "; }
    }
    std::cout << std::endl;
    std::cout << "\tDistance parcourue : " << move << std::endl;
}


// Dijkstra functions
int Graphe::findMinVertex(double* distance, bool* visited) const
{
    int minVertex(-1);
    for (int i(0); i<_nbSommets; ++i)
    {
        if (!visited[i] && (minVertex == -1 || distance[i] < distance[minVertex]))
        {
            minVertex = i;
        }
    }
    return minVertex;
}

void Graphe::dijkstra(int idMaison) const
{
    int src(idMaison-1);
    double* distance = new double[_nbSommets];
    bool* visited = new bool[_nbSommets];

    for (int i(0); i<_nbSommets; ++i)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[src] = 0;

    for (int i(0); i<_nbSommets-1; ++i)
    {
        int minVertex = findMinVertex(distance, visited);
        visited[minVertex] = true;
        for (int j(0); j<_nbSommets; ++j)
        {
            if (_matrice[minVertex][j] != 0.0 && !visited[j])
            {
                double dist = distance[minVertex] + _matrice[minVertex][j];
                if (dist < distance[j])
                {
                    distance[j] = dist;
                }
            }
        }
    }

    std::cout << "\nDijsktra :" << std::endl;
    for (int i(0); i<_nbSommets; ++i)
    {
        if(i != src)
            std::cout << "\t" << idMaison << " -> " << i+1 << " : " << distance[i] << std::endl;
    }
    delete [] visited;
    delete [] distance;
}


// Algorithme Tarjan
void Graphe::findComponent(int u, int* disc, int* low, std::stack<int> &pile, bool* stacked) const
{
    static int time(0);
    static int count(0);        // Pour numéroter les SCC
    disc[u] = low[u] = ++time;  // Incrémentation du moment de la découverte
    std::cout << "\tAjout du sommet " << u+1 << "..." << std::endl;
    pile.push(u);
    stacked[u] = true;
    for (int v(0); v<_nbSommets; ++v)
    {
        if (static_cast<int>(_matrice[u][v]))
        {
            if (disc[v] == -1)
            {
                findComponent(v, disc, low, pile, stacked);
                low[u] = (low[u]<low[v])? low[u]:low[v];
            }
            else if (stacked[v])
            {
                std::cout << "\tSommet " << v+1 << " deja visite" << std::endl;
                low[u] = (low[u]<disc[v])? low[u]:disc[v];
            }
        }
    }
    int popped = 0;
    if (low[u] == disc[u])
    {
        std::cout << "\t\tSCC " << ++count << " : ";
        while (pile.top() != u)
        {
            popped = pile.top();
            std::cout << popped+1 << " <- ";
            stacked[popped] = false;
            pile.pop();
        }
        popped = pile.top();
        std::cout << popped+1 << std::endl;
        stacked[popped] = false;
        pile.pop();
    }
}

void Graphe::tarjan() const
{
    std::cout << "Tarjan :" << std::endl;
    int* disc = new int[_nbSommets];
    int* low = new int[_nbSommets];
    bool* stacked = new bool[_nbSommets];
    std::stack<int> pile;
    std::cout << "Initialisation..." << std::endl;
    for (int i(0); i<_nbSommets; ++i)
    {
        // On initialise à -1 (rien n'a été visité)
        disc[i] = -1;
        low[i] = -1;
        stacked[i] = false;
    }
    std::cout << "Calcul des SCC (Strongly Connected Component)..." << std::endl;
    for (int i(0); i<_nbSommets; ++i)
    {
        if(disc[i] == -1)
        {
            findComponent(i, disc, low, pile, stacked);
        }
    }
    delete [] disc;
    delete [] low;
    delete [] stacked;
}
