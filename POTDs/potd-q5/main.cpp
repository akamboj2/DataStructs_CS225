// your code here
#include "q5.h"
#include "Food.h"
#include<iostream>



int main(){
  Food f;
  f.set_quantity(5);
  std::cout<<"You have "<<f.get_quantity()<<" apples."<<std::endl;
  increase_quantity(&f);
  std::cout<<"You have "<<f.get_quantity()<<" apples."<<std::endl;

}
