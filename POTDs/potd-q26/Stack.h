#ifndef _STACK_H
#define _STACK_H

#include <cstddef>

class Stack {
public:
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
  Stack() : size_(0){at_ = NULL;}
  ~Stack(){
    while(at_!=NULL){ item* del = at_;
    at_=at_->prev;
    delete del;}
    }
private:
  int size_;
  struct item{
    int data;
    item* prev;
    item() : prev(NULL){}
    item(int val) : data(val),prev(NULL){}
  };
  item* at_;
};

#endif
