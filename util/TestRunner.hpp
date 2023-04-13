#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#include "../util/Constants.hpp"
#include "../util/ArrayUtils.hpp"
#include "../util/HelperUtils.hpp"
#include "../util/ExecTimer.hpp"
#include "../util/ExportUtils.hpp"

#include "../class/SinglyLinkedList.hpp"
#include "../class/DoublyLinkedList.hpp"
#include "../class/Queue.hpp"
#include "../class/Stack.hpp"
#include "../class/ArrayList.hpp"
#include "../class/Matrix.hpp"
#include "../class/IGraph.hpp"
#include "../class/ITree.hpp"
#include "../class/BinaryTree.hpp"
#include "../class/BinaryTree2.hpp"
#include "../class/BinarySearchTree.hpp"

const size_t len = 50;				// array length

// output stream
ostream &out = cout;
namespace TestRunner{
		
	void RunSorterTests(){
		const size_t numIterations = 100;		// number of timers to run
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
			ArrayUtils::TailRecursiveQuickSort<int, numIterations>(timeArray);

			// open the CSV file
			csv.open("out/"+sortTimer.first+".csv", ios::out);
			// print the median 100 values to the csv file
			out<<sortTimer.first<<":\n";
			// calculate average
			float sum=0;
			for(int i=10;i<(int)numIterations-10;i++){
				out<<timeArray[i]<<" "<<mu<<",  ";
				csv<<timeArray[i]<<"\n";
				sum+=timeArray[i];
			}
			// print to console
			sum/=(numIterations-20.0);
			out<<"\nAverage of the median "<<(numIterations-20)<<" runs is "<<sum<<" "<<mu<<" seconds.\n";
			
			csv.close();
		}
		endl(out);
	}

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
		out<<"3rd index node is "<<link(3)<<endl;
		HelperUtils::PrintSinglyLinkedList<myType>(link);	
		link.Remove(4);
		link.Remove(2);
		out<<"2nd index node is "<<link(2)<<endl;
		HelperUtils::PrintSinglyLinkedList<myType>(link);
		endl(out);
		
		out<<"Test initializing SLL with array:\n";
		// test initializing DLL with array
		auto arr = HelperUtils::GetUniformArray<myType, len>();
		auto ll = DoublyLinkedList<myType>::Initialize(arr);
		HelperUtils::PrintDoublyLinkedList(ll);
		endl();
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
		link.Remove(4);
		link.Remove(3);
		link.Add(7);
		link.Add(8);
		link.Add(4,3);
		link.Add(9);
		out<<"5th index of data is "<<link(5)<<":\n";
		HelperUtils::PrintDoublyLinkedList<myType>(link);	
		link.Add(5,4);
		out<<"2nd index of data is "<<link(2)<<":\n";
		HelperUtils::PrintDoublyLinkedList<myType>(link);
		
		out<<"Test initializing DLL with array:\n";
		// test initializing DLL with array
		auto arr = HelperUtils::GetUniformArray<myType, len>();
		auto ll = DoublyLinkedList<myType>::Initialize(arr);
		HelperUtils::PrintDoublyLinkedList(ll);
		endl();
	}

	void RunQueue(){
		out<<"Test Queue:\n";
		// test initializing DLL with array
		auto arr = HelperUtils::GetUniformArray<myType, len>();
		Queue<myType> q;
		q = Queue<myType>::Initialize(arr);
		cout<<"Is Queue empty?: "<<q.IsEmpty()<<endl;
		q.Enqueue(50);
		cout<<"[ ";
		while(q.Size()>0)
			cout<<q.Dequeue()<<" ";
		cout<<"]";
		endl();
		cout<<"Is Queue empty?: "<<q.IsEmpty()<<endl;
		endl();
	}

	void RunStack(){
		out<<"Test Stacks:\n";
		// test initializing DLL with array
		auto arr = HelperUtils::GetUniformArray<myType, len>();
		
		Stack<myType> stack;
		stack = Stack<myType>::Initialize(arr);
		cout<<"Is Stack empty?: "<<stack.IsEmpty()<<endl;
		stack.Push(50);
		cout<<"[ ";
		while(stack.Size()>0)
			cout<<stack.Pop()<<" ";
		cout<<"]";
		endl();
		cout<<"Is Stack empty?: "<<stack.IsEmpty()<<endl;
		endl();
	}

	void RunArrayList(){
		out<<"Test ArrayLists.\n";
		ArrayList<myType> arr;
		out<<"Initial table limit is "<<arr.Limit()<<endl;
		out<<"Inserting 100 elements.\n";
		for(int i=0; i<100; i++){
			arr.Insert(i);
		}

		out<<"ArrayList length = "<<arr.Length()<<"\n";
		out<<"Current table limit is "<<arr.Limit()<<endl;
		out<<"Printing ArrayList:\n";
		for(int i=0;i<arr.Length();i++){
			out<<arr(i)<<" ";
		}
		endl();
		out<<"Inserting 101st element.\n";
		arr.Insert(100);
		out<<"Current table limit is "<<arr.Limit()<<endl;
		out<<"Removing 101st element.\n";
		arr.Remove();
		out<<"Current table limit is "<<arr.Limit()<<endl;
		out<<"Inserting random 100 elements."<<endl;
		auto ar= HelperUtils::GetRandomArray<myType, len>(0,10000);
		arr.Initialize(ar);
		out<<"Printing ArrayList:\n";
		for(int i=0;i<arr.Length();i++){
			out<<arr(i)<<" ";
		}
		endl(2);
	}

	void RunMatrix(){
		out<<"Test Matrices.\n";
		const int rows=5, columns=5;
		out<<"Creating uniform random matrix:\n";
		auto matrix = HelperUtils::CreateUniformRandomMatrix<myType, rows, columns>();
		out<<"Printing Matrix:\n";
		HelperUtils::PrintMatrix<myType>(matrix);
		cout<<"Calling Transpose:\n";
		auto result = matrix.Transpose();
		out<<"Result is \n";
		HelperUtils::PrintMatrix<myType>(result);

		out<<"Creating random new matrix:\n";
		auto randMatrix=HelperUtils::CreateUniformRandomMatrix<myType, rows, columns+2>();
		HelperUtils::PrintMatrix<myType>(randMatrix);
		auto product=matrix.Multiply(randMatrix);
		out<<"Product of original matrix and new matrix is:\n";
		HelperUtils::PrintMatrix<myType>(product);
		out<<"Original Matrix:\n";
		HelperUtils::PrintMatrix<myType>(matrix);
		out<<"Naive Squaring: \n";
		auto naiveSquare=matrix.NaivePower(2);
		HelperUtils::PrintMatrix<myType>(naiveSquare);

		out<<"Fast Squaring: \n";
		auto fastSquare=matrix.Power(2);
		HelperUtils::PrintMatrix<myType>(fastSquare);
		endl();

		out<<"Testing LU Decomposition:\nRandom matrix is\n";
		const int squareMatrixSide=20;
		auto squareMatrix=HelperUtils::CreateRandomMatrix<myType, squareMatrixSide, squareMatrixSide>(10,500);
		HelperUtils::PrintMatrix<myType>(squareMatrix);
		out<<"Running LUDecomposition: \n";
		auto lowerUpperPair = squareMatrix.LUDecomposition();

		
		auto first = lowerUpperPair.first;
		auto second = lowerUpperPair.second;
		out<<"Lower matrix is: \n";
		HelperUtils::PrintMatrix<double>(first);
		out<<"Upper matrix is: \n";
		HelperUtils::PrintMatrix<double>(second);
		auto shouldBeOriginal = first.Multiply(second);
		out<<"Product of lower and upper is \n";
		HelperUtils::PrintMatrix<double>(shouldBeOriginal);
		ExportUtils::ExportMatrixToCSV(shouldBeOriginal, "test.csv");	
		endl();

	}

	void RunBinaryTree(){
		out<<"Test BinaryTrees:\nInitial value = ";
		BinaryTree<myType> test;
		out<<test.Value;
		out<<"\nHeight is "<<test.Height()<<endl;
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;
		out<<"Inserting 7"<<endl;
		test.Insert(7);
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;
		out<<"Inserting 8"<<endl;
		test.Insert(8);
		out<<"Inserting 9"<<endl;
		test.Insert(9);
		out<<"Check if contains 9:  "<<test.Contains(9)<<endl;
		out<<"Inserting 10"<<endl;
		test.Insert(10);
		out<<"Height is "<<test.Height()<<endl;
		out<<"Total number of children of root is  "<<test.NumberOfChildren()<<endl;
		out<<"Total tree size is "<<test.Size()<<endl;
		out<<"Check if contains 0:  "<<test.Contains(0)<<endl;
		out<<"Check if contains 5:  "<<test.Contains(5)<<endl;
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;

		ExportUtils::ExportBinaryTreeToCSV<myType>(test);
	}

	void RunBinarySearchTree(){
		out<<"Test BinarySearchTrees:\nInitial value = ";
		BinarySearchTree<myType> test;
		test.Value=7;
		out<<test.Value;
		out<<"\nHeight is "<<test.Height()<<endl;
		out<<"Check if contains 3:  "<<test.Contains(3)<<endl;
		out<<"Inserting 3"<<endl;
		test.Insert(3);
		out<<"Check if contains 3:  "<<test.Contains(3)<<endl;
		out<<"Inserting 8"<<endl;
		test.Insert(8);
		out<<"Inserting 9"<<endl;
		test.Insert(9);
		out<<"Check if contains 9:  "<<test.Contains(9)<<endl;
		out<<"Inserting 0"<<endl;
		test.Insert(0);
		out<<"Height is "<<test.Height()<<endl;

		out<<"Inserting 5"<<endl;
		test.Insert(5);
		out<<"Inserting 6"<<endl;
		test.Insert(6);
		out<<"Height is "<<test.Height()<<endl;
		out<<"Total number of children of root is  "<<test.NumberOfChildren()<<endl;
		out<<"Total tree size is "<<test.Size()<<endl;
		out<<"Check if contains 0:  "<<test.Contains(0)<<endl;
		out<<"Check if contains 5:  "<<test.Contains(5)<<endl;
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;

		ExportUtils::ExportBinaryTreeToCSV<myType>(test);
	}

	void RunBinaryTree2(){
		out<<"Test BinaryTrees2:\nInitial value = ";
		BinaryTree2<myType> test = BinaryTree2<myType>();
		out<<"Root is "<<test.rootValue()<<endl;
		out<<"Height is "<<test.Height()<<endl;
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;
		out<<"Inserting 7"<<endl;
		test.Insert(7);
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;
		out<<"Inserting 8"<<endl;
		test.Insert(8);
		out<<"Inserting 9"<<endl;
		test.Insert(9);
		out<<"Check if contains 9:  "<<test.Contains(9)<<endl;
		out<<"Inserting 10"<<endl;
		test.Insert(10);
		out<<"Height is "<<test.Height()<<endl;
		out<<"Root is "<<test.rootValue()<<endl;
		out<<"Number of direct root children = "<<test.NumberOfChildren()<<endl;
		out<<"Total tree size is "<<test.Size()<<endl;
		out<<"Check if contains 0:  "<<test.Contains(0)<<endl;
		out<<"Check if contains 5:  "<<test.Contains(5)<<endl;
		out<<"Check if contains 7:  "<<test.Contains(7)<<endl;

		ExportUtils::ExportBinaryTree2ToCSV<myType>(test);
	}
}	// end namespace