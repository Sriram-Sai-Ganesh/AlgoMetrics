#include <iostream>
#include <array>
#include "../inc/SearchUtils.hpp"
#include "../inc/SortUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int currentType;
const double seed=12345;
const size_t len = 50;

using namespace std;
int main()
{
	// int ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	// int ar2[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	// int len=sizeof(ar)/sizeof(ar[0]);

	// cout<<"iterative search: result is "<<SearchUtils::IterativeSearch<int>(ar, len, 11)<<endl;

	// SortUtils::BubbleSort<int>(ar2, len);

	// cout<<"bubble sort: result is ";
	
	// for(int i:ar2) cout<<i<<" ";

	int min=0, max=50;

	array<currentType, len> ar = HelperUtils::GetUniformArray<currentType, len>(min, max);	
	HelperUtils::PrintArray<currentType, len>(ar);

	return 0;
}