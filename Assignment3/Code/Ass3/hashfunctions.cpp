#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <math.h>
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 5){
    int result = 0;
    int total= value.length();
    for(int i = 0; i < total; i++)
    {
        result += value[i] * pow(a, total-i-1);
    }
    return result;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
    int result = 0;
    int total= value.length();
    for(int i = 0; i < total; i++)
    {
        result ^=(result<<5) + (result>>2) + value[i] ;
    }

    return result;

}
unsigned long fasthash(std::string value)
{
    unsigned long hash = 5381;
    int c;
    int i=0;
    while (c == value[i]){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        i++;
    }
    return hash;
}


// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){

    return (hash)%size;
}
// multiplication addition and division compression.
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
    return ((m*hash)+a)%size;
}
// 'm' and 'a' can take any value
#endif
// you may write your own program to test these functions.
