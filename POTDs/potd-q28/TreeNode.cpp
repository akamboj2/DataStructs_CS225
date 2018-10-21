#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int h(TreeNode* r){
  if (r==NULL) return -1;
  return 1+max(h(r->left_),h(r->right_));
}
int TreeNode::getHeight() {
  return h(this);
}
