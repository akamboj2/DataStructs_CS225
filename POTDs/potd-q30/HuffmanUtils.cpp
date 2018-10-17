#include "HuffmanNode.h"
#include "HuffmanUtils.h"
#include <string>

using std::string;

/**
 * binaryToString
 *
 * Write a function that takes in the root to a huffman tree
 * and a binary string.
 *
 * Remember 0s in the string mean left_ and 1s mean right_.
 */

string binaryToString(string binaryString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    string s="";
    HuffmanNode* at;
    for (char& c: binaryString) {
      at=huffmanTree;
      while(at!=NULL){
        if(c=='0') at=at->left_;
        else at=at->right_;
      }
      s+=at->char_;
    }
    return s;
}

/**
 * stringToBinary
 *
 * Write a function that takes in the root to a huffman tree
 * and a character string. Return the binary representation of the string
 * using the huffman tree.
 *
 * Remember 0s in the binary string mean left_ and 1s mean right_
 */
bool isChar(char c, HuffmanNode* r){
  if (r->char_=='0'){//meaning internal node
    return (isChar(c,r->left_) || isChar(c,r->right_));//final thing
  }else{
    return c==r->char_;//return true if at correct character
  }
}
void trav(string & s, char c, HuffmanNode* r){

  if (r->left_!=NULL && isChar(c,r->left_)){
    s+="0";
    trav(s,c,r->left_);
  }else if(r->right_!=NULL && isChar(c,r->right_)){
    s+="1";
    trav(s,c,r->right_);
  }
}

string stringToBinary(string charString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    string ans="";
    for(char& c:charString){
      trav(ans,c,huffmanTree);
    }
    return ans;
}
