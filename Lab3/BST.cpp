// Lab 3 - BST.cpp
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
  return nullptr;
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){
  return nullptr;
}

std::shared_ptr<Node> BST::maximum(){
  return nullptr;
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){
  return nullptr;
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
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){
  return nullptr;
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
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
}
