#include "Node.h"
#include <iostream>
using namespace std;



void mergeList(Node *first, Node *second) {
  // your code here!
  if (first==NULL) {first=second; return;};
  if (second==NULL) {second=first; return;};
  Node* at= first;
  Node* cpy1= first->next_, *cpy2=second->next_;
  at->next_=second;
  at=at->next_;
  //std::cout<<"here?\n";
  while(true){
    //cout<<"starte of while: ";
    //printList(first);
    if (cpy1==NULL) break;
    at->next_=cpy1;
    //if (at->next==NULL) break;
    //if (cpy1!=NULL)
    cpy1=cpy1->next_;
    at=at->next_;
    if (cpy2==NULL) break;
    at->next_=cpy2;
    //if (cpy2!=NULL)
    cpy2=cpy2->next_;
    at=at->next_;
  }

}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
