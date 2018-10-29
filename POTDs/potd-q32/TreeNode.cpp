#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

int h(TreeNode* r){//returns height from node r
  if (r==NULL) return -1;
  return 1+max(h(r->left_),h(r->right_));
}

TreeNode* checkBal(TreeNode* r){
  int balL, balR;
  if(abs(h(r->right_)-h(r->left_))==2) return r;
  balL=abs(h(r->left_->right_)-h(r->left_->left_));
  balR=abs(h(r->right_->right_)-h(r->right_->left_));
  if (balL==2) return r->left_;
  if (balR==2) return r->right_;
  if (balL>balR){
    return checkBal(r->left_);
  }else{
    return checkBal(r->right_);
  }
  // bool bal= (h(r->right_)-h(r->left_)>1 ? false:true);
  // if (bal) return r;
  // if (!bal){
  //   if(h(r->right_)<h(r->left_)){
  //     return checkBal(r->left_);
  //   }else{
  //     return checkBal(r->right_);
  //   }
  // }
}
TreeNode* findLastUnbalanced(TreeNode* root) {
  // your code here
//  bool rightbal,leftbal;
  if (abs(h(root->right_)-h(root->left_))>1) return root;
  else{
    return checkBal(root);
  }

  // Treenode* ret1,ret2;
  //
  // if(!rightbal){
  //   ret1=findLastUnbalanced(root->right_);
  // }
  // if(!leftbal){
  //   ret2=findLastUnbalanced(root->left_);
  // }
  //
  // if(rightbal && leftbal) return root;
  //


  //check if this node is unbalanced and return it's lowest unbalanced if so, if balanced then return null
  // if(h(root->left)>1+h(root->rigth)){
  //
  // }
  // //check if left unbalanced and right unbalanced then return the lowest of them
  // return NULL;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
