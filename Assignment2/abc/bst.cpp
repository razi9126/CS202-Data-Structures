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
    del(getRoot());
}

template <class T>
void BST<T> :: del(node<T>* p)  //recursive function for the destructor
{
    if (p==NULL)
    {
        return;
    }
    else
    {
        del(p->left);
        del(p->right);
        delete p;
        p=NULL;
    }
}
template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   if (p==NULL)
   {
       return 0;
   }
   else {return(p->height);}
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (p==NULL)
        return 0 ;
    return (height(p->right) - height(p->left));
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    if (p==NULL){ return;}
    else if((p->left==NULL) && (p->right==NULL))
    {
        p->height = 1;

    }
    else if((p->left!=NULL) && (p->right==NULL))
    {
        p->height= 1 + (height(p->left));

    }
    else if((p->left==NULL) && (p->right!=NULL))
    {
        p->height= 1 + (height(p->right));
    }
    else
    {
        p->height= 1+ max(height(p->left),height(p->right));

    }
}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rightright(node<T>* p)
{
    // Rotate left code goes here.
    node<T>* newroot=p->right;
    node<T>* newleft=newroot->left;

    newroot->left=p;
    p->right=newleft;

    fixHeight(newroot);
    fixHeight(p);

    return newroot;
    //return p;
}

template <class T>
node<T>* BST<T> :: leftleft(node<T>* p){
    node<T>* newroot=p->left;
    node<T>* newleft=newroot->right;

    newroot->right=p;
    p->left=newleft;

    fixHeight(newroot);
    fixHeight(p);

    return newroot;
//    return p;
}



template <class T>
node<T>* BST<T> :: balance(node<T>* p){

    fixHeight(p);

    if(balanceFactor(p)==2)
    {
        if(balanceFactor(p->right)< 0) //right left
            {p->right = leftleft(p->right);}
        return rightright(p);
    }
    if( balanceFactor(p)==-2)
    {
        if(balanceFactor(p->left)> 0)
            {p->left = rightright(p->left);}
        return leftleft(p);
    }

    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: makeRoot(node<T>* p)
{
    root=p;
}


template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
    if (!search(k))
    {
        if (p==NULL)
        {
            node<T> *n = new node<T>(k,value);
            return n;
        }
        else
        {
            if (k>p->key)
            {
                p->right=insertHelper(value, k, p->right);
            }
            else
            {
                p->left=insertHelper(value, k, p->left);
            }
        }
    }
    return balance(p);


}
template<class T>
node<T>* BST<T> :: search(T key){
    node<T> *temp=getRoot();
    node<T> *val=NULL;
    while(temp!=NULL)
    {
        if (temp->key==key)
        {
            val=temp;
            return val;
        }
        else if(key>temp->key)
        {
            temp=temp->right;
        }
        else
        {
            temp=temp->left;
        }
    }
    return NULL;

}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p)
{
    // This function finds the min node of the tree.
    if(p==NULL)
    {
        return NULL;
    }
    else
    {
        node<T> *temp=p;
        while (temp->left!=NULL)
        {
            temp=temp->left;
        }
        return temp;
    }
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {

    if (p->left ==NULL)
    {
        return p->right;
    }
    else
    {
        p->left=removemin(p->left);
        return balance(p);
    }
   // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}


template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    if (p==NULL)
        return NULL;
    if (k>(p->key))
        {p->right=remove(p->right, k);}
    else if (k<p->key)
       {p->left=remove(p->left, k);}
    else
    {
        if((p->right==NULL) && (p->left==NULL))
        {
            node<T> *temp=p;
            delete temp;
            return NULL;
        }
        else if ((p->right==NULL) && (p->left!=NULL))
        {
            node<T> *temp=p;
            node<T> *nextchild=temp->left;
            delete temp;
            return balance(nextchild);
        }
        else if ((p->right!=NULL) && (p->left==NULL))
        {
            node<T> *temp=p;
            node<T> *nextchild=temp->right;
            delete temp;
            return balance(nextchild);
        }
        else
        {
            node<T> *temp=p;
            node<T> *nextchild=findmin(p->right);
            nextchild->right=removemin(p->right);
            nextchild->left=p->left;
            delete temp;
            return balance(nextchild);
        }

    }

    return balance(p);
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
