#include "Node.h"

using namespace std;
#include<iostream>

Node *listSymmetricDifference(Node *first, Node *second) {
  // your code here
  //check every node in first list and see if that's in second or already in symmetric difference
  Node* rhead=NULL, *ret=rhead;
  for (Node* i=first;i!=NULL;i=i->next_){
    bool in=false;
    for (Node* i2=second;i2!=NULL;i2=i2->next_){
      if (i->data_==i2->data_) {in = true; break;}
    }
    for (Node* r=rhead;r!=NULL;r=r->next_){
      if (i->data_==r->data_) in = true;
    }
    if (!in){
      if (rhead==NULL){
      //  std::cout<<"allocating nodes;";
        ret = new Node(*i);//need a special case to not loose the head
        rhead=ret;
        ret->next_=NULL;
      }else{
      //  std::cout<<"allocating nodes;";

        ret->next_ = new Node(*i);
        ret=ret->next_;
        ret->next_=NULL;
      }
    }
  }
  for (Node* i=second;i!=NULL;i=i->next_){//same thing as set of loops except switch first and second
    bool in=false;
    for (Node* i2=first;i2!=NULL;i2=i2->next_){
      if (i->data_==i2->data_) in = true;
    }
    for (Node* r=rhead;r!=NULL;r=r->next_){
      if (i->data_==r->data_) in = true;
    }
    if (!in){
      if (rhead==NULL){
    //    std::cout<<"1allocating nodes;";

        ret = new Node(*i);
        rhead=ret;
        ret->next_=NULL;
      }else{
    //    std::cout<<"2allocating nodes;";

        ret->next_ = new Node(*i);
        ret=ret->next_;
        ret->next_=NULL;
      }
    }
  }
  return rhead;
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
