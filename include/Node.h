#ifndef NODE_H
#define NODE_H
#include <string>
#include <sstream>
#include "Directions.h"

class Node
{
    public:
        Node();
        Node(int r, int c);
        Node(int r, int c, Directions d);
        virtual ~Node();

        bool Compare(Node a, Node b);
        bool equals(Node a);
        int getId();
        void null();
        std::string print();

        int row;
        int col;
        int priority; // used for
        Directions direction;

    protected:

    private:
};

#endif // NODE_H
