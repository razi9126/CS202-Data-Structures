#include <fstream>
#include "sorts.cpp"

using namespace std;


// A single pair is stored in a Vector<long>
// You have to return a vector of all pairs.
vector< vector<long> > smartSearch(vector<long> nums, long k)
{   

    // Write your code in this function

}


int main()
{
    vector<long> nums;
    ifstream in("random.txt");
    long n;
    while(in >> n)
        nums.push_back(n);
    in.close();

    long k;
    cout << "Enter the value of K: ";
    cin >> k;

    vector< vector<long> > result = smartSearch(nums, k);

    for(int i = 0; i < result.size(); i++)
        cout << result[i][0] << ", " << result[i][1] << endl;

    return 0;
}