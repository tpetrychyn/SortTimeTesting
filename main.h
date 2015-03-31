
//
//  main.h
//  Assignment11
//
//  Created by Taylor Petrychyn on 2015-03-31.
//  Copyright (c) 2015 Taylor Petrychyn. All rights reserved.
//

#ifndef Assignment11_main_h
#define Assignment11_main_h

void InsertionSort(int a[]);
void ShellSortHibbard(int a[]);
void ShellSortSedgeWick(int a[]);
void HeapSort(int a[]);
void PercolateDown(int a[], int i, const int elementCount);
void SelectionSort(int a[]);
void QuickSort(int a[], int left, int right);
void MergeSort(int a[], int b[], int bottomLeft, int topRight);

int Partition(int a[], int left, int right);
void DeterminePivot(int a[], int left, int right);
void InsertionSort(int a[], int left, int right);

#endif
