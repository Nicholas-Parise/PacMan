
#include "Pathing.h"

class Compare{
    public:
        bool operator() (Node a, Node b){
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



bool Pathing::isValid(int r, int c){
 if(r<conf::SIZEY && r>=0 && c<conf::SIZEX && c>=0){
        return true;
 }

return false;
}



std::vector<Node> Pathing::avaliableDirections(Node n){

        int r = n.row;
        int c = n.col;
        Node current;
        std::vector<Node> dirs;

        // is not in range

        if(conf::GameMatrix[r-1][c] != 1){//&& CurrentDirection != DOWN){
            if(isValid(r-1,c)){
                current = Node(r-1,c);
                dirs.push_back(current);// up
            }
        }

        if(conf::GameMatrix[r][c-1] != 1){//&& CurrentDirection != RIGHT){
            if(isValid(r,c-1)){
                current = Node(r,c-1);
                dirs.push_back(current);//cout<<"Left ";
            }
        }

        if(conf::GameMatrix[r+1][c] != 1){// && CurrentDirection != UP){
            if(isValid(r+1,c)){
                current = Node(r+1,c);
                dirs.push_back(current);//cout<<"Down ";
            }
        }

        if(conf::GameMatrix[r][c+1] != 1){// && CurrentDirection != LEFT){
            if(isValid(r,c+1)){
                current = Node(r,c+1);
                dirs.push_back(current);//cout<<"Right ";
            }
        }

        return dirs;
    }


    /**
     * uses dijkstra algorithm to find the shortest path between two nodes
     * @param start starting node
     * @param finsh ending node
     * @return list of steps to get from start to finish
     * distance is always 1 beucase it's a grid
     */
    std::vector<Node> Pathing::shortestPath(Node start, Node finsh){

        Node current;

        // reset arrays
        for (int i = 0; i < conf::VERTEX; i++) {
            dist[i] = INT_MAX;
            prev[i] = nullNode;
        }

        std::priority_queue<Node, std::vector<Node>, Compare> pqueue;

        std::vector<Node> sequence;
        dist[start.getId()] = 0;
        start.priority = 0;  // we set the priority to 0
        pqueue.push(start);   // and we add the start node to the queue


        while (!pqueue.empty()){

            current = pqueue.top(); // get top node
            pqueue.pop();   // and remove it


            if(current.equals(finsh)){ // if it found the end

                while(!current.equals(nullNode)){
                    sequence.insert(sequence.begin(),current); // go through all the previous nodes and find the path
                    current = prev[current.getId()];
                }
                return sequence; // return this path
            }

            for (Node v : avaliableDirections(current)) { // Go through all v neighbors of "current"
            //    cout<<"neighbours: "<<v.print()<<endl;

                int altDist = dist[current.getId()] + 1;

                if(altDist < dist[v.getId()]){ // if the new distance is better than the previous

                    dist[v.getId()] = altDist; // change distance
                    prev[v.getId()] = current; // add to the previous array (for path finding)
                    v.priority = altDist;
                    pqueue.push(v); // add node to the queue and set the priority to the distance
                }
            }
        }

        return sequence; // failed
    }
