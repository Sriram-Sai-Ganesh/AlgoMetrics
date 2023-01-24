#include <iostream>
#include "../inc/SearchUtils.hpp"
#include "../inc/SortUtils.hpp"

using namespace std;
int main()
{
	int ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int ar2[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int length=sizeof(ar)/sizeof(ar[0]);

	cout<<"iterative search: result is "<<SearchUtils::IterativeSearch<int>(ar, length, 11)<<endl;

	SortUtils::BubbleSort<int>(ar2, length);

	cout<<"bubble sort: result is ";
	
	for(int i:ar2) cout<<i<<" ";
	
	return 0;
}