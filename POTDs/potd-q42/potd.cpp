#include <unordered_map>

using namespace std;

unordered_map<string, int> common_elems(unordered_map<string, int> &mapA,
                                        unordered_map<string, int> &mapB) {

    // your code here
    unordered_map<string,int> ans;
    // unordered_map<string, int>::Iterator
    auto Bend=mapB.end();
    for (auto A : mapA){//for somereason auto A makes it return an actual pair (not an iterator that you have to derefence to get the pair)
      cout<<"At: "<<A.first<<" "<<A.second<<endl;

       auto B=mapB.find(A.first);
      if (B!=Bend) {
        cout<<"YES IN B! "<<B->first<<" "<<B->second<<endl;

        int sum=B->second+A.second;
        ans.insert({{A.first,sum}});
        cout<<"Erasing from B "<<A.first<<endl;
         mapB.erase(A.first);
      }
    }
    for(auto er:ans){
      cout<<"Now going through ans and erasing from a: "<<er.first<<" "<<er.second<<endl;
      mapA.erase((ans.find(er.first))->first);
    }

    return ans;
}
