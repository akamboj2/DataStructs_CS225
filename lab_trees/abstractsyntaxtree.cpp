#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(typename BinaryTree<std::string>::Node* r) const{
  //base case: if right and left children are null just return value
  //must have either 0 or 2 chidren
  if (r->left==NULL && r->right==NULL) return stod(r->elem);
  if(r->elem=="+")
    return eval(r->left)+eval(r->right);
  if(r->elem=="-")
    return eval(r->left)-eval(r->right);
  if(r->elem=="*")
    return eval(r->left)*eval(r->right);
  if(r->elem=="/")
    return eval(r->left)/eval(r->right);
  return 0;
}
