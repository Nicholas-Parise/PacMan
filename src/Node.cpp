#include "Node.h"

Node::Node(int r, int c)
{
    row = r;
    col = c;
}


Node::Node()
{
    row = 0;
    col = 0;
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
