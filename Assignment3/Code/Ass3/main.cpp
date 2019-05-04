#include <iostream>
#include <time.h>

using namespace std;

bool timeOut;
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
int main()
{
    cout<<fasthash("sdjkass");
    return 0;
}
