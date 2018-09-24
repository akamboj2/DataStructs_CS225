// your code here
#include "Bar.h"
using namespace potd;

Bar::Bar(std::string name){
  f_ = new Foo(name);
}
Bar::Bar(const Bar & other){
  f_=new Foo(other.get_name());
}
Bar & Bar::operator=(const Bar & other){
  delete f_;
  f_=new Foo(other.get_name());
  return *this;
}
Bar::~Bar(){
  delete f_;
}
std::string Bar::get_name()const{
  return f_->get_name();
}
