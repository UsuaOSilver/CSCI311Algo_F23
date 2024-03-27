// AVLTree.cpp
// Author: 


#include <iostream>
#include <limits.h>
#include "AVLTree.h"
using namespace std;

// Function declaration
int getHeight(std::shared_ptr<AVLNode>);
int getBalanceFactor(std::shared_ptr<AVLNode>);
void updateHeight(shared_ptr<AVLNode>);

//do not change anything in the above
//implement the following methods, starting here

AVLTree::AVLTree() : root(nullptr), size(0) {}

std::shared_ptr<AVLNode> AVLTree::getRoot(){
  return root;
}

int AVLTree::getSize(){
  return size;
}

std::shared_ptr<AVLNode> AVLTree::search(int val){
  return search(root, val);
}

std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val){
     if (!n || n->value == val) {
          return n;
     }
     else if (val < n->value) {
          return search(n->left, val);
     }
     else {
          return search(n->right, val);
     }
}

std::shared_ptr<AVLNode> AVLTree::minimum(){
  return minimum(root);
}

std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n){
     if (!n) return n;
     while (n->left) {
          n = n->left;
     }
  return n;
}

std::shared_ptr<AVLNode> AVLTree::maximum(){
  return maximum(root);
}

std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n){
     if (!n) return n;
     while (n->right) {
          n = n->right;
     }
  return n;
}

void AVLTree::insertValue(int val){
     root = insertValue(root, val);
}

std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val){
     if (!n) {
          ++size;
          return std::make_shared<AVLNode>(val);
     }
     if (val < n->value) {
          n->left = insertValue(n->left, val);
     }
     else if (val > n->value) {
          n->right = insertValue(n->right, val);
     }
     else {
          return n;
     }
     return rebalance(n);
}

void AVLTree::deleteValue(int val){
     root = deleteValue(root, val);
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val){

     // Base case: key is not found or tree only has 1 node
     if (!n) return n;

     if (val < n->value) {
          n->left = deleteValue(n->left, val);
     }
     else if (val > n->value) {
          n->right = deleteValue(n->right, val);
     }
     else {
          // Case: node with 1 child or no child
          if (!n->left || !n->right) {

               std::shared_ptr<AVLNode> temp = n->left ? n->left : n->right;

               // Case: No child
               if (!temp) {
                    temp = n;
                    n = nullptr;
               }
               // Case: 1 child
               else {
                    *n = *temp;
               }
          }
          // Case: node with 2 children
          else {
               std::shared_ptr<AVLNode> temp = minimum(n->right); // Get minimum of right subtree
               n->value = temp->value; // Copy the data of the above to this node
               n->right = deleteValue(n->right, temp->value); // Delete that minimum node
          }
     }

     // Rebalance the tree
     return rebalance(n);
}

std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n){
     if (!n) return n;
     updateHeight(n);
     int balance = getBalanceFactor(n);

     // Left heavy
     if (balance < -1) {
          if (getBalanceFactor(n->left) > 0) {
               // Case: Left-Right
               return rotateLeftRight(n);
          }
          // Case: Left-Left
          return rotateRight(n);
     }

     // Right heavy
     if (balance > 1) {
          if (getBalanceFactor(n->right) < 0) {
               // Case: Right-Left
               return rotateRightLeft(n);
          }
          // Case: Right-Right
          return rotateLeft(n);
     }

     // Node is balanced
     return n;
}


//==== Rotation ================================================================================
//
//==============================================================================================
std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n){
     auto rightChild = n->right;
     n->right = rightChild->left;
     rightChild->left = n;
     updateHeight(n);
     updateHeight(rightChild);
  return rightChild;
}

std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n){
     auto leftChild = n->left;
     n->left = leftChild->right;
     leftChild->right = n;
     updateHeight(n);
     updateHeight(leftChild);
  return leftChild;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n){
     n->left = rotateLeft(n->left);
  return rotateRight(n);
}

std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n){
     n->right = rotateRight(n->right);
  return rotateLeft(n);
}


//==== Traversal ===============================================================================
//
//==============================================================================================
void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
     if (n) {
          order.push_back(n);
          preOrder(n->left, order);
          preOrder(n->right, order);
     }
}

void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
     if (n) {
          inOrder(n->left, order);
          order.push_back(n);
          inOrder(n->right, order);
     }
}

void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
     if (n) {
          postOrder(n->left, order);
          postOrder(n->right, order);
          order.push_back(n);
     }
}


//===== Helper functions =======================================================================
//
//==============================================================================================
int getHeight(std::shared_ptr<AVLNode> n) {
     if (!n) return -1; //Base case
     return n->height;
}

int getBalanceFactor(std::shared_ptr<AVLNode> n) {
     if (!n) return 0;
     return getHeight(n->right) - getHeight(n->left);
}

void updateHeight(shared_ptr<AVLNode> n) {
     if (!n) return;
     int leftHeight = getHeight(n->left);
     int rightHeight = getHeight(n->right);
     n->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}