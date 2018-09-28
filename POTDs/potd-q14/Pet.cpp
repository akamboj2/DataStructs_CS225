// Pet.cpp
#include "Pet.h"
using namespace std;

string Pet::print() {
    return "My name is "+name_;
};

Pet::Pet() : Animal(), owner_name_("Cinda"),name_("Fluffy") { }

Pet::Pet(string type, string food, string n, string on) : Animal(type,food),  owner_name_(on), name_(n) { }

void Pet::setOwnerName(string n){
  owner_name_=n;
}
string Pet::getOwnerName(){
  return owner_name_;
}
void Pet::setFood(string nu_food){
  food_=nu_food;
}
string Pet::getFood(){
  return food_;
}
void Pet::setName(string n){
  name_=n;
}
string Pet::getName(){
  return name_;
}
