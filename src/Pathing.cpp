#include "Pathing.h"

class Compare
{
public:
    bool operator() (Node a, Node b)
    {
        return (a.priority > b.priority);
    }
};

Pathing::Pathing()
{
    Node nullNode(-1,-1);
    maxValue = conf::SIZEY*conf::SIZEX;

    // initializing array
    std::fill(dist, dist + conf::VERTEX, INT_MAX);
    std::fill(prev, prev + conf::VERTEX, nullNode);
}

Pathing::~Pathing()
{
    //dtor
}



bool Pathing::isValid(int r, int c)
{
    if(r<conf::SIZEY && r>=0 && c<conf::SIZEX && c>=0)
    {
        return true;
    }

    return false;
}


/**
* determines the avaliable directions that do not contain a wall
* @n current node, this contains row,col, and direction
* @return vector of Node directions
*/
std::vector<Node> Pathing::avaliableDirections(Node n)
{

    int r = n.row;
    int c = n.col;
    Node current;
    std::vector<Node> dirs;

    if(isValid(r-1,c))
    {
        if(conf::GameMatrix[r-1][c] != 1 && n.direction != DOWN)
        {

            current = Node(r-1,c,UP);
            dirs.push_back(current);// up
        }
    }

    if(isValid(r,c-1))
    {
        if(conf::GameMatrix[r][c-1] != 1 && n.direction != RIGHT)
        {

            current = Node(r,c-1,LEFT);
            dirs.push_back(current);//cout<<"Left ";
        }
    }else{
        //special case teleporter
        if(r == 14 && c < 1)
        {
            current = Node(r,c-1,LEFT);
            dirs.push_back(current);//cout<<"Left ";
        }
    }

    if(isValid(r+1,c))
    {
        if(conf::GameMatrix[r+1][c] != 1 && n.direction != UP)
        {

            //special case can't go back inside the ghost house
            //if(!(r == conf::GhostHomeRow && c == conf::GhostHomeCol)){
                current = Node(r+1,c,DOWN);
                dirs.push_back(current);//cout<<"Down ";
            //}

        }
    }

    if(isValid(r,c+1))
    {
        if(conf::GameMatrix[r][c+1] != 1 && n.direction != LEFT)
        {

            current = Node(r,c+1,RIGHT);
            dirs.push_back(current);//cout<<"Right ";
        }
    }else{
        //special case teleporter
        if(r == 14 && c > 26)
        {
             current = Node(r,c+1,RIGHT);
            dirs.push_back(current);//cout<<"Right ";
        }
    }

    return dirs;
}


/**
 * uses dijkstra algorithm to find the shortest path between two nodes
 * @param start starting node
 * @param finish ending node
 * @return list of steps to get from start to finish
 * distance is always 1 beucase it's a grid
 */
std::vector<Node> Pathing::shortestPath(Node start, Node finish)
{
    iteration = 0;
    Node current;
    std::vector<Node> sequence;
    std::priority_queue<Node, std::vector<Node>, Compare> pqueue;

    // reset arrays
    for (int i = 0; i < conf::VERTEX; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = nullNode;
    }

    dist[start.getId()] = 0;
    start.priority = 0;  // we set the priority to 0
    pqueue.push(start);   // and we add the start node to the queue


    while (!pqueue.empty())
    {
        iteration ++;
        current = pqueue.top(); // get top node
        pqueue.pop();   // and remove it

        if(current.equals(finish) && iteration > 1)  // if it found the end
        {

            while(!current.equals(nullNode))
            {
                sequence.insert(sequence.begin(),current); // go through all the previous nodes and find the path
                current = prev[current.getId()];
            }
            return sequence; // return this path
        }

        for (Node v : avaliableDirections(current))   // Go through all v neighbors of "current"
        {

            int altDist = dist[current.getId()] + 1;

            if(altDist < dist[v.getId()])  // if the new distance is better than the previous
            {

                dist[v.getId()] = altDist; // change distance
                prev[v.getId()] = current; // add to the previous array (for path finding)
                v.priority = altDist;
                pqueue.push(v); // add node to the queue and set the priority to the distance
            }
        }
    }

    //start.direction = NONE; // this makes it reverse
    return scaredSolver(start); // failed but prevents going through walls
}


std::vector<Node> Pathing::scaredSolver(Node start)
{

    std::vector<Node> sequence;
    std::vector<Node> temp = avaliableDirections(start);
    int value = (rand()%temp.size());

    sequence.push_back(start);

    sequence.push_back(temp[value]);
    return sequence;
}




