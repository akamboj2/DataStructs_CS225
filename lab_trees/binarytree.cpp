/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    return mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * r){
  if (r==NULL) return;
  mirror(r->left);
  mirror(r->right);
  Node* temp = r->left;
  r->left=r->right;
  r->right=temp;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
//  cout<<"CALLED isOrderedIterative()\n";
    // your code here
    stack<Node*> trav, ordered;

    for(Node* at = root; at!=NULL;at=at->left){//initialize stack for inorder traversal
      trav.push(at);
    }
    Node* curr;
    while(!trav.empty()){
      curr=trav.top();//remove first node
      trav.pop();
      ordered.push(curr);
      if (curr->right!=NULL){//then add its right and right's lefts if needed
        trav.push(curr->right);
        for(Node* i =curr->right->left;i!=NULL;i=i->left) trav.push(i);
      }
    }
    //note this prints the exact opposite of inorder traversal (bc we pushing it on a stack FIFO)
    Node*at=ordered.top();
    bool ret=true;
    while(!ordered.empty()){
      //since our stack is backwards check that every next element on stack is less than
      //what you are at
  //    cout<<ordered.top()->elem<<" ";
      ordered.pop();
      if(!ordered.empty()){
        if (at->elem<ordered.top()->elem) {
          //cout<<at->elem<<" is less than "<< ordered.top()->elem<<" so false!\n";
          return false;
        }//else{ cout<<at->elem<<" > "<<ordered.top()->elem<<"\n";}
        at=ordered.top();
      }
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrd(root);
}

template <typename T>
bool BinaryTree<T>::isOrd(Node* r) const{
  if (r->left==NULL && r->right==NULL){//base case
    return true;
  }
  if(r->left==NULL)
    return (r->right->elem>r->elem && isOrd(r->right));
  if(r->right==NULL)
    return (r->left->elem<r->elem && isOrd(r->left));

  //recursive step
  return (r->right->elem>r->elem && r->left->elem<r->elem && isOrd(r->left) && isOrd(r->right));
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> start;
    paths.push_back(start);//need to make sure paths isn't empy otherwise line 191 first push_back is a segfault
    path(root,paths);
}

template <typename T>
void BinaryTree<T>::path(Node* r, vector<vector<T>> &paths) const{
  if (r->left==NULL &&r->right==NULL){//right and left are null just push the element and return
    paths.back().push_back(r->elem);
    return; //base case
  }

  paths.back().push_back(r->elem);
  vector<T> copy = paths.back();
  if(r->left==NULL){ //if left is NULL (and right can't also equal null bc of base case check)
    path(r->right,paths);//just go add the right paths
  }else{
    path(r->left,paths);//if left is not null. first add left paths
    if(r->right!=NULL){//then add right paths
      paths.push_back(copy);//but need to push a new path onto array of paths
      path(r->right,paths);
    }
  }



}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumD(root,0);
}

template <typename T>
int BinaryTree<T>::sumD(Node* r, int d) const{
  if (r==NULL) return 0; //base case
//  if(r->left==NULL) return sumD(r->right,d+1)+d;
//  if(r->right==NULL) return sumD(r->left,d+1)+d;

  return sumD(r->right,d+1)+sumD(r->left,d+1)+d;

}
