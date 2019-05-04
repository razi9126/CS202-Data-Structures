#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"

template <class T>
MinHeap<T>::MinHeap(int cap)
{
	harr= new T[cap];
	heap_size = 0;
	capacity = cap;
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	if (l > (heap_size-1))  					//right would also be out of bounds then
		return;
	else if (r > (heap_size -1)){
		if (harr[i] >  harr[l]) {			// swap if parent is greater than left child (right child does not exist)
			int temp =  harr[l];
			harr[l] = harr[i];
			harr[i] = temp;
		}
		MinHeapify(l);
	}
	else{													//both left and right children exist
		if (harr[l] < harr[r])							// if left child smaller than right
		{
			if (harr[i] > harr[l]) {			// swap if parent is greater than left child (right child does not exist)
				int temp = harr[l];
				harr[l] = harr[i];
				harr[i] = temp;
				MinHeapify(l);
			}
		}
		else{											// if right child smaller than left
			if (harr[i] > harr[r]) {			// swap if parent is greater than right child (right child does not exist)
				int temp = harr[r];
				harr[r] = harr[i];
				harr[i] = temp;
				MinHeapify(r);
			}
		}
		return;
	}
}

int MinHeap::parent(int i)
{
	int x = (i-1)/2;
	if (x>0)
		return x;
	else
		return 0;
}

int MinHeap::left(int i)
{
	return ((2*i)+ 1);
}

int MinHeap::right(int i)
{
	return ((2*i)+2);
}

int MinHeap::extractMin()
{
	if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
 	int temp = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	if(heap_size>0 )
		MinHeapify(0);
	return temp;

}


void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i]= new_val;
	heap_size++;
	while(i!=0){
		if (harr[parent(i)] > harr[i])
		{
			int temp = harr[parent(i)];
			harr[parent(i)] = harr[i];
			harr[i] = temp;
			i= parent(i);
		}
		else
			break;
	}
}

int MinHeap::getMin()
{
	return harr[0];
}

void MinHeap::deleteKey(int i)
{
    if(i<heap_size){
	harr[i] = harr[heap_size-1];
	heap_size--;
	MinHeapify(i);
    }
}

void MinHeap::insertKey(int k)
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
				int temp = harr[parent(x)];
				harr[parent(x)] = harr[x];
				harr[x] = temp;
				x= parent(x);
			}
			else
				break;
		}
	}
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif
