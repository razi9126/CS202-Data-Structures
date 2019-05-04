#ifndef PQUEUE__CPP
#define PQUEUE__CPP

#include <cstdlib>
#include "pqueue.h"
#include <iostream>
using namespace std;
// #include "heap.cpp"
// #include "Graph.cpp"

template <class T>
pqueue<T>::pqueue(int cap)
{
	harr= new T[cap];
	heap_size = 0;
	capacity = cap;
}

template <class T>
void pqueue<T>::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	if (l > (heap_size-1))  					//right would also be out of bounds then
		return;
	else if (r > (heap_size -1)){
		if (harr[i] >  harr[l]) {			// swap if parent is greater than left child (right child does not exist)
			T temp =  harr[l];
			harr[l] = harr[i];
			harr[i] = temp;
		}
		MinHeapify(l);
	}
	else{													//both left and right children exist
		if (harr[l] < harr[r])							// if left child smaller than right
		{
			if (harr[i] > harr[l]) {			// swap if parent is greater than left child (right child does not exist)
				T temp = harr[l];
				harr[l] = harr[i];
				harr[i] = temp;
				MinHeapify(l);
			}
		}
		else{											// if right child smaller than left
			if (harr[i] > harr[r]) {			// swap if parent is greater than right child (right child does not exist)
				T temp = harr[r];
				harr[r] = harr[i];
				harr[i] = temp;
				MinHeapify(r);
			}
		}
		return;
	}
}

template <class T>
int pqueue<T>::parent(int i)
{
	int x = (i-1)/2;
	if (x>0)
		return x;
	else
		return 0;
}

template <class T>
int pqueue<T>::left(int i)
{
	return ((2*i)+ 1);
}

template <class T>
int pqueue<T>::right(int i)
{
	return ((2*i)+2);
}

template <class T>
T pqueue<T>::extractMin()
{
	if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
 	T temp = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	if(heap_size>0 )
		MinHeapify(0);
	return temp;

}

template <class T>
void pqueue<T>::decreaseKey(int i, T new_val)
{
	harr[i]= new_val;
	heap_size++;
	while(i!=0){
		if (harr[parent(i)] > harr[i])
		{
			T temp = harr[parent(i)];
			harr[parent(i)] = harr[i];
			harr[i] = temp;
			i= parent(i);
		}
		else
			break;
	}
}

template <class T>
T pqueue<T>::getMin()
{
	return harr[0];
}

template <class T>
void pqueue<T>::deleteKey(int i)
{
    if(i<heap_size){
	harr[i] = harr[heap_size-1];
	heap_size--;
	MinHeapify(i);
    }
}

template <class T>
void pqueue<T>::insertKey(T k)
{
	if (heap_size==capacity)
	{
		cout<<"Full";
	}
	else
	{
		harr[heap_size] = k;
		int x = heap_size;
		heap_size++;
		while(x!=0){
			if (harr[parent(x)] > harr[x])
			{
				T temp = harr[parent(x)];
				harr[parent(x)] = harr[x];
				harr[x] = temp;
				x= parent(x);
			}
			else
				break;
		}
	}
}

template <class T>
T* pqueue<T>::getHeap()
{
	return harr;
}
#endif