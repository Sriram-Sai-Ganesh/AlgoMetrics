#include <iostream>
#include <array>
#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"
#include "../inc/ExecTimer.hpp"
#include "../inc/LinkedList.hpp"

typedef int myType;					// type of variable
const size_t len = 100;				// array length
const unsigned char mu=230;		// 230 : µ

using namespace std;

int main()
{
	// output stream
	ostream &out = cout;
	// set array value bounds
	myType min=0, max=len*3;
	// initialize array
	auto randArray = HelperUtils::GetUniformRandomArray<myType, len>(min, max-1);
	
	auto funcTimer = CreateTimer(ArrayUtils::TailRecursiveQuickSort<myType, len>);
	out<<"\nInitial:\n";
	// HelperUtils::PrintArray<myType, len>(randArray, out);
	endl(out, 2);

	auto unsorted = randArray;
	int iterations = 100;
	for(int i=0;i<iterations;i++){
		unsorted=randArray;
		cout<<funcTimer(unsorted)<<" "<<mu<<"s\n";
	}
	
	out<<"\nFinal:\n";
	HelperUtils::PrintArray<myType, len>(unsorted);
	endl(out, 3);

	tryLinkedLists();
	return 0;
}

void tryLinkedLists(){
	
	cout<<"LinkedLists: \n";
	SinglyLinkedList<myType> link;
	link.Add(1);
	link.Add(2);
	link.Add(3);
	link.Add(4);
	link.Add(5);
	HelperUtils::PrintLinkedList<myType>(link);	
	
	cout<<"\n3rd index node is "<<link(3)<<endl;
	HelperUtils::PrintLinkedList<myType>(link);	
	link.RemoveNode(4);
	link.RemoveValue(2);
	cout<<"\n2nd index node is "<<link(2)<<endl;
	HelperUtils::PrintLinkedList<myType>(link);	
	endl(cout);
}