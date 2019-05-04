#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD()
{
    tableSize = 10000; // you cant change this
    count=0;
    hashTable = new block*[tableSize];

    for(unsigned long i=0 ; i < tableSize ; i++)               //initialization
        hashTable[i] = NULL;
}

HashD::~HashD(){
    for (unsigned long i = 0; i < tableSize; i++){
        if(hashTable[i] != NULL){
            delete hashTable[i];
        }
    }
    delete[] hashTable;
}

unsigned long HashD :: hash1(string value){
   unsigned long val = bitHash(value) % tableSize;
   return val;
}
unsigned long HashD :: hash2(string value)
{
    unsigned long val = (11 - (bitHash(value)+1)%11);
    return val;
}

void HashD::resizeTable()
{
    long newsize=round(tableSize*2);
//    cout<<"Resizing"<<endl;
    block** newhashTable = new block*[newsize];             //pointer to array of pointers to blocks

    for(unsigned long i=0 ; i < newsize ; i++)               //initialization
        newhashTable[i] = NULL;
//    cout<<"INItIALIZATION DONE"<<endl;
    for (unsigned long i = 0; i < tableSize; i++)
    {
        if (hashTable[i] != NULL && hashTable[i]->value!="")
        {
            int k =0;
            unsigned long v1 = bitHash(hashTable[i]->value) % newsize;
            unsigned long v2 = hash2(hashTable[i]->value);
            unsigned long newval = v1 + (k*v2);
            unsigned long newindex= divCompression(newval,newsize);                                   //calculating the new index in the new table
            block* toIns = new block(newval, hashTable[i]->value);        //the new block to be inserted. same value but diff key

            while (newhashTable[newindex] != NULL)
            {
                k++;
                newindex = (v1 + (k* v2))% newsize;
//        cout<<"index: "<<index<<" ";
            }
            newhashTable[newindex] = toIns;

        }
    }
//    cout<<"stsdr";
    delete[] hashTable;
    // cout<<newsize<<endl;
    hashTable= newhashTable;
    tableSize=newsize;

    return;
}

void HashD::insert(string value){
    // cout<<"Insert"<<endl;
    long i=0;
    unsigned long v1 = hash1(value);
    unsigned long v2 = hash2(value);
    unsigned long ind = v1 + (i*v2);
    block* toIns = new block(ind,value);
    unsigned long index = divCompression(ind,tableSize);
    // cout<<index<<" ";
    while((hashTable[index] != NULL) && (hashTable[index]->value != value)&& (hashTable[index]->value != ""))
    {
        i=i+1;
        index = (v1 + (i* v2))% tableSize;

       // cout<<"index: "<<index<<" i: "<<i<<" ";
    }
    if(hashTable[index] == NULL)
        count=count+1;
    else if (hashTable[index]->key == -1)
        count=count+1;
    hashTable[index] = toIns;           //inserting the value
    // cout<<"index: "<<index<<endl;
    double emp= tableSize-count;
//    cout<<" At: "<<index<<" ";
//    cout<<val<<endl;
    if (emp<(tableSize/6)) {                    //resizing threshhold
        // cout<<emp<<" "<< (tableSize/6)<<endl;
        // cout<<"RESIZING"<<endl;
        resizeTable();}
        return;
    }

    void HashD::deleteWord(string value){
        long i=0;
        unsigned long v1 = hash1(value);
        unsigned long v2 = hash2(value);
        unsigned long ind = v1 + (i*v2);
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
        i++;
        ind = v1 + (i*v2);

        index=ind%tableSize;
    }
    long emp= tableSize-count;
    if (tableSize>2000)
    {
        long v=(tableSize*0.6);
//    cout<<emp<<" "<<v<<endl;
        if (emp-v>0)                       //resizing threshhold
        {
            long newsize=round(tableSize*0.6);
            //Need to shrink down if condition satisfied
            block** newhashTable = new block*[newsize];             //pointer to array of pointers to blocks

        for(unsigned long i=0 ; i < newsize ; i++)               //initialization
            newhashTable[i] = NULL;
    //    cout<<"INItIALIZATION DONE"<<endl;
        for (unsigned long i = 0; i < tableSize; i++)
        {
            if (hashTable[i] != NULL && hashTable[i]->value!="")
            {
                int k =0;
                unsigned long v1 = bitHash(hashTable[i]->value) % newsize;
                unsigned long v2 = hash2(hashTable[i]->value);
                unsigned long newval = v1 + (k*v2);
                unsigned long newindex= divCompression(newval,newsize);                                   //calculating the new index in the new table
                block* toIns = new block(newval, hashTable[i]->value);        //the new block to be inserted. same value but diff key

                while (newhashTable[newindex] != NULL)
                {
                    k++;
                    newindex = (v1 + (k* v2))% newsize;
    //        cout<<"index: "<<index<<" ";
                }
                newhashTable[newindex] = toIns;

            }
    }
//    cout<<"stsdr";
    delete[] hashTable;
    // cout<<newsize<<endl;
    hashTable= newhashTable;
    tableSize=newsize;
}
}



    return;
}

block* HashD::lookup(string value){
    long i = 0;
    unsigned long v1 = hash1(value);
    unsigned long v2 = hash2(value);
    unsigned long ind = v1 + (i*v2);
    unsigned long index = divCompression(ind,tableSize);
    while (hashTable[index]!=NULL)
    {
        //if node found return its value
        if(hashTable[index]->value == value)
            return hashTable[index];
        i++;
        ind = v1 + (i*v2);
       
        index=ind%tableSize;
    }
    return NULL;
}

#endif
