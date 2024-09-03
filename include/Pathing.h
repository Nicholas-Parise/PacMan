#ifndef PATHING_H
#define PATHING_H

#pragma once
#include "Node.h"
#include "configuration.h"
#include <vector>
#include <queue>

class Pathing
{
    public:
        Pathing();
        virtual ~Pathing();
        std::vector<Node> shortestPath(Node start, Node finsh);

    protected:

    private:
        bool isValid(int r, int c);
        std::vector<Node> avaliableDirections(Node n);
        Node nullNode;
        int maxValue;

        int dist[conf::VERTEX];
        Node prev[conf::VERTEX];
};

#endif // PATHING_H
