#ifndef NODE_H
#define NODE_H
#include <string>
#include <sstream>

class Node
{
    public:
        Node();
        Node(int r, int c);
        virtual ~Node();

        bool Compare(Node a, Node b);
        bool equals(Node a);
        int getId();
        void null();
        std::string print();

        int row;
        int col;
        int priority; // used for

    protected:

    private:
};

#endif // NODE_H
