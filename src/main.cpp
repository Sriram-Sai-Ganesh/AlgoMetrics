#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int myType;				// type of variable in array
const size_t len = 100;					// array length

using namespace std;


void testSearchUtils(array<myType, len> sorted, myType target);
void testSortUtils(array<myType, len> array);


int main()
{
	// set arrray value bounds
	myType min=-10, max=700;

	// initialize array
	array<myType, len> ar = HelperUtils::GetRandomArray<myType, len>(min, max-1);
	HelperUtils::PrintArray<myType, len>(ar);
	endl(2);
	
	testSortUtils(ar);

	// sort ar
	ar = ArrayUtils::SelectionSort(ar);

	// int index = HelperUtils::GetRandomNumber<int>(0, len-1);
	// testSearchUtils(ar, ar[index]);
	

	return 0;
}


void testSortUtils(array<myType, len> ar){

	// BubbleSort elements
	cout<<"After BubbleSort:\n";
	array<myType, len> bubbleSorted = ArrayUtils::BubbleSort<myType, len>(ar);
	// print result
	HelperUtils::PrintArray<myType, len>(bubbleSorted);
	endl(2);

	// SelectionSort elements
	cout<<"After SelectionSort:\n";
	array<myType, len> selectionSorted = ArrayUtils::SelectionSort<myType, len>(ar);
	// print result
	HelperUtils::PrintArray<myType, len>(selectionSorted);
	endl(2);

	// InsertionSort elements
	cout<<"After InsertionSort:\n";
	array<myType, len> insertionSorted = ArrayUtils::InsertionSort<myType, len>(ar);
	// print result
	HelperUtils::PrintArray<myType, len>(insertionSorted);
	endl(2);
}

void testSearchUtils(array<myType, len> sorted, myType target){

	cout<<"sorted array is \n";
	HelperUtils::PrintArray<myType, len>(sorted);
	// perform 3 search operations
	cout<<"Searching for "<<target<<" in array:\n";
	
	int iterSearch = ArrayUtils::IterativeSearch<myType, len>(sorted, target);
	cout<<"result of iterative search is "<<iterSearch<<endl;
	
	int binSearch = ArrayUtils::RecursiveBinarySearch<myType, len>(sorted, target);
	cout<<"result of recursive binary search is "<<binSearch<<endl;

	binSearch = ArrayUtils::IterativeBinarySearch<myType, len>(sorted, target);
	cout<<"result of iterative binary search is "<<binSearch<<endl;
}
