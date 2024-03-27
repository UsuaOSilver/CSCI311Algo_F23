// Lab 4 - BST.cpp
// Author: UsuaoSilver

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

BST::BST(){
}

BST::~BST(){}

std::shared_ptr<Node> BST::search(int target){ 
  return search(root, target); 
} 

std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target){

     // Base case
     if (n == NULL || n->value == target) return n;

     // Target greater than n's target
     if (n->value < target) return search(n->right, target);

     // Target smaller than n's target
     return search(n->left, target);
}

std::shared_ptr<Node> BST::minimum(){
  return minimum(root);
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){

     if (n == nullptr) {
          return nullptr;
     }

     while (n->left != nullptr) {
          n = n->left;
     }

  return n;
}

std::shared_ptr<Node> BST::maximum(){
  return maximum(root);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){

     if (n == nullptr) {
          return nullptr;
     }

     while (n->right != nullptr) {
          n = n->right;
     }

  return n;
}

void BST::insertValue(int val){ 

     root = insertValue(root, val);
} 

std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val){ 

     if (n == nullptr) {
          return std::shared_ptr<Node>(new Node(val));
     }

     if (val < n->value) {
          n->left = insertValue(n->left, val);
     }
     else if (val > n->value) {
          n->right = insertValue(n->right, val);
     }

     return n; 
} 

void BST::deleteValue(int val){
     root = deleteValue(root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){

     if (n == nullptr) {
          return nullptr;
     }

     if (val < n->value) {
          n->left = deleteValue(n->left, val);
     }
     else if (val > n->value) {
          n->right = deleteValue(n->right, val);
     }
     else {
          if (n->left == nullptr) {
               return n->right;
          }
          else if (n->right == nullptr) {
               return n->left;
          }

          n->value = minimum(n->right)->value;
               n->right = deleteValue(n->right, n->value);
     }

  return n;
}

bool BST::isBST(std::shared_ptr<Node> n){ 
  return isBST(root, INT_MIN, INT_MAX); 
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high){ 

     if (n == nullptr) {
          return true;
     }

     if (n->value < low || n->value > high) {
          return false;
     }

     return isBST(n->left, low, n->value - 1) && isBST(n->right, n->value + 1, high);
} 

void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){ 
     if (n != nullptr) {

          order.push_back(n);

          preOrder(n->left, order);

          preOrder(n->right, order);
     }
} 

void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){

     if (n != nullptr) {
          inOrder(n->left, order);
          order.push_back(n);
          inOrder(n->right, order);
     }
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){

     if (n != nullptr) {
          postOrder(n->left, order);
          postOrder(n->right, order);
          order.push_back(n);
     }
}
