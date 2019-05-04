#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
}

HashL::~HashL(){
    
}

unsigned long HashL :: hash(string value){
    return 0;
}

void HashL::resizeTable(){
    return;
}

void HashL::insert(string value){
    return;
}

void HashL::deleteWord(string value){
    return;
}
block* HashL::lookup(string value){
    return NULL;
}
#endif
