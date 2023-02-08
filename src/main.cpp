#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"
#include "../inc/TimerUtils.hpp"

typedef int myType;					// type of variable in array
const size_t len = 100;				// array length

using namespace std;

int main()
{
	// output stream
	ostream &out = cout;
	// set array value bounds
	myType min=0, max=len*3;
	// initialize array
	auto randArray = HelperUtils::GetUniformRandomArray<myType, len>(min, max-1);

	out<<"Initial:\n";
	HelperUtils::PrintArray<myType, len>(randArray, out);
	endl(2);

	auto unsorted = randArray;
	int iterations = 100;
	for(int i=0;i<iterations;i++){
		unsorted=randArray;
		// QuickSort > MergeSort
		TimerUtils::SortTimer<myType, len>(ArrayUtils::MergeSort<myType, len>, unsorted);
	}
	
	out<<"\nFinal:\n";
	HelperUtils::PrintArray<myType, len>(unsorted);
	
	endl();
	return 0;
}

void testSortUtils(array<myType, len> randArray, ostream &out=cout){

	// BubbleSort elements
	auto bubbleSorted=randArray;
	ArrayUtils::BubbleSort<myType, len>(bubbleSorted);
	// print result
	out<<"After BubbleSort:\n";
	HelperUtils::PrintArray<myType, len>(bubbleSorted);
	endl(2);

	// SelectionSort elements
	auto selectionSorted=randArray;
	ArrayUtils::SelectionSort<myType, len>(selectionSorted);
	// print result
	out<<"After SelectionSort:\n";
	HelperUtils::PrintArray<myType, len>(selectionSorted);
	endl(2);

	// InsertionSort elements
	auto insertionSorted=randArray;
	ArrayUtils::InsertionSort<myType, len>(insertionSorted);
	// print result
	out<<"After InsertionSort:\n";
	HelperUtils::PrintArray<myType, len>(insertionSorted);
	endl(2);

	// QuickSort elements
	auto quickSorted=randArray;
	ArrayUtils::QuickSort<myType, len>(quickSorted);

	// MergeSort elements
	auto mergeSorted=randArray;
	ArrayUtils::MergeSort<myType, len>(mergeSorted);
	// print result
	out<<"After MergeSort:\n";
	HelperUtils::PrintArray<myType, len>(mergeSorted);
	endl(2);
}

void testSearchUtils(array<myType, len> sorted, myType target, ostream &out=cout){

	out<<"sorted array is \n";
	HelperUtils::PrintArray<myType, len>(sorted);
	// perform 3 search operations
	out<<"Searching for "<<target<<" in array:\n";
	
	int iterSearch = ArrayUtils::IterativeSearch<myType, len>(sorted, target);
	out<<"result of iterative search is "<<iterSearch<<endl;
	
	int binSearch = ArrayUtils::RecursiveBinarySearch<myType, len>(sorted, target);
	out<<"result of recursive binary search is "<<binSearch<<endl;

	binSearch = ArrayUtils::IterativeBinarySearch<myType, len>(sorted, target);
	out<<"result of iterative binary search is "<<binSearch<<endl;
}
