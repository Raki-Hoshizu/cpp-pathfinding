#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <chrono>

const int max = 500;

using coord = unsigned int;
using adjMatrice = std::array<std::array<double, max>, max>;

class Maison
{
public:
    Maison(int id, coord x, coord y) : _id(id), _idPred(id), _x(x), _y(y)
    {}
    coord getX() { return _x; }
    coord getY() { return _y; }
    int getId() { return _id; }

    int getIdPred() const { return _idPred; }
    void setIdPred(int id) { _idPred = id; }

private:
    int _id;
    int _idPred;
    coord _x;
    coord _y;

    friend bool operator==(Maison const& m1, Maison const& m2);
};

class Graphe
{
public:
    Graphe();
    void setOriente(bool o) { _oriente = o; }
    void initMatrice(int);
    void ajoutRoute(int, int, double);
    void ajoutMaison(Maison);
    int lecture(std::string);
    void affichageMatrice();

    // Algorithme A*
    double calcHCost(int, int) const;
    double findWay(int, int);

    //Dijkstra functions
    int findMinVertex(double*, bool*) const;
    void dijkstra(int) const;

    void comparer(int,int);

    // Algorithme tarjan
    void findComponent(int, int*, int*, std::stack<int>&, bool*) const;
    void tarjan() const;

private:
    adjMatrice _matrice;
    std::vector<Maison> _maisons;
    bool _oriente;
    int _nbSommets;
};
