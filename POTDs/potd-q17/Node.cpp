#include "Node.h"

using namespace std;

void sortList(Node **head) {
  // your code here!
  Node* sorted;
  Node* h= *head;
  Node* curr=h;
  Node* max=curr;//initialize max to first node;
  while(h->next!=null){
    while (curr->next!=NULL){
      if (curr->data_>max->data_){//check if larger
        max=curr;//if it is larger take store it in max
      }
      curr=curr->next_;
    }
    //once you find max; remove it from head and add it to sorted
    Node*i=h;
    while(i->next!=max){ i=i->next_;}//ends when i->next is the max
    i->next_=max->next_;
    sorted->next_=max;
    max=h->next_;
  }

  //at the end make sure you return the correct head
  *h=sorted;//becacuse h is *head now we put sorted memory address in that memory address
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
