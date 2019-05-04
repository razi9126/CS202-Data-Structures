#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
}

HashD::~HashD(){

}

unsigned long HashD :: hash1(string value){
    return 0;
}

unsigned long HashD :: hash2(string value){
    return 0;
}

void HashD::resizeTable(){
    return;
}

void HashD::insert(string value){
    return;
}

void HashD::deleteWord(string value){
    return;
}

block* HashD::lookup(string value){
    return NULL;
}

#endif