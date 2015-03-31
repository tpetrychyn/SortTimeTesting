//
//  main.cpp
//  Assignment11
//
//  Created by Taylor Petrychyn on 2015-03-31.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "main.h"

using namespace std;
int arraySize = 1000;

int comparisons;
int assignments;

int main(int argc, const char * argv[]) {
    
    ofstream outData;
    outData.open("output.txt");
    if (!outData) {
        cout << "Could not open output file" << endl;
        return 2;
    }
    
    string files[9] = { "file1k.random", "file1k.reverse", "file1k.sorted", "file10k.random", "file10k.reverse", "file10k.sorted", "file100.random", "file100.reverse", "file100.sorted" };
    
    for (auto filename : files) {
        ifstream inData;
        inData.open(filename);
    
        //Check that file was opened
        if (!inData) {
            cout << "File not found" << endl;
            return 1;
        }
        
        //Determine how many values will be in the files
        if (filename.find("1k") != string::npos)
            arraySize = 1000;
        else if (filename.find("10k") != string::npos)
            arraySize = 10000;
        else if (filename.find("100") != string::npos)
            arraySize = 100;
    
        //Read in array once per file
        int arrayToSort[arraySize];
        int arrayPos = 0;
        while (!inData.eof() && arrayPos < arraySize) {
            inData >> arrayToSort[arrayPos];
            arrayPos++;
        }
        
        int tempArray[arraySize];
        outData << filename << endl;
        outData << "Algorithm,Comparisons,Assignments" << endl;
        
        
        /*Insertion Sort*/
        comparisons = 0; //reset our counts
        assignments = 0;
        for (int i=0;i<arraySize;i++)//assign array to a temp array each time to limit disc reads
            tempArray[i] = arrayToSort[i];
    
        InsertionSort(tempArray); //perform the sort
        outData << "Insertion," << comparisons << "," << assignments << endl; //output our data
        
        
        /*ShellSort Hibbard*/
        comparisons = 0;
        assignments = 0;
        for (int i=0;i<arraySize;i++)
            tempArray[i] = arrayToSort[i];
        
        ShellSortHibbard(tempArray);
        outData << "Shell (Hibbard)," << comparisons << "," << assignments << endl;
        
        
        /*HeapSort*/
        comparisons = 0;
        assignments = 0;
        for (int i=0;i<arraySize;i++)
            tempArray[i] = arrayToSort[i];
        
        HeapSort(tempArray);
        outData << "Heap," << comparisons << "," << assignments << endl;
        
        
        /*SelectionSort*/
        comparisons = 0;
        assignments = 0;
        for (int i=0;i<arraySize;i++)
            tempArray[i] = arrayToSort[i];
        
        SelectionSort(tempArray);
        outData << "Selection," << comparisons << "," << assignments << endl;
        
        
        /*QuickSort*/
        comparisons = 0;
        assignments = 0;
        for (int i=0;i<arraySize;i++)
            tempArray[i] = arrayToSort[i];
        
        QuickSort(tempArray, 0, arraySize);
        outData << "Quick," << comparisons << "," << assignments << endl;
        
        
        /*MergeSort*/
        comparisons = 0;
        assignments = 0;
        for (int i=0;i<arraySize;i++)
            tempArray[i] = arrayToSort[i];
        int newArray[arraySize];
        MergeSort(tempArray, newArray, 0, arraySize);
        outData << "Merge," << comparisons << "," << assignments << endl;
        
    
        outData << "\n";
    }
    
    return 0;
}

void InsertionSort(int a[]) {
    for (int i=1;i<arraySize - 1;i++) {
        int temp = a [i];
        assignments++;
        int j = i;
        comparisons++; //loop will perform at least 1 comparison (aka loops are n+1)
        while (j > 0 && temp < a [j - 1]) {
            comparisons++; //each successful loop performs another comparison
            a [j] = a [j - 1];
            assignments++;
            j --;
        }
        a [j] = temp;
        assignments++;
    }
    return;
}

void ShellSortHibbard(int a[]) {
    int k = log (arraySize);
    int gap = pow(2,k) - 1;
    while (gap > 0) {
        for (int i = gap;i<arraySize- 1;i++) {
            int temp = a [i];
            assignments++;
            int j = i;
            comparisons++;
            while (j >= gap && temp < a [j - gap]) {
                comparisons++;
                a [j] = a [j - gap];
                assignments++;
                j = j - gap;
            }
            a [j] = temp;
            assignments++;
        }
        k --;
        gap = pow(2,k) - 1;
    }
    return;
}

void HeapSort(int a[]) {
    int elementCount = arraySize - 1;
    // build max-heap phase
    int i = elementCount / 2;
    while (i > 0) {
        PercolateDown (a, i, elementCount);
        i --;
    }
        // sort phase
    while (elementCount > 1) {
        swap (a [1], a [elementCount]);
        assignments++;
        elementCount --;
        PercolateDown (a, 1, elementCount);
    }
    return;
}

void PercolateDown(int a[], int i, const int elementCount) {
    int temp = a [i];
    while (i * 2 <= elementCount) {
        int child = i * 2;
        comparisons++;
        if (child != elementCount && a [child] < a [child + 1]) {
            child ++;
        }
        comparisons++;
        if (temp < a [child]) {
            a [i] = a [child];
            assignments++;
        } else
            break;
        i = child;
    }
    a [i] = temp;
    assignments++;
    return;
}

void SelectionSort(int a[]) {
    for (int i = 0;i<arraySize - 2;i++) {
        int min = i;
        int temp = a [i];
        assignments++;
        for (int j = i + 1;j<arraySize - 1;j++) {
            comparisons++;
            if (a [j] < temp) {
                comparisons++;
                min = j;
                temp = a [j];
                assignments++;
            }
        }
        a [min] = a [i];
        assignments++;
        a [i] = temp;
        assignments++;
    }
    return;
}

void QuickSort(int a[], int left, int right) {
    if (left + 10 <= right) {
        int pivot = Partition (a, left, right);
        QuickSort (a, left, pivot - 1);
        QuickSort (a, pivot + 1, right);
    } else
        InsertionSort (a, left, right);
    return;
}

int Partition(int a[], int left, int right) {
    DeterminePivot (a, left, right);
    // pivot is in a [right - 1]
    int i = left;
    int j = right - 1;
    while (1) {
        comparisons++;
        while (a [++i] < a [right - 1])
            comparisons++;
        comparisons++;
        while (a [right - 1] < a [--j])
            comparisons++;
        if (i < j) {
            swap (a [i], a [j]);
            assignments++;
        }
        else
            break;
    }
    swap (a [i], a [right - 1]);
    assignments++;
    // pivot is in a [i]
    return i;
}

void DeterminePivot(int a[], int left, int right) {
    int center = (left + right) / 2;
    comparisons++;
    if (a [center] < a [left]) {
        swap (a [left], a [center]);
        assignments++;
    }
    comparisons++;
    if (a [right] < a [left]) {
        swap (a [left], a [right]);
        assignments++;
    }
    comparisons++;
    if (a [right] < a [center]) {
        swap (a [center], a [right]);
        assignments++;
    }
    swap (a [center], a [right - 1]);
    assignments++;
    // pivot is in a [right - 1]
    return;
}

void InsertionSort(int a[], int left, int right) {
    for (int i=left;i<right;i++) {
        int temp = a [i];
        assignments++;
        int j = i;
        comparisons++;
        while (j > 0 && temp < a [j - 1]) {
            comparisons++;
            a [j] = a [j - 1];
            assignments++;
            j --;
        }
        a [j] = temp;
        assignments++;
    }
    return;
}

void MergeSort(int a[], int b[], int bottomLeft, int topRight) {
    if (bottomLeft < topRight) {
        // partition phase
        int bottomRight = (bottomLeft + topRight) / 2;
        MergeSort (a, b, bottomLeft, bottomRight);
        int topLeft = bottomRight + 1;
        MergeSort (a, b, topLeft, topRight);
        // merge phase
        int i = bottomLeft;
        int elementCount = topRight - bottomLeft + 1;
        while (bottomLeft <= bottomRight and topLeft <= topRight) {
            comparisons++;
            if (a [bottomLeft] <= a [topLeft]) {
                b [i] = a [bottomLeft];
                assignments++;
                bottomLeft ++;
            } else {
                b [i] = a [topLeft];
                assignments++;
                topLeft ++;
            }
            i ++;
        }
        while (bottomLeft <= bottomRight) {
            b [i] = a [bottomLeft];
            assignments++;
            bottomLeft ++;
            i ++;
        }
        while (topLeft <= topRight) {
            b [i] = a [topLeft];
            assignments++;
            topLeft ++;
            i ++;
        }
        // result in a
        i = 0;
        while (i < elementCount) {
            a [topRight] = b [topRight];
            assignments++;
            i ++;
            topRight --;
        }
    }
    return;
}
