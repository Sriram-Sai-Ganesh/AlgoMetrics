#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#include "../inc/ArrayUtils.hpp"
#include "../inc/HelperUtils.hpp"
#include "../inc/ExecTimer.hpp"
#include "../inc/SinglyLinkedList.hpp"
#include "../inc/DoublyLinkedList.hpp"

typedef int myType;					// type of variable

using namespace std;
// output stream
ostream &out = cout;

void RunSinglyLinkedList(){
	out<<"\nSinglyLinkedList Tests: \n";
	SinglyLinkedList<myType> link;
	link.Add(1);
	link.Add(2);
	link.Add(3);
	link.Add(4);
	link.Add(5);
	link.Add(6);
	link.Add(7);
	link.Add(8);
	link.Add(9);
	HelperUtils::PrintSinglyLinkedList<myType>(link);	
	out<<"\n3rd index node is "<<link(3)<<endl;
	HelperUtils::PrintSinglyLinkedList<myType>(link);	
	link.RemoveNode(4);
	link.RemoveNode(2);
	out<<"\n2nd index node is "<<link(2)<<endl;
	HelperUtils::PrintSinglyLinkedList<myType>(link);
	endl(out);
}

void RunDoublyLinkedList(){
	out<<"\nDoublyLinkedList Tests: \n";
	DoublyLinkedList<myType> link;
	link.Add(1);
	link.Add(2);
	link.Add(3,2);
	link.Add(4,3);
	link.Add(6,4);
	link.Add(5,4);
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	
	out<<"3rd index of data is "<<link(3)<<":\n";
	out<<"4th index of data is "<<link(4)<<":\n";
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	link.RemoveNode(4);
	link.RemoveNode(3);
	link.Add(7);
	link.Add(8);
	link.Add(4,3);
	link.Add(9);
	out<<"5th index of data is "<<link(5)<<":\n";
	HelperUtils::PrintDoublyLinkedList<myType>(link);	
	link.Add(5,4);
	out<<"2nd index of data is "<<link(2)<<":\n";
	HelperUtils::PrintDoublyLinkedList<myType>(link);
}

void RunSorterTests(){
	const size_t len = 10000;				// array length
	const size_t numIterations = 500;		// number of timers to run
	const unsigned char mu=230;		// ASCII 230 = 'µ'
	// file out stream
	ofstream csv;
	auto randArray = HelperUtils::GetUniformRandomArray<myType, len>(0, 3*len);		// initialize array
	// create a vector of pairs<string name, ExecTimer func>
	auto sorterList = HelperUtils::CreateSorterVector<myType, len>();
	
	// for each function timer, 
    for(auto sortTimer:sorterList) {
		
		// create array to store runtimes
		array<int, numIterations> timeArray;

		// call sortTimer 'numIterations' times
		for(int i=0;i<(int)numIterations;i++){
			auto arrCopy=randArray;	// avoid modifying original radom array
			timeArray[i]=sortTimer.second(arrCopy);	//second part of pair is the ExecTimer object
		}
		// sort the array of times
		ArrayUtils::TailRecursiveQuickSort<myType, numIterations>(timeArray);

		// open the CSV file
		csv.open("out/"+sortTimer.first+".csv", ios::out);
		// print the median 100 values to the csv file
		out<<sortTimer.first<<":\n";
		// calculate average
		float sum=0;
		for(int i=10;i<(int)numIterations-10;i++){
			out<<timeArray[i]<<" "<<mu<<" seconds\n";
			csv<<timeArray[i]<<"\n";
			sum+=timeArray[i];
		}
		// print to console
		sum/=(numIterations-20.0);
		out<<"\nAverage of the median "<<(numIterations-20)<<" runs is "<<sum<<" "<<mu<<" seconds.";
		
		csv.close();
	}
	out<<"done\n";
	// endl(out, 2);
}

int main()
{
	// RunSorterTests();
	// RunSinglyLinkedList();
	RunDoublyLinkedList();
	return 0;
}