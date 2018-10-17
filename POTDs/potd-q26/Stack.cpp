#include "Stack.h"

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
  return size_;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
  if(at_==NULL) return true;
  return false;
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
  item* next = new item(value);
  next->prev=at_;
  at_=next;
  size_++;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
  int ret=at_->data;
  item* del = at_;
  at_=at_->prev;
  delete del;
  size_--;
  return ret;
}
