#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 5){
    int result = 0;
    int total= word.length();
    for(int i = 0; i < total; i++)
    {
        result += word[i] * pow(val, total-i-1);
    }
    return result;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
    int result = 0;
    int total= word.length();
    for(int i = 0; i < total; i++)
    {
        result +=(result<<5) + (result>>2) + word[i] ;
    }

    return result;

}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){

    return hash%size;
}
// multiplication addition and division compression.
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
    return 0;
}
// 'm' and 'a' can take any value
#endif
// you may write your own program to test these functions.
