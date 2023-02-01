#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int myType;					// type of variable in array
const size_t len = 100;				// array length

using namespace std;

void testSearchUtils(array<myType, len> sorted, myType target);
void testSortUtils(array<myType, len> array);


int main()
{
	// set arrray value bounds
	myType min=-10, max=700;

	// initialize array
	auto randArray = HelperUtils::GetRandomArray<myType, len>(min, max-1);
	HelperUtils::PrintArray<myType, len>(randArray);
	endl(2);
	
	testSortUtils(randArray);


	auto sortedArray = randArray;
	// ArrayUtils::BogoSort(sortedArray);
	// cout<<"After BogoSort:\n";
	// HelperUtils::PrintArray<myType, len>(sortedArray);
	ArrayUtils::SelectionSort(sortedArray);

	int index = HelperUtils::GetRandomNumber<int>(0, len-1);
	testSearchUtils(sortedArray, sortedArray[index]);

	return 0;
}


void testSortUtils(array<myType, len> randArray){

	// BubbleSort elements
	auto bubbleSorted=randArray;
	ArrayUtils::BubbleSort<myType, len>(bubbleSorted);
	// print result
	cout<<"After BubbleSort:\n";
	HelperUtils::PrintArray<myType, len>(bubbleSorted);
	endl(2);

	// SelectionSort elements
	auto selectionSorted=randArray;
	ArrayUtils::SelectionSort<myType, len>(selectionSorted);
	// print result
	cout<<"After SelectionSort:\n";
	HelperUtils::PrintArray<myType, len>(selectionSorted);
	endl(2);

	// InsertionSort elements
	auto insertionSorted=randArray;
	ArrayUtils::InsertionSort<myType, len>(insertionSorted);
	// print result
	cout<<"After InsertionSort:\n";
	HelperUtils::PrintArray<myType, len>(insertionSorted);
	endl(2);

	// QuickSort elements
	auto quickSorted=randArray;
	ArrayUtils::QuickSort<myType, len>(quickSorted);
	// print result
	cout<<"After QuickSort:\n";
	HelperUtils::PrintArray<myType, len>(quickSorted);
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
