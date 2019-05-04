#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
    tableSize=size;
    hashTable=new LinkedList<string>[tableSize];
}
HashC::~HashC()
{
    for (int i = 0; i < tableSize; i++)
    {
        hashTable[i].~LinkedList();

    }
    delete[] hashTable;
return;
}

unsigned long HashC :: hash(string input){
  int val=bitHash(input);
  return divCompression(val,tableSize);
}

void HashC::insert(string word){
    int value = hash(word);
    hashTable[value].insertAtHead(word);

    return;
}

ListItem<string>* HashC :: lookup(string word){
    int v=hash(word);
    return hashTable[v].searchFor(word);

}

void HashC :: deleteWord(string word){

    int value=hash(word);
    hashTable[value].deleteElement(word);
    return;
}

#endif
