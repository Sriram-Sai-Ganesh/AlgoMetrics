#include <iostream>
#include <array>
#include "../inc/SearchUtils.hpp"
#include "../inc/SortUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int currentType;				// type of variable in array
const size_t len = 100;					// array length
const uint64_t seed=33489857205;		// prng seed

using namespace std;
int main()
{
	currentType min=-100, max=100;
	endl(2);

	array<currentType, len> ar = HelperUtils::GetRandomArray<currentType, len>(min, max);
	HelperUtils::PrintArray<currentType, len>(ar);
	endl(2);
	
	cout<<"After BubbleSort:\n";
	ar = SortUtils::BubbleSort<currentType, len>(ar);
	HelperUtils::PrintArray<currentType, len>(ar);
	endl(2);


	cout<<"Searching:\n";
	
	int iterSearch = SearchUtils::IterativeSearch<currentType, len>(ar, 2);
	cout<<"result of iterative search is "<<iterSearch<<endl;
	
	int binSearch = SearchUtils::RecursiveBinarySearch<currentType, len>(ar, 2);
	cout<<"result of recursive binary search is "<<binSearch<<endl;

	binSearch = SearchUtils::IterativeBinarySearch<currentType, len>(ar, 2);
	cout<<"result of iterative binary search is "<<binSearch<<endl;


	return 0;
}