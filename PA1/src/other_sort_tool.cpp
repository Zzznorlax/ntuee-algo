// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2021/02/26 Hsien-Chia Chen]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
	for (int i = 1; i < data.size(); i++) {
		// key is the element i sort
		int key = data[i];
		int j = i - 1;
		// put every element bigger than key on the right of key
		while (j >= 0 && data[j] > key) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;
	}
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
	if (low < high) {
		// divide
		int q = Partition(data, low, high);
		// conquer recursively sort two subarrays
		QuickSortSubVector(data, low, q - 1);
		QuickSortSubVector(data, q + 1, high);
	}
}

// create a function to exchange two elements
void exchange(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
	// pivot be the rightmost
	int pivot = data[high];
	int i = (low - 1);
	// subarray on the left of pivot
	for (int j = low; j < high; j++) {
		if (data[j] < pivot) {
			i++;
			exchange(&data[i], &data[j]);
		}
	}
	// subarray on the right of pivot
	i++;
	exchange(&data[i], &data[high]);
	return i;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
	//divide
	if (low < high) {
		int q = (low + high) / 2;
		// conquer recursively call itself
		MergeSortSubVector(data, low, q);
		MergeSortSubVector(data, q + 1, high);
		// combine
		Merge(data, low, q, q + 1, high);
	}
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
	int left = middle1 - low + 1;
	int right = high - middle2 + 1;
	// create temp arrays
	int *L = new int[left];
	int *R = new int[right];
	// copy data to the tow temp arrays
	for (int i = 0; i < left; i++)
		L[i] = data[low + i];
	for (int j = 0; j < right; j++)
		R[j] = data[middle2 + j];

	// merge back into data
	int a = 0;    // for right
	int b = 0;    // for left
	int c = low;  // for data
	while (a < left && b < right) {
		if (L[a] <= R[b]) {
			data[c] = L[a];
			a++;
		}
		else {
			data[c] = R[b];
			b++;
		}
		c++;
	}
	// if R is empty, copy the rest elements of L in data
	while (a < left && b == right) {
		data[c] = L[a];
		a++;
		c++;
	}
	// if L is empty, copy the rest elements of R in data
	while (a == left && b < right) {
		data[c] = R[b];
		b++;
		c++;
	}
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1 ; i > 0; i--) {
		exchange(&data[0], &data[i]);
		heapSize = heapSize - 1;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
	// Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
	// TODO : Please complete max-heapify code here
	// get root's two children
	int L = root * 2 + 1;
	int R = root * 2 + 2;
	// create temp int to store the largest value
	int largest;
	// find largest
	if (L < heapSize && data[L] > data[root]) {
		largest = L;
	}
	else {
		largest = root;
	}
	if (R < heapSize && data[R] > data[largest]) {
		largest = R;
	}
	// make the root has the largest element
	if (largest != root) {
		exchange(&data[root], &data[largest]);
		MaxHeapify(data, largest);
	}
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
	heapSize = data.size(); // initialize heap size
	// Function : Make input data become a max-heap
	// TODO : Please complete BuildMaxHeap code here
	for (int i = (data.size() / 2) - 1 ; i >= 0; i--) {
		MaxHeapify(data, i);
	}
}
