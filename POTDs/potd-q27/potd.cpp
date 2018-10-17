// Your code here
#include "potd.h"
string getFortune(const string &s){
  string fort[7]={"Congrats","You loose","derp","omg lol",
"oooyaa boingaaa", "YOU WIN A MILLION DOLLARS", "NO, of course not"};
  return fort[s.length()%7];
}
