/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>
#include <math.h>
#include "kdtree.h"

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if(first[curDim]==second[curDim]){//in the case of a tie use point's operator<
      return first<second;
    }
    if(first[curDim] <= second[curDim]){
      return true;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double dist_target_potential = 0;
    double dist_target_currentBest = 0;

    for(unsigned i = 0; i < Dim; i++){
      dist_target_potential += pow((target[i] - potential[i]), 2);
      dist_target_currentBest += pow((target[i] - currentBest[i]), 2);
    }

    dist_target_potential = sqrt(dist_target_potential);
    dist_target_currentBest = sqrt(dist_target_currentBest);

    if(dist_target_potential==dist_target_currentBest){
      return potential<currentBest;
    }

    if(dist_target_potential < dist_target_currentBest){
      return true;
    }
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    //root = new KDTreeNode();
    vector<Point<Dim>> vec = newPoints;
    if(vec.empty() == true){
      root=NULL;
      return;
    }

    // int a = 0;
    // int b = 0;
//    std::cout << newPoints.size() << std::endl;
    helper(vec, 0, 0, vec.size() - 1, root);


}

template <int Dim>
void KDTree<Dim>::helper(vector<Point<Dim>>& vector, int dimension, int start, int end, KDTreeNode*& root_){

    // std::cout << "here1" << std::endl;
    if(end < start){
      return;
    }

    // std::cout << "here2" << std::endl;
    int median = (start + end) / 2;

    // std::cout << "here3" << std::endl;
    root_ = new KDTreeNode();

    // std::cout << "here4" << std::endl;
    root_->point = select(vector, start, end, median, dimension);

    // std::cout << "Dim: " << Dim << std::endl;
    // std::cout << "(dimension + 1) mod Dim: " << (dimension + 1) % Dim << std::endl;
    helper(vector, (dimension + 1) % Dim, start, median - 1, root_->left);
    helper(vector, (dimension + 1) % Dim, median + 1, end, root_->right);

}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, int k, int dimension){

  // std::cout << "size: " << list.size() << std::endl;
  // std::cout << "left: " << left << std::endl;
  // std::cout << "right: " << right << std::endl;
  //std::cout << "here5" << std::endl;
  if(left == right){
    //std::cout << "here5.5" << std::endl;
    return list[left];
//    std::cout << list[left] << std::endl;
  }

  // std::cout << "here6" << std::endl;
  int pivotIndex = k;
  pivotIndex = partition(list, left, right, pivotIndex, dimension);

  // std::cout << "here7" << std::endl;
  if(k == pivotIndex){
    return list[k];
  } else if(k < pivotIndex){
    return select(list, left, pivotIndex - 1, k, dimension);
  } else {
    return select(list, pivotIndex + 1, right, k, dimension);
  }
  // std::cout << "here8" << std::endl;

}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int dimension){

  // std::cout << "here9" << std::endl;
  Point<Dim> pivotValue = list[pivotIndex];

  // std::cout << "here10" << std::endl;
  // swap list[pivotIndex] and list[right]
  Point<Dim> temp = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = temp;

  int storeIndex = left;

  // std::cout << "here11" << std::endl;
  for(int i = left; i < right; i++){
    if(smallerDimVal(list[i], pivotValue, dimension)){
      // swap list[storeIndex] and list[i]
      temp = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = temp;
      storeIndex++;
    }
  }

  // std::cout << "here12" << std::endl;
  // list[right] and list[storeIndex]
  temp = list[storeIndex];
  list[storeIndex] = list[right];
  list[right] = temp;

  // std::cout << "here13" << std::endl;
  return storeIndex;

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

  //root = other.root;
  // root->point = other.root->point;
  // root->left = other.root->left;
  // root->right = other.root->right;
  root = copyNodes(other.root);
  size = other.size;
  //return *this;

}

template<int Dim> typename
KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyNodes(KDTreeNode* r){
  //copy root then copy left and right
  if (r==NULL) return NULL;
  KDTreeNode* node = new KDTree<Dim>::KDTreeNode(r->point);
  node->left= copyNodes(r->left);
  node->right= copyNodes(r->right);
  return node;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  // delete root;
  // root = NULL;
  //
  // root = rhs.root;
  // root->point = rhs.root->point;
  // root->left = rhs.root->left;
  // root->right = rhs.root->right;
  destroy(root);
  root = copyNodes(rhs.root);
  size = rhs.size;

  return *this;
}

template<int Dim>
void KDTree<Dim>::destroy(KDTreeNode* & r){
  //need to pass pointer by reference in order to set r=NULL at end;
  if(r==NULL) return;
  if (r->left!=NULL) destroy(r->left);
  if (r->right!=NULL) destroy (r->right);
  delete r;
  r=NULL;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  // if (root==NULL) return;
  // if (root->left!=NULL) delete root->left;
  // root->left = NULL;
  // if (root->right!=NULL) delete root->right;
  // root->right = NULL;
  // delete root;
  // root = NULL;


  destroy(root);

}

/*Returns the distance squared between two points
*/
template <int Dim>
double KDTree<Dim>::distSq(const Point<Dim>& p1, const Point<Dim>& p2) const{
  double sum=0;
  for (int i=0;i<Dim;i++){
    sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
  }
  return sum;
}

/*findNearestNeighbor's private helper function for recursively going through tree
parameters: target point to find, node that function is at, level that the function is at
returns: best point in tree
Note: it assumes node is not null
*/
template <int Dim>
Point<Dim> KDTree<Dim>::fNN(const Point<Dim>& target, KDTreeNode* node, unsigned level) const{
  //if your at leaf then return this node as the current closest neighbor
  if(node->left==NULL && node->right==NULL) return node->point;

  bool wentLeft=false; //to keep track of if we went left or right initially
  //first find like a BST
  Point<Dim> currBest = node->point;
  if(smallerDimVal(target,node->point,level%Dim)){
    //if target is less then node at splitting dimension go left
    //but also if your supposed to go left and left is NULL, you're at the closest you can get (depth wise)
    if (node->left==NULL) return node->point;
    currBest = fNN(target,node->left,level+1);
    wentLeft=true;
  }else{
    if (node->right==NULL) return node->point;
    currBest = fNN(target,node->right,level+1);
  }

  //when going back up tree, look at current node
  if (shouldReplace(target,currBest,node->point)){
    //if node's point is closer, make that current best
    currBest=node->point;
  }
  //but now we may also need to check the other subtree
  Point<Dim> otherBest;
  bool checked_other=false;
  double r = distSq(target,currBest);
  double dSqSplitDim = (node->point[level%Dim]-target[level%Dim])*(node->point[level%Dim]-target[level%Dim]);
  if (dSqSplitDim<r || (dSqSplitDim==r && node->point<currBest)){
    //if the dist squared of the splitting dimension at the point and target is less than the radius
    //between the currbest and target, their may be something on other side of node
    if(wentLeft){
      //go the opposite way you went from before
      if (node->right!=NULL){
        otherBest=fNN(target,node->right,level+1);
        checked_other=true;
      }
    }else{
      if (node->left!=NULL){
        otherBest=fNN(target,node->left,level+1);
        checked_other=true;
      }
    }
    //finally decide between the currentBest and the other from the subtree
    if (checked_other)
      currBest = (shouldReplace(target,currBest,otherBest) ? otherBest:currBest);
  }
  //you should be at the best point from everything below you now
  return currBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if (root==NULL) return Point<Dim>();
    return fNN(query,root,0);
}
