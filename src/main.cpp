#include <iostream>
#include <array>
#include "../inc/SearchUtils.hpp"
#include "../inc/SortUtils.hpp"
#include "../inc/HelperUtils.hpp"

typedef int currentType;
const uint64_t seed=33489857205;	// rng seed
const size_t len = 50;					// array length

using namespace std;
int main()
{
	currentType min=-100, max=100;

	cout<<"creating random array: \n";
	array<currentType, len> ar = HelperUtils::GetRandomArray<currentType, len>(min, max);
	cout<<"\nprinting arr:\n";
	HelperUtils::PrintArray<currentType, len>(ar);
	cout<<endl;
	cout<<"sorting...\n";
	array<currentType, len> sorted = SortUtils::BubbleSort<currentType, len>(ar);
	HelperUtils::PrintArray<currentType, len>(sorted);
	return 0;
}