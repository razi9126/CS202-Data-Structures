#include <fstream>
#include "sorts.cpp"

using namespace std;
//Copied the code for binary search from the internet
long binarySearch(vector<long>& nums, int l, int r, long toFind)          //log n time
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;
        if (nums[mid] ==toFind)
            return mid;
        if (nums[mid] > toFind)
            return binarySearch(nums, l, mid-1, toFind);
        return binarySearch(nums, mid+1, r, toFind);
   }

   return LONG_MAX;
}
// A single pair is stored in a Vector<long>
// You have to return a vector of all pairs.
vector< vector<long> > smartSearch(vector<long> nums, long k)
{
    //Sorting takes nlogn time. Only binary search will take O(n log n) for total of n items.
    //Sseaching for the other value takes n(total values to be seached) x logn(time taken for binary search) total time
    //Hence overall complexity is nlogn

    vector<long> result = QuickSortArray(nums); //result now has the numbers in sorted order [O(n log n)]
    long i = 0;
    vector< vector<long> > values;

    while (i<result.size()){
        long diff = k-result[i];
        long x = binarySearch(result, 0, result.size(), diff);
        if (x!= LONG_MAX){
            vector<long> entries;
            entries.push_back(result[i]);
            entries.push_back(diff);
            values.push_back(entries);
        }
        i++;
    }
    return values;
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
