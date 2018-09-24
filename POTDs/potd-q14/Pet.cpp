// Pet.cpp
sing namespace std;

void Pet::setFood(string nu_food) {
    food_ = nu_food;
}

string Pet::getFood() {
    return food_;
}

void Pet::setType(string nu_type) {
    type_ = nu_type;
}

string Pet::getType() {
    return type_;
}

string Pet::print() {
    return "I am a " + type_;
};

Pet::Pet() : type_("cat"), food_("fish") { }

Pet::Pet(string type, string food) : type_(type), food_(food) { }
