#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include <unordered_map>
using std::make_pair;
#include <vector>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  std::list<edgeListIter> adj = adjList.at(v.key_);
  return adj.size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  // vertexMap
  std::pair<std::string, V&> new_vertex(key, v);
  vertexMap.insert(new_vertex);
  //vertexMap.insert(std::make_pair<std::string, V&>(key, v));
  // // adjList
  std::list<edgeListIter> new_list;
  std::pair<std::string, std::list<edgeListIter>> new_vertex_2(key, new_list);
  adjList.insert(new_vertex_2);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2

  // E edge = *(adjList.at(key));
  // std::vector<V> vertices;
  //
  // for(size_t i = 0; i < vertices.size(); i++){
  //   std::list<edgeListIter> adj = adjList.at(vertices[i].key());
  //   //std::list<edgeListIter> adj = adjList[vertices[i]];
  //   typename std::list<edgeListIter>::iterator it_adj = adj.begin();
  //   for(it_adj = adj.begin(); it_adj != adj.end(); it_adj++){
  //     if((*(*it_adj)).get().source() == vertices[i] || (*(*it_adj)).get().dest() == vertices[i]){
  //       adj.remove(*it_adj);
  //     }
  //   }
  // }


  // loop through adjList and call remove edge

  // std::unordered_map<std::string, std::list<edgeListIter>> adjList;
  std::list<edgeListIter> adj = adjList.at(key);
  typename std::list<edgeListIter>::iterator it_adj = adj.begin();
  for(it_adj = adj.begin(); it_adj != adj.end(); it_adj++){
    // if((*(*it_adj)).get().source() == vertices[i] || (*(*it_adj)).get().dest() == vertices[i]){
    //   adj.remove(*it_adj);
    // }
    removeEdge((*(*it_adj)).get().source(), (*(*it_adj)).get().dest());
  }


  // std::list<E_byRef> edgeList;
  // typename std::list<E_byRef>::iterator it_list = edgeList.begin();
  // while(it_list != edgeList.end()){
  //   // if((*it_list).source_ == vertexMap.at(key)){
  //   if((*it_list).get().source() == vertexMap.at(key)){
  //     // vertices.push_back((*it_list).dest_);
  //     vertices.push_back((*it_list).get().dest());
  //     edgeList.erase(it_list);
  //     break;
  //   // } else if((*it_list).dest_ == vertexMap.at(key)){
  //   } else if((*it_list).get().dest() == vertexMap.at(key)){
  //     // vertices.push_back((*it_list).source_);
  //     vertices.push_back((*it_list).get().source());
  //     edgeList.erase(it_list);
  //     break;
  //   } else {
  //     it_list++;
  //   }
  // }

  adjList.erase(key);

  // std::unordered_map<std::string, V &> vertexMap;
  vertexMap.erase(key);


}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));

  // std::list<E_byRef> edgeList;
  edgeList.push_front(e);

  // std::unordered_map<std::string, std::list<edgeListIter>> adjList;
  edgeListIter it = edgeList.begin();
  (adjList.at(v1.key())).push_back(it);
  (adjList.at(v2.key())).push_back(it);

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  edgeListIter toRemove=edgeList.end();//this is the edge we will remove
  for(edgeListIter it = edgeList.begin();it!=edgeList.end();it++){ //go through list of edges
    if (((*it).get().source().key()==key1 && (*it).get().dest().key()==key2) || ((*it).get().source().key()==key2 && (*it).get().dest().key()==key1)){
      toRemove=it;//if an edge lines up with the key store it
    }
  }
  if(toRemove!=edgeList.end()){
    removeEdge(toRemove);
    edgeList.erase(toRemove);
  }

}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  //find vertices with this edge;
  V source=(*it).get().source(),dest=(*it).get().dest();
  //then look it up in adjList
  std::list<edgeListIter>& list_src = adjList.at(source.key()), &list_dest=adjList.at(dest.key());

  //http://www.cplusplus.com/reference/list/list/remove/
  list_src.remove(it);
  list_dest.remove(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  std::list<edgeListIter> list=adjList.at(key); //make a list of incident edges
  for(auto e : list){
    edges.push_front(*e);//go through each and add it to new list
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  std::list<edgeListIter> list=adjList.at(key1);
  // for(edgeListIter it = list.front();list.size()>0;list.pop_front()){
  //     if(it->dest().key()==key2) return true;
  // }

  for(typename std::list<edgeListIter>::iterator it = list.begin();it!=list.end();it++){ //go through all key1's adjacent edges
    if((*(*it)).get().dest()==key2 && (*(*it)).get().source()==key1) return true; //if one of those edges destination is key2...they're adjacent!
    //it could also be undirected so src and dest flipped
    if((!(*(*it)).get().directed()) && (*(*it)).get().dest()==key1 && (*(*it)).get().source()==key2) return true;
  }
   return false;//otherwise they're not adjacent
}
