#include <iostream>
#include <array>
#include "../inc/SearchUtils.hpp"
#include "../inc/SortUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int myType;				// type of variable in array
const size_t len = 100;					// array length

using namespace std;
int main()
{
	myType min=-10, max=70;
	myType target = HelperUtils::GetRandomNumber<myType>(min, max);
	endl(2);

	array<myType, len> ar = HelperUtils::GetRandomArray<myType, len>(min, max);
	HelperUtils::PrintArray<myType, len>(ar);
	endl(2);
	
	cout<<"After BubbleSort:\n";
	ar = SortUtils::BubbleSort<myType, len>(ar);
	HelperUtils::PrintArray<myType, len>(ar);
	endl(2);


	cout<<"Searching for "<<target<<" in array:\n";
	
	int iterSearch = SearchUtils::IterativeSearch<myType, len>(ar, target);
	cout<<"result of iterative search is "<<iterSearch<<endl;
	
	int binSearch = SearchUtils::RecursiveBinarySearch<myType, len>(ar, target);
	cout<<"result of recursive binary search is "<<binSearch<<endl;

	binSearch = SearchUtils::IterativeBinarySearch<myType, len>(ar, target);
	cout<<"result of iterative binary search is "<<binSearch<<endl;


	return 0;
}