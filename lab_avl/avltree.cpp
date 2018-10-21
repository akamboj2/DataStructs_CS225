/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* oldt=t;
    t=t->right;//t is now the new t
    oldt->right=t->left;
    t->left=oldt;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* oldt=t;
    t=t->left;
    oldt->left=t->right;
    t->right=oldt;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //if tree was balanced before and you add one. you're only going to have to do one rotation if any.
    //and that will be at the subtree root.
    //lets calculate balance factor.
    updateHeight(root);
    if(subtree==NULL) return;
    int balance = h(subtree->right) - h(subtree->left);
    //instead of     int balance = subtree->right->height - subtree->left->height;
    //bc right left could be null

    if(balance==-2){//left heavy
      //need to call h funciton instead of subtree->left->left->height, incase the left left is null!
      int bleft= h(subtree->left->right)-h(subtree->left->left);
      if(bleft<=-1){//then we got a stick on the left
        rotateRight(subtree);
      }else if (bleft>=1){
        rotateLeftRight(subtree);
      }
    }else if(balance==2){
      int bright=h(subtree->right->right)-h(subtree->right->left);
      if (bright<=-1){
        rotateRightLeft(subtree);
      }else if(bright>=1){
        rotateLeft(subtree);
      }
    }
    updateHeight(root);
}

template <class K, class V>
void AVLTree<K,V>::updateHeight(Node* r){
  if(r!=NULL){//if r is NULL just return from function
    r->height= h(r);
    updateHeight(r->left);
    updateHeight(r->right);
  }
}
template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    //just like inserting into normal bst just make sure it's balanced afterwards
    if(subtree==NULL){//base case
      subtree= new Node(key,value);
    }else{
      if(key>subtree->key) insert(subtree->right,key,value);
      else insert(subtree->left,key,value);
    }
    rebalance(subtree);
    //this will rebalance from the lowest point of inbalance (bc its going backwards up the tree)
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
//            cout<<"No child remove: \n";
            delete subtree;
            subtree=NULL;
            //cout<<"priting again\n";
            //print();
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
  //          cout<<"2 child remove!\n";
            Node*& iop=findIoP(subtree->left);
  //          cout<<"iop is "<<iop<<" "<<iop->key<<"\n";
            swap(iop,subtree);
  //          cout<<"swaped it with "<<iop->key<<"\n";
            delete iop;
            iop=NULL;
        } else {
            /* one-child remove */
            // your code here
            if(subtree->left!=NULL){
              Node* temp = subtree;
              subtree=subtree->left;
              delete temp;
            }
            if(subtree->right!=NULL){
              Node* temp=subtree;
              subtree=subtree->right;
              delete temp;
            }
        }
        // your code here
        rebalance(subtree);

    }
    rebalance(subtree);

}

template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K, V>::findIoP(Node*& r){//assum we're given the left subtree to start
//so go all the way right
  if (r->right==NULL) return r;
  else return findIoP(r->right);
}
