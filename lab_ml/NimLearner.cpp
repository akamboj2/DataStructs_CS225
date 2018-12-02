/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
  for (unsigned i=0;i<=startingTokens;i++){//go through and add al veritices
    g_.insertVertex("p1-"+std::to_string(i));
    g_.insertVertex("p2-"+std::to_string(i));
  }
  for (unsigned i=startingTokens;i>0;i--){//go backwards from the amount of startingTokens
    //add the edge if player takes 1
    g_.insertEdge("p1-"+std::to_string(i),"p2-"+std::to_string(i-1));
    g_.setEdgeWeight("p1-"+std::to_string(i),"p2-"+std::to_string(i-1),0);
    g_.insertEdge("p2-"+std::to_string(i),"p1-"+std::to_string(i-1));
    g_.setEdgeWeight("p2-"+std::to_string(i),"p1-"+std::to_string(i-1),0);
    if(i!=1) {//if your not at the last token add the edge for if the player takes more than one
      g_.insertEdge("p1-"+std::to_string(i),"p2-"+std::to_string(i-2));
      g_.setEdgeWeight("p1-"+std::to_string(i),"p2-"+std::to_string(i-2),0);
      g_.insertEdge("p2-"+std::to_string(i),"p1-"+std::to_string(i-2));
      g_.setEdgeWeight("p2-"+std::to_string(i),"p1-"+std::to_string(i-2),0);
    }
  }
  startingVertex_="p1-"+std::to_string(startingTokens);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 Vertex at=startingVertex_,next;
 int tokens=std::stoi(at.substr(3,string::npos));
 while(at!="p1-0" && at!="p2-0"){
   int r=rand()%2+1;
   tokens=(tokens-r>=0?tokens-r:0);
   //std::cout<<"at= "<<at<<" player: "<<stoi(at[1])<<"\n"; <--doesn't work
   next = ((std::stoi(at.substr(1,1))-1)? "p1-"+std::to_string(tokens):"p2-"+std::to_string(tokens));
   path.push_back(g_.getEdge(at,next));
   at=next;
 }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 //Edge win1_1("p1-1","p2-0"), win1_2("p2-1","p1-0");

 //int add =(path.back()==win1? 1:-1);
//  cout<<std::endl;
 for (auto p :path){
   //cout<<"at p "<<p.source<<","<<p.dest<<" back is "<<path.back().source<<","<<path.back().dest<<'\n';
   if(path.back().dest=="p2-0"){
  //   cout<<"1 won "<<p.source.substr(1,1)+" current weight:"<<g_.getEdgeWeight(p.source,p.dest)<<"\n";
     if (std::stoi(p.source.substr(1,1))==1){//reward p1 for winning
  //     cout<<"\tNow 1 is being rewarded"<<"\n";
       g_.setEdgeWeight(p.source,p.dest,g_.getEdgeWeight(p.source,p.dest)+1);
     }else{//dock p2
//       cout<<"\tNow 2 is being docked"<<"\n";
       g_.setEdgeWeight(p.source,p.dest,g_.getEdgeWeight(p.source,p.dest)-1);
     }
   }else{
//     cout<<"2 won."<<p.source.substr(1,1)+" "<<g_.getEdgeWeight(p.source,p.dest)<<"\n";
     if (std::stoi(p.source.substr(1,1))==1){//if p1 lost... dock p1 points
//       cout<<"\tNow 1 is being docked"<<"\n";
       g_.setEdgeWeight(p.source,p.dest,g_.getEdgeWeight(p.source,p.dest)-1);
     }else{//reward p2
//       cout<<"\tNow 2 is being rewarded"<<"\n";
       g_.setEdgeWeight(p.source,p.dest,g_.getEdgeWeight(p.source,p.dest)+1);
     }
  }
   }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
