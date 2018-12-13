#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "DirectedEdge.h"

#include "CYOA.h"

#include <string>
#include <iostream>

int main() {
 cout<<"at least entering main?";
 // CYOA cyoa;
 // Graph<Vertex, DirectedEdge> g = cyoa.load("data/");
 // std::cout << g << std::endl;
 //
 //  // Modify the g.shortestPath call to find the shortest path to your story:
 //
 //  std::list<std::string> path = g.shortestPath("waf-zoey", "waf-zoey-oak");
 //  for (std::string key : path) {
 //    std::cout << key << " -> ";
 //  }
 //  std::cout << "[THE END]" << std::endl;

//  cout<<"Here1";

/*
       _ b   /--------- h
      /  | _/           |
    a -- c -- e    f -- g
      \_   _/
         d
*/
// Graph<Vertex, Edge> g;
// g.insertVertex("a");
// g.insertVertex("b");
// g.insertVertex("c");
// g.insertVertex("d");
// g.insertVertex("e");
// g.insertVertex("f");
// g.insertVertex("g");
// g.insertVertex("h");
//
// // Edges on `a`:
// g.insertEdge("a", "b");
// g.insertEdge("a", "c");
// g.insertEdge("a", "d");
// //  cout<<"is it adj? "<<g.isAdjacent("d","a")<<"\n";
// // Additional edges on `b`:
// g.insertEdge("b", "c");
//
// // Additional edges on `c`:
// g.insertEdge("c", "e");
// g.insertEdge("c", "h");
//
// // Additional edges on `d`:
// g.insertEdge("d", "e");
//
// // Additional edges on `e`: (none)
//
// // Additional edges on `f`:
// g.insertEdge("f", "g");
//
// // Additional edges on `g`:
// g.insertEdge("g", "h");
//
// // Additional edges on `h`: (none)
//
//   g.removeVertex("d");
//   cout<<g.isAdjacent("g","f");
//
//   g.removeEdge("f","g");
//   cout<<g.isAdjacent("f","g");
Graph<Vertex, Edge> g;
g.insertVertex("a");
g.insertVertex("b");
g.insertVertex("c");
g.insertEdge("a", "b");
g.insertEdge("a", "c");
g.insertEdge("b", "c");
   std::list<std::string> path = g.shortestPath("a","c");
 for (auto p : path) cout<<p<<" ";


  return 0;
}
