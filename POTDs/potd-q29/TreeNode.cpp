#include "TreeNode.h"
#include <iostream>
TreeNode*& findNode(TreeNode*& r, int key){
  if (r==NULL) return r;
  if (r->val_==key) return r;
  TreeNode*& ret1=findNode(r->left_,key),*&ret2=findNode(r->right_,key);
  if (ret1==NULL) return ret2;
  else return ret1; //assumes delete node is actually a node in the tree
}
TreeNode*& _ios(TreeNode*& r){
  if (r->left_==NULL) return r;
  return _ios(r->left_);
}
TreeNode * deleteNode(TreeNode* root, int key) {
  // your code here
  //first find node

  TreeNode*& node=findNode(root,key);
  if(node==NULL) return root;
  // if(root->val_!=key){
  //   deleteNode(root->left_);
  //   deleteNode(root->right_);
  // }else{
    //case no child;
    if(node->left_==NULL && node->right_==NULL){
      delete node;
      node=NULL;
    } else if(node->left_==NULL){ //one child remove
      TreeNode*temp=node->right_;
      delete node;
      node=temp;
    } else if(node->right_==NULL){ //one child remove
      TreeNode* temp=node->left_;
      delete node;
      node=temp;
    }else{//two child remove
      std::cout<<"In 2child rem on "<<node->val_<<"\n";
      inorderPrint(root);std::cout<<"\n";
      std::cout<<"Node's Right: "<<node->right_->val_<<"\n";

      TreeNode*& ios=_ios(node->right_);
      std::cout<<"Node's Right: "<<node->right_->val_<<"\n";

      // while(ios->left_!=NULL){
      //   ios=ios->left_;
      // }
      // TreeNode* tempR,*tempL;
      // tempR=ios->right_;
      // tempL=ios->left_;
      // if(node->right_->val_==ios->val_){//special case when you happen to be swapping on right next to another
      //   ios->right_=node;
      // }else{
      //   ios->right_=node->right_;
      // }
      // ios->left_=node->left_;
      // node->right_=tempR;
      // node->left_=tempL;
      //
      //  TreeNode*& temp=node,*&temp2=ios;
      //  node=temp2;
      //  ios=temp;
      std::cout<<"Root is "<<root->val_<<"\n";
      std::cout<<"Root is still"<<root->val_<<"\n";
      inorderPrint(node);std::cout<<"\n";
      std::cout<<"Node's Right: "<<node->right_->val_<<"\n";

      std::cout<<"ios is "<<ios->val_<<" \n";
      int temp=ios->val_;
      ios->val_=node->val_;
      std::cout<<"Node's Right: "<<node->right_->val_<<"\n";

      node->val_=temp;
      std::cout<<"Node's Right: "<<node->right_->val_<<"\n";

      std::cout<<"now ios is "<<ios->val_<<" \n";
      std::cout<<"now node is "<<node->val_<<" \n";
      std::cout<<"Root is still"<<root->val_<<"\n";
      inorderPrint(node);std::cout<<"\n";


  //    deleteNode(ios,key);
//      ios=NULL;

      if(ios->left_==NULL && ios->right_==NULL){
        std::cout<<"doing two child remove! \n";
        delete ios;
        ios=NULL;
      } else if(ios->left_==NULL){ //one child remove
        TreeNode*temp=ios->right_;
        delete ios;
        ios=temp;
      } else if(ios->right_==NULL){ //one child remove
        TreeNode* temp=ios->left_;
        delete ios;
        ios=temp;
      }

      std::cout<<"after: \n";
      inorderPrint(root);std::cout<<"\n";
    }
//  }



  return root;
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
