#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"
#include "list.h"
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    long* arr= new long[nums.size()];
    for (int i = 0; i< nums.size(); i++) 												//copying to array
        arr[i] = nums[i];
    for (int i = 1; i< nums.size(); i++)
    {
        long toMove = arr[i];
        int j = i - 1;

        while((j>=0) && (arr[j]>toMove))													// move one step until find the right place
        {
            // will exit as soon as toMove>arr[j], array behind this already sorted
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = toMove;
    }

    vector<long> entries;
    for (int i = 0; i< nums.size(); i++) 												//copying to array
    {
        entries.push_back(arr[i]);
    }
    return entries;

}

//=====================================================================================
ListItem<int>* Merge(ListItem<int>* l1, ListItem<int>* l2)      //Basic merging algorithm
{
    if (l1 == NULL)                         //if head of list1 is empty
        return l2;
    else if (l2 == NULL)                    //if head of list 12 is empty
        return l1;
    else if (l1->value <= l2->value)
    {
        l1->next = Merge(l1->next, l2);      //l1 is the first value
        return l1;												//returning after setting the next pointers so that we don't have to traverse the whole list to add a new pointer to it
    }
    else
    {
        l2->next = Merge(l1, l2->next);
        return l2;
    }
}


ListItem<int>* divide(ListItem<int>* original)
{
    List<int> og;
    og.setHead(original);
    int half = (og.length())/2;
    if (original == NULL)
        return NULL;
    else if (original->next == NULL)        //1 item list hence second list would just be null
        return NULL;
    else                                            // divide the list into aprox half
    {
        int k = 0;
        ListItem<int>* l2 = original;
        ListItem<int>* prev;
        while (k<half)
        {
            prev = l2;
            l2=l2->next;
            k++;
        }
        prev->next = NULL;                          // make previous LL goo till half its original size
        return l2;
    }
}

ListItem<int>* MSort(ListItem<int> *head)
{
    if (head == NULL)
        return NULL;
    else if (head->next == NULL)
        return head;
    else
    {
        List<int> list2;
        list2.setHead(divide(head));
        ListItem<int>* a = MSort(head);										//Will go into recursive calls until 1 elements lists
        ListItem<int>* b = MSort(list2.getHead());
        return Merge(a,b);													// Finally apply the basic merge also to the 2 lists
 
    }
}

vector<long> MergeSort(vector<long> nums)
{
    List<int> l;
    for (int i = 0; i< nums.size(); i++)
    {
        l.insertAtHead(nums[i]);
    }
    List<int> final;
    ListItem<int>* newhead;
    newhead = MSort(l.getHead());
    vector<long> entries;												//copying to array

    while(newhead!=NULL)
    {
        entries.push_back(newhead->value);
        newhead= newhead->next;
    }
    return entries;


}
//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
    long* arr= new long[nums.size()];
    for (int i = 0; i< nums.size(); i++) 												//copying to array
        arr[i] = nums[i];
    int s = nums.size();
    qSort(arr,0, (s-1));

    vector<long> entries;
    for (int i = 0; i< nums.size(); i++) 												//copying to array
    {
        entries.push_back(arr[i]);
    }
    return entries;
}

void qSort(long arr[], int start, int end)
{
    if(start < end)
    {
        int pivot_position = divide(arr, start, end);										//Index of position that is in its final place in array
        qSort(arr, start, pivot_position-1);
        qSort(arr, pivot_position+1, end);
    }

}

int divide(long arr[], int start, int end)
{
	//Uncomment this if you want to use the last element as pivot
    // //Using last element as the pivot
//    int pivot = end;
//    long pivot_value = arr[pivot];
//    int i = start;																			//Only sort the array other than the last element
//    int j = end-1;


//Uncomment this if you want to use median of 3 values as the pivot
    int val=0;									
    if (end>start)
    {
        long a = arr[start];
        long b = arr[end];
        long c = arr[((start+end)/2)];
        if (a>b)
        {
            if (b>c)
            {}
            else
            {
                long temp = arr[((start+end)/2)];									//replace pivot with the last value. Using last value as pivot
                arr[((start+end)/2)] = arr[end];
                arr[end] = temp;
            }
        }
        else if (b>a)
        {
            if (a>c)
            {
                long temp = arr[start];
                arr[start] = arr[end];
                arr[end] = temp;
            }
            else
            {
                long temp = arr[((start+end)/2)];
                arr[((start+end)/2)] = arr[end];
                arr[end] = temp;
            }
        }
        else if (c>a)
        {
            if (a>b)
            {
                long temp = arr[start];
                arr[start] = arr[end];
                arr[end] = temp;
            }
            else
            {}
        }
    }

    int pivot = end;
    long pivot_value = arr[pivot];
    int i = start;																			//Only sort the array other than the last element
    int j = end-1;


    //Uncomment this if you want to use the last element as the pivot
    // int pivot = start;
    // long pivot_value = arr[pivot];
    // int i = start+1;																			//Only sort the array other than the last element
    // int j = end;


    while (i <= j)
    {
        while ((arr[i] <= pivot_value) && (i<j))
            i=i+1;
        while ((arr[j] >= pivot_value) && (j>=i))
            j=j-1;
        if (i <= j)
        {
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
        if (i > j)
            break;
    }
    long tmp = arr[i];																		//Swap the last element to its final position in array
    arr[i] = arr[end];
    arr[end] = tmp;
    return i;
}

//=====================================================================================
vector<long> QuickSortList(vector<long> nums)
{

}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
    MinHeap* heap = new MinHeap(nums.size());
    for (int i = 0; i< nums.size(); i++) 												//copying to array
        heap->insertKey(nums[i]);
    vector<long> entries;
    for (int i = 0; i< nums.size(); i++)
        entries.push_back(heap->extractMin());
    return entries;

}

#endif
