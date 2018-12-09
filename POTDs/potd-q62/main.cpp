#include <iostream>

using namespace std;

#include "beiju.cpp"

int main() {

    while (! cin.eof()) {
        string s;
        getline(cin,s);
        //cout<<s<<endl;
        cout << beiju(s) << endl;
    }
}
