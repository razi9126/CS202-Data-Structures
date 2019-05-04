#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

    // your destructor code goes here
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   return 0;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    return;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
    return p;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){    
    fixHeight(p);
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
    return balance(p);
}
template<class T>
node<T>* BST<T> :: search(T key){
    return NULL;
    // Search code goes here.
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    return NULL;
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    return balance(p);
    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    return balance(p);
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
