#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "list.h"
using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> QuickSortArray(vector<long> nums);
vector<long> QuickSortList(vector<long> nums);
vector<long> HeapSort(vector<long> nums);
ListItem<int>* Merge(ListItem<int>* firstNode, ListItem<int>* secondNode);
ListItem<int>* divide(ListItem<int>* original);
ListItem<int>* MSort(ListItem<int> *head);
void qSort(long array[], int start, int end);
int divide(long arr[], int start, int end);

#endif
