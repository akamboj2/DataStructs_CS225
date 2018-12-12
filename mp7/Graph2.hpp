#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include "Edge.h"
#include "Vertex.h"

//#include <bits/stdc++.h>
/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
using std::vector;
using std::priority_queue;
using std::greater;
using std::cout;
using std::unordered_map;
using std::string;
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  //cout<<"IN HERE!";
  //priority_queue <int, vector<int>, greater<int> > pq;
  //https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    // pq.push(5);
    // pq.push(1);
    // pq.push(10);
    // pq.push(30);
    // pq.push(20);
    //
    // // One by one extract items from min heap
    // while (pq.empty() == false)
    // {
    //     cout << pq.top() << " ";
    //     pq.pop();
    // }

    std::list<std::string> path;
  //Dijkstra's: NOTE THIS ALGORITHM ASSUMES NON NEGATIVE WEIGHTED GRAPH!
  unordered_map<V,unsigned>d;
  unordered_map<string,string> p;//holds current vertex and it's previous as a string
  // unordered_map<string,string>test;
  // unordered_map<string,unsigned>test2;
  // test2["working?"]=132;
  // test["hi"]="working?";
  for(auto v : vertexMap){
    d[v.second]=999999;
    p[v.second.key()]='\0';//string null character
  }
  d.at(vertexMap.at(start))=0;

  unordered_map<std::string, V&> unvisited=vertexMap;
  while(unvisited.size()>0){//visit all the vertices
    //find mininum vertex in
    V min(unvisited.begin()->second.key());
    for(auto v : unvisited){
      if(d.at(v.second)<d.at(min)){
        min=v.second;
      }
    }
//    cout<<"Now visiting: "<<min<<"\n";
    //once you find minimum visit it;
    unvisited.erase(min.key());
    for(auto edge : adjList[min.key()]){
      E e = edge->get(); //get edge from iterator
      V neighbor(e.dest().key());
      if(!e.directed() && neighbor==min){//if your neighor is the one you are visiting
        neighbor = e.source(); //theres a chance that the source is the neighbor
      }
      //first check if we already visited it
//      cout<<"\t at neighbor: "<<neighbor<<"\n";
      if (unvisited.find(neighbor.key())==unvisited.end()) continue; //if it's not in unvisited that means it is visited so go to next neighbor
//      cout<<"\tVisiting it's neighbor: "<<neighbor<<"\n";
      //if we haven't visited it check if this will lead to faster route;
      if (d.at(min)+e.weight() < d.at(neighbor)){
        d.at(neighbor)= d.at(min)+e.weight();
        p.at(neighbor.key())=min.key();
//        cout<<"\t\tCHANGING p of "<<neighbor<<" to "<<min.key()<<"\n";
      }
    }
  }
//  finally after running extract path
  path.push_front(end);//push the end

  string at=end;
  while(true){
    string prev=p[at];//check at it's previous vertex
    if (prev[0]=='\0') break; //if it's at null then you're done break!
    path.push_front(prev);//otherwise push it on and move to the next one
    at=prev;
  }
  return path;
}
