#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>

const int max = 100;

using coord = unsigned int;

class Maison
{
public:
    Maison(int id, coord x, coord y) : _id(id), _x(x), _y(y)
    {}
    coord getX() { return _x; }
    coord getY() { return _y; }
    int getId() { return _id; }

private:
    int _id;
    coord _x;
    coord _y;

    friend bool operator==(Maison const& m1, Maison const& m2);
};

class Graphe
{
public:
    Graphe();
    std::vector<Maison> getMaisons() { return _maisons; }
    void setOriente(bool o) { _oriente = o; }
    void initMatrice(int);
    void ajoutRoute(int, int, double);
    void ajoutMaison(Maison);
    int lecture(std::string);
    void affichageMatrice();

    void afficheQuartier();
    int estimerDistance(int, int) const;
    int choisirRoute(int, int) const;
    void trouverChemin(int, int) const;

private:
    std::array<std::array<double, max>, max> _matrice;
    std::vector<Maison> _maisons;
    bool _oriente;
    int _nbSommets;
};
