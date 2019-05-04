#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP
#include "linearProbing.h"
#include "hashfunctions.cpp"
#include <math.h>


HashL::HashL()
{
    tableSize = 1000; // you cant change this
    count=0;
    hashTable = new block*[tableSize];

    for(int i=0 ; i < tableSize ; i++)               //initialization
        hashTable[i] = NULL;

    block* deleted = new block(-1, "");                    // to signify a node was present here(marker we discussed in class)

}

HashL::~HashL()
{
    for (unsigned long i = 0; i < tableSize; i++){
        if(hashTable[i] != NULL){
            hashTable[i]=NULL;
        }
    }
    delete[] hashTable;

}

unsigned long HashL :: hash(string value)
{
    unsigned long val=bitHash(value);
    return val;

}

void HashL::resizeTable()
{
    long newsize=round(tableSize*2);
//    cout<<"Resizing"<<endl;
    block** newhashTable = new block*[newsize];             //pointer to array of pointers to blocks

    for(unsigned long i=0 ; i < newsize ; i++)               //initialization
        newhashTable[i] = NULL;
//    cout<<"INItIALIZATION DONE"<<endl;
    for (unsigned long i = 0; i < tableSize; i++)
    {
        if (hashTable[i] != NULL )
        {

            unsigned long newval = hash(hashTable[i]->value);
            unsigned long newindex= divCompression(newval,newsize);                                   //calculating the new index in the new table
            block* toIns = new block(newval, hashTable[i]->value);        //the new block to be inserted. same value but diff key

            while (newhashTable[newindex] != NULL && hashTable[i]->value !="")  //inserting in the new table  //&& (newhashTable[newindex]->value != value)&& (newhashTable[newindex]->key != -1)
            {
                newindex=newindex+1;
                newindex=newindex%newsize;
            }
            newhashTable[newindex]=toIns;

        }
    }
//    cout<<"stsdr";
    delete[] hashTable;
    hashTable= newhashTable;
    tableSize=newsize;

    return;
}

void HashL::insert(string value)
{
    unsigned long ind = hash(value);
    block* toIns = new block(ind,value);
    unsigned long index = divCompression(ind,tableSize);

//    cout<<"tablesize: "<<tableSize<<" ";
    while((hashTable[index] != NULL) && (hashTable[index]->value != value)&& (hashTable[index]->value != ""))
    {
        index++;
        index=index%tableSize;
//        cout<<"index: "<<index<<" ";
    }

    if(hashTable[index] == NULL)
        count=count+1;
    else if (hashTable[index]->key == -1)
        count=count+1;
    hashTable[index] = toIns;           //inserting the value
    double emp= tableSize-count;
//    cout<<" At: "<<index<<" ";
//    cout<<val<<endl;
    if (emp<(tableSize/6))                       //resizing threshhold
    {
        resizeTable();
    }
    return;
}

void HashL::deleteWord(string value)
{
    unsigned long ind = hash(value);
    unsigned long index = divCompression(ind,tableSize);
    block* deleted = new block(-1, "");
    while(hashTable[index] != NULL)
    {
        if(hashTable[index]->value == value)
        {
            hashTable[index] = deleted;         //insert -1 at that place to allow for traversal on elements after this too
            count--;
            break;
        }
        index=index+1;
        index=index%tableSize;
    }
    //Need to shrink down if condition satisfied
    long emp= tableSize-count;
    if (tableSize>2000)
    {
        long v=(tableSize*0.6);
//    cout<<emp<<" "<<v<<endl;
        if (emp-v>0)                       //resizing threshhold
        {
            long newsize=round(tableSize*0.8);
//    cout<<"Resizing"<<endl;
            block** newhashTable = new block*[newsize];             //pointer to array of pointers to blocks

            for(unsigned long i=0 ; i < newsize ; i++)               //initialization
                newhashTable[i] = NULL;
//    cout<<"INItIALIZATION DONE"<<endl;
            for (unsigned long i = 0; i < tableSize; i++)
            {
                if (hashTable[i] != NULL && hashTable[i]->value !="")
                {
                    unsigned long newval = hash(hashTable[i]->value);
                    unsigned long newindex= divCompression(newval,newsize);                                   //calculating the new index in the new table
                    block* toIns = new block(newval, hashTable[i]->value);        //the new block to be inserted. same value but diff key

                    while (newhashTable[newindex] != NULL)  //inserting in the new table  //&& (newhashTable[newindex]->value != value)&& (newhashTable[newindex]->key != -1)
                    {
                        newindex=newindex+1;
                        newindex=newindex%newsize;
//                        cout<<newindex;
                    }
//                    cout<<endl;
                    newhashTable[newindex]=toIns;

                }
            }

//    cout<<"stsdr";
            delete[] hashTable;
            hashTable= newhashTable;
            tableSize=newsize;
        }
    }
    return;
}
block* HashL::lookup(string value)
{
    unsigned long ind = hash(value);
    unsigned long index = divCompression(ind,tableSize);
    while (hashTable[index]!=NULL)
    {
        //if node found return its value
        if(hashTable[index]->value == value)
            return hashTable[index];
        index++;
        index=index%tableSize;
    }
    return NULL;
}
#endif
