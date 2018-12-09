
string beiju(string input) {
  string ans="", bj="";
  bool inBj=false;
  for(unsigned i=0;i<input.length();i++){
    if(input[i]=='[') {
      inBj=true;
      ans=bj+ans;
      bj="";
    }
    else if(input[i]==']'){
      inBj=false;
      ans=bj+ans;
      bj="";
    }
    else if(inBj) bj+=input[i];
    else ans+= input[i];
  }
    return bj+ans;
}
