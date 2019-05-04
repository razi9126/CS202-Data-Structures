//*****************************************************************************
//
// This part requires all the work to be done in this file only.
// You will be modifying this function only ->
//
//
//
//*****************************************************************************



#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "stack.cpp"

using namespace std;

void towers(Stack<int>& a, Stack<int>& b, Stack<int>& c);
bool testing();

int main()
{
	if (testing())
	{
		cout << "Test cases passed." << endl;
	} else {
		cout << "Test cases failed." << endl;
	}
}

void TOH(int n,Stack<int>& a, Stack<int>& b, Stack<int>& c)
{
    if(n==1)
    {
        c.push(a.pop());
        //cout<<"Move Disk "<<n<<" from "<<Sour<<" to "<<Des<<endl;
        return;
    }

    TOH(n-1,a,c,b);
    c.push(a.pop());
    //cout<<"Move Disk "<<n<<" from "<<Sour<<" to "<<Des<<endl;
    TOH(n-1,b,a,c);
}
void towers(Stack<int>& a, Stack<int>& b, Stack<int>& c)
{
    int siz=a.length();
    TOH(siz,a,b,c);
}
bool testing()
{
	srand(time(NULL));
	int maxValue = 500;

	for (int i = 1; i < 20; ++i)
	{
		Stack<int> a;
		Stack<int> b;
		Stack<int> c;
		vector<int> temp;

		for (int j = 0; j < i; ++j)
			temp.push_back((rand()+1) % maxValue);
		sort(temp.begin(), temp.end());

		for (int j = 0; j < i; ++j)
			a.push(temp[i - j - 1]);

		towers(a, b, c);

		for (int j = 0; j < i; ++j)
		{
			if (temp[j] != c.pop())
				return false;
		}
	}

	return true;
}

