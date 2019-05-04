#include <iostream>
#include "bst.h"
#include <vector>


using namespace std;

template <class T>
void ToVec(node<T>* val, vector<node<T>*> &ans){
    if(val == NULL)
        return ;

    ToVec(val->left, ans);
    ans.push_back(val);
    ToVec(val->right, ans);
}

template <class T>
void Merge(vector<node<T>*> a1, vector<node<T>*> a2, vector<node<T>*> &ans){
    int i = 0; int j = 0;

    while (1)
    {
        if ((i==a1.size()) && (j == a2.size()))
            break;
        else if (i==a1.size())
            {ans.push_back(a2[j]); j++;}
        else if (j==a2.size())
            {ans.push_back(a1[i]); i++;}
        else if (a1[i]->key==a2[j]->key)
        {
            ans.push_back(a1[i]);
            i++; j++;
        }
        else if ((a1[i]->key)<(a2[j]->key))
        {
            ans.push_back(a1[i]);
            i++;
        }
        else
        {
            ans.push_back(a2[j]);
            j++;
        }
    }

}


template <class T>
void printer(node<T>* val){
    if(val == NULL)
        return ;
    printer(val->left);
    cout<<val->key<<endl;

    printer(val->right);
}



template <class T>
node<T>* makeBST(vector<node<T>*> val,int start, int end)
{

    if (start > end)
      return NULL;

    int mid = (start + end)/2;
    node<T>* root = new node<T>(val[mid]->key, val[mid]->value);

    root->left = makeBST(val, start, mid-1);
    root->right = makeBST(val, mid+1, end);

    return root;
}
//
//void mergeArray(T a1, T a2, )

template <class T>
void Union(BST<T>* tree1){
    vector<node<T>*> ans;
    ToVec(tree1->getRoot(),ans);
    for(size_t i = 0; i < ans.size(); ++i)
    {
        cout << ans[i]->key;
    }
    BST<int>* tree = new BST<int>();
    tree->makeRoot(makeBST(ans,0,ans.size()-1));

}

template <class T>
BST<T>* bst_Union(BST<T>* tree1,BST<T>* tree2)
{
    vector<node<T>*> arr1;
    ToVec(tree1->getRoot(),arr1);
    vector<node<T>*> arr2;
    ToVec(tree2->getRoot(),arr2);
//    printer(tree1->getRoot());
//printer(tree2->getRoot());

    BST<int>* tree = new BST<int>();
    vector<node<T>*> final_vec;
    Merge(arr1,arr2,final_vec);

    tree->makeRoot(makeBST(final_vec,0,final_vec.size()-1));

    return tree;
}
