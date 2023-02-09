#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"
#include "../inc/ExecTimer.hpp"

typedef int myType;					// type of variable
const size_t len = 100;				// array length
const char mu=230;		// 230 : µ

using namespace std;

int test(int num){
	// cout<<"success "<<num<<endl;
	double sum=0;
	for(int i=0;i<num;i++){sum++;}
	return 0;
}

int main()
{
	// output stream
	ostream &out = cout;
	// set array value bounds
	myType min=0, max=len*3;
	// initialize array
	
	auto randArray = HelperUtils::GetUniformRandomArray<myType, len>(min, max-1);
	
	auto funcTimer = CreateTimer(ArrayUtils::QuickSort<myType, len>);
	out<<"\nInitial:\n";
	HelperUtils::PrintArray<myType, len>(randArray, out);
	endl(2);

	auto unsorted = randArray;
	int iterations = 100;
	for(int i=0;i<iterations;i++){
		unsorted=randArray;
		cout<<funcTimer(unsorted)<<" "<<mu<<"s\n";
	}
	
	out<<"\nFinal:\n";
	HelperUtils::PrintArray<myType, len>(unsorted);
	endl();
	return 0;
}