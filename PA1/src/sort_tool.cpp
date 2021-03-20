// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2021/02/26 Hsien-Chia Chen]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here

    for (int i = 0; i < data.size(); i++)
    {
        int element = data[i];

        int j = i - 1;
        for (; j >= 0 && data[j] > element; j--)
        {
            data[j + 1] = data[j];
        }

        data[j + 1] = element;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed

    if (low >= high)
    {
        return;
    }

    int pivotIndex = Partition(data, low, high);

    QuickSortSubVector(data, low, pivotIndex - 1);
    QuickSortSubVector(data, pivotIndex + 1, high);
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[high];

    int j = low - 1;
    for (int i = low; i <= high; i++)
    {
        if (data[i] <= pivot)
        {
            j++;
            int tmpElement = data[i];
            data[i] = data[j];
            data[j] = tmpElement;
        }
    }

    return j;
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed

    if (low == high)
    {
        return;
    }

    int middle = (high + low) / 2;

    MergeSortSubVector(data, low, middle);
    MergeSortSubVector(data, middle + 1, high);

    Merge(data, low, middle, middle + 1, high);
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    // Function : Merge two sorted subvector
    // TODO : Please complete the function

    int leftIndex = low;
    int rightIndex = middle2;

    vector<int> combined(data.size());

    int combinedIndex = low;
    while (leftIndex <= middle1 && rightIndex <= high)
    {
        if (data[leftIndex] < data[rightIndex])
        {
            combined[combinedIndex] = data[leftIndex];
            leftIndex++;
        }
        else
        {
            combined[combinedIndex] = data[rightIndex];
            rightIndex++;
        }

        combinedIndex++;
    }

    int remainingStartIndex = leftIndex;
    int remainingEndIndex = middle1;
    if (leftIndex > middle1)
    {
        remainingStartIndex = rightIndex;
        remainingEndIndex = high;
    }

    for (int i = remainingStartIndex; i <= remainingEndIndex; i++)
    {
        combined[combinedIndex] = data[i];
        combinedIndex++;
    }

    for (int i = low; i <= high; i++)
    {
        data[i] = combined[i];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    int tmp = 0;
    for (int i = data.size() - 1; i >= 1; i--)
    {
        tmp = data[i];
        data[i] = data[0];
        data[0] = tmp;

        // heapsize used to isolate the sorted part of heap
        heapSize--;

        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int rightIndex = (root + 1) * 2;
    int leftIndex = (root + 1) * 2 - 1;

    int largestElementIndex = root;

    if (rightIndex < heapSize && data[rightIndex] > data[largestElementIndex])
    {
        largestElementIndex = rightIndex;
    }

    if (leftIndex < heapSize && data[leftIndex] > data[largestElementIndex])
    {
        largestElementIndex = leftIndex;
    }

    if (largestElementIndex != root)
    {
        int tmp = data[largestElementIndex];
        data[largestElementIndex] = data[root];
        data[root] = tmp;
        MaxHeapify(data, largestElementIndex);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here

    for (int i = heapSize / 2; i >= 0; i--)
    {
        MaxHeapify(data, i);
    }
}
