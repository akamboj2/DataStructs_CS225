// Pet.h
#pragma once
#include <string>

using namespace std;

class Pet {
    private:
        string type_;
        string owner_name;
        string name;
    protected:
        string food_;
    public:
        Pet();
        Pet(string type, string food);

        void setFood(string nu_food);
        string getFood();
        void setType(string nu_type);
        string getType();
        string print();
};
