#include "Node.h"


Node::Node(int r, int c, Directions d)
{
    row = r;
    col = c;
    direction = d;
}

Node::Node(int r, int c)
{
    row = r;
    col = c;
    direction = NONE;
}


Node::Node()
{
    row = 0;
    col = 0;
    direction = NONE;
}

bool Node::equals(Node a){
    return ((a.row == row) && (a.col == col));
}


int Node::getId(){
    return (row*28 + col);
}

void Node::null(){
    row = -1;
    col = -1;
}


std::string Node::print(){
    std::ostringstream oss;
oss<<"row:"<<row<<" col:"<<col<<"";
return oss.str();
}


Node::~Node()
{
    //dtor
}
