#include <string>
#include <stack>

using namespace std;

bool isValid(string input) {
    stack<char> st;
    for (unsigned x=0;x<input.length();x++){
      if (input[x]=='[' || input[x]=='(' ||input[x]=='{' ) st.push(input[x]);
      if(input[x]==']'){
        if (!st.empty() && st.top()=='[') st.pop();
        else return false;
      }
      if(input[x]=='}'){
        if (!st.empty() && st.top()=='{') st.pop();
        else return false;
      }
      if(input[x]==')'){
        if (!st.empty() && st.top()=='(') st.pop();
        else return false;
      }

    }
    if (st.empty())
      return true;    // modify this!
    else
      return false;
}
