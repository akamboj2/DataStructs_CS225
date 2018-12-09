#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

#define EMPTY 0

class Node {
    public:
        int a;
        int b;
        vector<Node *> neighbors;
        Node () : a(EMPTY), b(EMPTY), neighbors() {}
        Node (const int &a_, const int &b_) : a(a_), b(b_), neighbors() {}
        Node (const int &a_, const int &b_, const vector<Node *> &neighbors_) : a(a_), b(b_), neighbors(neighbors_) {}
        Node (const Node &tmpNode) : a(tmpNode.a), b(tmpNode.b), neighbors() {}
        bool operator==(const Node & b_node)
        {
            return a == b_node.a && b == b_node.b;
        }
        Node &operator=(const Node & b_node) {
            // WARNING: This operator does not copy the vector
            a = b_node.a;
            b = b_node.b;
            return *this;
        }
};

struct Graph {
    vector<Node *> nodes;
};

// void makeG(int a_cap,int b_cap, int a, int b){
//   static Graph g;
//   //there must be an easier way to do this...
//
//   //3 things you can do to each container
//   //1. Empty each container
//   bool empA=true,empB=true;
//   //2. Fill them
//   bool fillA=true,fillA=true;
//   //pour across
//   bool atob=true, btoa=true;
//   for(auto n : g.nodes){
//     empA&= !(*n==Node(0,b));//if this node exists empA becomes false
//     empB&= !(*n==Node(a,0));
//     fillA&= !(*n==Node(a_cap,b));
//     fillB&= !(*n==Node(a,b_cap));
//     atob&= !(*n==Node(0,(a+b>b_cap?b_cap:a+b));
//     btoa&= !(*n==Node((b+a>a_cap?a_cap:b+a),0));
//   }
//   if(!empA)
//   return g;
// }
Graph createGraph(int capacityy_a, int capacity_b) {
    // TODO
    Graph g;
    return g;
}


int findSolution(Graph g, int target) {
    // TODO: returns minimum number of steps to reach target liters of water (or -1)
    return -1;
}

int waterPouring(int a, int b, int target) {
    // Call createGraph
    // Call findSolution
    // Graph stateMachineGraph = createGraph(a, b);
    // int steps = findSolution(stateMachineGraph, target);
    // for (Node *graphNode : stateMachineGraph.nodes)
    //     {
    //         delete graphNode;
    //     }

    cout<<"Case: "<<a<<" "<<b<<"\n";
    return 0;
}
