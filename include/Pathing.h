#ifndef PATHING_H
#define PATHING_H

#pragma once
#include <vector>
#include <queue>
#include "Node.h"
#include "configuration.h"
#include "Directions.h"
#include <iostream>

class Pathing
{
    public:
        Pathing();
        virtual ~Pathing();
        std::vector<Node> shortestPath(Node start, Node finsh);
        std::vector<Node> scaredSolver(Node start);

    protected:

    private:
        bool isValid(int r, int c);
        std::vector<Node> avaliableDirections(Node n);
        Node nullNode;
        int maxValue;
        int iteration;

        int dist[conf::VERTEX];
        Node prev[conf::VERTEX];

};

#endif // PATHING_H
