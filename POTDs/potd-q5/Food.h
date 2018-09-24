// Your code here
#pragma once
#include <string>
class Food{
public:
  std::string get_name(){
    return name;
  }
  void set_name(std::string s){
    name=s;
  }
  void set_quantity(int q){
    quant=q;
  }
  int get_quantity(){
    return quant;
  }
private:
  int quant;
  std::string name;
};
