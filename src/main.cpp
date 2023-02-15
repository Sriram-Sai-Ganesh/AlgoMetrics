#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"
#include "../inc/ExecTimer.hpp"
#include "../inc/SinglyLinkedList.hpp"
#include "../inc/DoublyLinkedList.hpp"

typedef int myType;					// type of variable
const size_t len = 10000;				// array length
const size_t numIterations = 120;				// number of timers to run
const unsigned char mu=230;		// 230 : µ

using namespace std;

void trySinglyLinkedList(){
	cout<<"LinkedLists: \n";
	SinglyLinkedList<myType> link;
	link.Add(1);
	link.Add(2);
	link.Add(3);
	link.Add(4);
	link.Add(5);
	HelperUtils::PrintSinglyLinkedList<myType>(link);	
	
	cout<<"\n3rd index node is "<<link(3)<<endl;
	HelperUtils::PrintSinglyLinkedList<myType>(link);	
	link.RemoveNode(4);
	link.RemoveValue(2);
	cout<<"\n2nd index node is "<<link(2)<<endl;
	HelperUtils::PrintSinglyLinkedList<myType>(link);	
	endl(cout);
}


void tryDoublyLinkedList(){
	cout<<"LinkedLists: \n";
	DoublyLinkedList<myType> link;
	link.Add(1);
	link.Add(2);
	link.Add(3);
	link.Add(4);
	link.Add(5);
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	
	cout<<"\n3rd index node is "<<link(3)<<endl;
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	link.RemoveNode(4);
	link.RemoveValue(2);
	cout<<"\n2nd index node is "<<link(2)<<endl;
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	endl(cout);
}

int main()
{
	// output stream
	ostream &out = cout;
	// set array value bounds
	myType min=0, max=len*3;
	// initialize array
	auto randArray = HelperUtils::GetUniformRandomArray<myType, len>(min, max-1);
	// create an ExecTimer object
	auto funcTimer = CreateTimer(ArrayUtils::QuickSort<myType, len>);
	
	// print initial array.
	// (comment out if array is large)
	// HelperUtils::PrintArray<myType, len>(randArray, out); 
	// endl(out, 2);

	// store times in an array
    array<int, numIterations> timeArray;
	// run the timer 'numIterations' times
	out<<"\nRunning timers...\n";
	auto unsorted = randArray;
	for(int i=0;i< (int)numIterations;i++){
		unsorted=randArray;
		int result = funcTimer(unsorted);
		// out<<result<<" "<<mu<<"s\n";
		timeArray[i]=result;
	}
	// sort the array of times
	ArrayUtils::TailRecursiveQuickSort<myType, numIterations>(timeArray);
	// print final array
	// out<<"\nFinal:\n";	// comment out if array is large
	// HelperUtils::PrintArray<myType, len>(unsorted);
	out<<"list of times is \n";
	float sum=0;
	for(int i=10;i<(int)numIterations-10;i++){
		cout<<timeArray[i]<<" "<<mu<<" seconds\n";
		sum+=timeArray[i];
    }
	sum/=(numIterations-20.0);

	out<<"\nAverage of median "<<(numIterations-20)<<" runs is "<<sum<<" "<<mu<<" seconds.";

	
	endl(out, 2);

	// trySinglyLinkedList();
	// tryDoublyLinkedList();
	return 0;
}