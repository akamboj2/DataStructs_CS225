// Pet.h
#pragma once
#include <string>
#include "Animal.h"
using namespace std;

class Pet : public Animal{
    private:
        string owner_name_;
        string name_;
    public:
        Pet();
        Pet(string type, string food, string n, string on) ;
        void setOwnerName(string n);
        string getOwnerName();
        void setFood(string nu_food);
        string getFood();
        void setName(string n);
        string getName();
        string print();
};
