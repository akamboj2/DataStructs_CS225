
vector<string> NoProblem(int start, vector<int> created, vector<int> needed) {
  int probs=start;
  vector<string> s;
  // your code here
  for (unsigned i=0;i<created.size();i++){
    if(needed[i]<=probs){
      s.push_back("No problem! :D");
      probs-=needed[i];
    }else{
      s.push_back("No problem. :(");
    }
    probs+=created[i];
  }
  return s;
}
