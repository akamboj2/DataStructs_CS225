#include "Node.h"
//#include <iostream>
using namespace std;

Node *listUnion(Node *first, Node *second) {
  // your code here
  Node* u;
  if (first!=nullptr)
    u=new Node(*first);
  else if (second!=nullptr)
    u=new Node(*second);
  else
    return nullptr;

  u->next_=NULL;
  //first=first->next_;
  Node* at;
  while(first!=NULL){//go through first list
    bool in = (u->data_==first->data_ ?true:false);
    //cout<<"Checking"<<first->data_<<"\n";
    for(at=u;at!=NULL;at=at->next_) {//check if piece of data is in union yet
      if (first->data_==at->data_) {in =true; break;}
    }
    if(!in){//if it's not in the union list yet add it
      //cout<<"it's not in the union see: ";
      //at=u;
      ////cout<<at->data_<<" "<<(at->next_==NULL)<<endl;
      /*while(at!=NULL){
        //cout<<at->data_<<" ";
        at=at->next_;
      }*/
      for(at=u;at->next_!=NULL;at=at->next_) {
        //cout<<"( are we at null"<<(at->next_==NULL)<<" )";
        //cout<<at->data_<<" ";//go to end of list
      }
      //cout<<at->data_;
      //cout<<"\n";
      at->next_=new Node;
      at->next_->data_=first->data_;
      //cout<<"Just added first->data_ "<< first->data_<<"to "<< at->data_<<"\n";
      at->next_->next_=NULL;
      //cout<<at->data_<<" "<<at->next_->data_<<endl;
      //cout<<"added: ";
      for(at=u;at!=NULL;at=at->next_) ;//cout<<at->data_<<" ";//go to end of list
      //cout<<endl;
    }
    first=first->next_;
  }
  while(second!=NULL){//go through first list
    bool in = (u->data_==second->data_ ?true:false);
    //cout<<"Checking"<<second->data_<<"\n";
    for(at=u;at!=NULL;at=at->next_) {//check if piece of data is in union yet
      if (second->data_==at->data_) {in =true; break;}
    }
    if(!in){//if it's not in the union list yet add it
      //cout<<"it's not in the union see: ";
      //at=u;
      ////cout<<at->data_<<" "<<(at->next_==NULL)<<endl;
      /*while(at!=NULL){
        //cout<<at->data_<<" ";
        at=at->next_;
      }*/
      for(at=u;at->next_!=NULL;at=at->next_) {
        //cout<<"( are we at null"<<(at->next_==NULL)<<" )";
        //cout<<at->data_<<" ";//go to end of list
      }
      //cout<<at->data_;
      //cout<<"\n";
      at->next_=new Node;
      at->next_->data_=second->data_;
      //cout<<"Just added first->data_ "<< second->data_<<"to "<< at->data_<<"\n";
      at->next_->next_=NULL;
      //cout<<at->data_<<" "<<at->next_->data_<<endl;
      //cout<<"added: ";
      for(at=u;at!=NULL;at=at->next_) ;//cout<<at->data_<<" ";//go to end of list
      //cout<<endl;
    }
    second=second->next_;
  }


  return u;
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
