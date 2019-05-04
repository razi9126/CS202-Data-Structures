#ifndef __TREE_CPP
#define __LIST_CPP
#include "tree.h"
#include <fstream>
#include <vector>



Tree::Tree()
{
    head=NULL;
}

Tree::Tree(string file)
{
    head=NULL;


    ifstream fin;
    fin.open(file.c_str(), ios::in);
    while(!fin.eof())
    {
        string line;
        getline(fin, line);
        insert(line);
    }
    fin.close();
}
Tree::~Tree()
{
    TreeItem* current=getHead();
    TreeItem* temp=NULL;
    while(head!=NULL)
    {
        if(current->FChild!=NULL)
        {
            current=current->FChild;
        }
        else if ((current->NextS!=NULL)&&(current->Parent!=NULL))
        {
            temp=current->NextS;
            (current->Parent)->FChild=NULL;
            delete current;
            current=temp;
        }
        else if (current->Parent!=NULL)
        {
            temp=current->Parent;
            temp->FChild=NULL;
            delete current;
            current= temp;
        }
        else
        {
            delete current;
            head=NULL;
        }
    }
}

TreeItem* Tree::findInTree(string toFind, TreeItem* current)

{
    if (current==NULL)
    {
        return NULL;
    }
    while (current->NextS!=NULL) //Checks uptil the last element in each row
    {
        if(current->value==toFind)
        {
            return current;
        }
        else if (current->FChild!=NULL)
        {
            return (findInTree(toFind, current->FChild));
        }
        current=current->NextS;
    }
    if(current->value==toFind)  //Checking the last element in each row
    {
        return current;
    }
    else if (current->FChild!=NULL)
    {
        return (findInTree(toFind, current->FChild));
    }
    else
        return (findInTree(toFind, (current->Parent)->NextS)); //Returning the pointer to right sib of the parent so that it doesnt go in infinite loop


    }


void Tree::insert(string item)
{
    vector<string> result=toVector(item);
    TreeItem *current=head;
    insertInTree(result, current, NULL, 0);
}


void Tree::insertInTree(vector<string> result, TreeItem* current, TreeItem* parent, int i)
{
    if (i!= result.size())
    {
        TreeItem* tmp= new TreeItem(result[i]);
        tmp->NextS=NULL; tmp->Parent=parent; tmp->FChild=NULL;
        if ((current==NULL)&&(i==0)) //if head is null then assign head its new value
        {
            head=tmp;
            if (parent!=NULL) //if the new node we're inserting is not at root, Meaning that it would have a parent
            {
                parent->FChild=tmp;}                  //Done with Iqra Zahra
            insertInTree(result, tmp->FChild, tmp, (i+1));
            return;
        }
        else if (current==NULL)
        {
            if (parent!=NULL) //if the new node we're inserting is not at root, Meaning that it would have a parent
            {
                parent->FChild=tmp;
            }
            insertInTree(result, tmp->FChild, tmp, (i+1));
            return;
        }
        else
        {
            while(current->NextS!=NULL)
            {
                if (current->value==result[i])
                {
                    insertInTree(result, current->FChild, current, (i+1));
                    return;}
                else
                {current=current->NextS;}
            }
            if (current->value==result[i])  //checks the last element here
            {
                insertInTree(result, current->FChild, current, (i+1));
                return; }
            else    //Insert after the last element
            {
                current->NextS=tmp;
                insertInTree(result, tmp->FChild, tmp, (i+1));
                return; }
        }
    }
}



vector<string> Tree::Locate(string qry)
{
    TreeItem *pointer=NULL;
    pointer=findInTree(qry,getHead());
    vector<string>output;
    if (pointer==NULL)
        return output;
    else
    {
        while (pointer!=NULL)
        {
            output.push_back(pointer->value);
            pointer=pointer->Parent;
        }
        return output;
    }

}

string Tree::LComAc(string a, string b)
{
    vector<string>output1=Locate(a);
    vector<string>output2=Locate(b);

    if((output1.size()==0) || (output2.size()==0))
        return "One of the files not found";
    else
    {
        for (int i=0;i<output1.size();i++){
            for (int j=0;j<output2.size();j++)
            {
                if (output1[i]==output2[j])
                {
                    return output1[i];
                }
                else{}
            }
        }
    }

}

TreeItem* Tree::getHead()
{
	return head;
}



int Tree::countFiles()
{
    return traverse(getHead());
}

int Tree::traverse(TreeItem* current)
{
    if (current==NULL)
    {
        return 0;
    }
    int counter=0;
    while (current->NextS!=NULL)
    {

        if (current->FChild!=NULL)
        {
            return (counter+(traverse(current->FChild)));
        }
        current=current->NextS;
        counter++; //counts how many times it has moved towards to right in a row
    }

    if (current->FChild!=NULL)
    {
        return (counter+(traverse(current->FChild)));
    }
    else
        return 1+counter+(traverse((current->Parent)->NextS));


}

vector<string> Tree::toVector(string input)
{
    vector<string> result;
    string current="";
    for (int i=0; i<input.length(); i++)
    {
//        if (input[i]=='\\')
        if (input[i]=='/')
        {
            result.push_back(current);
            current="";
        }
        else
        {
            current+= input[i];
        }
    }
    result.push_back(current);
    return result;

}

void Tree::moveFolder(string fromFolder,string toFolder)
{
}
#endif
