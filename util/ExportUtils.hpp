#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../util/Constants.hpp"
#include "../util/TestRunner.hpp"
#include "../util/HelperUtils.hpp"

#include "../class/Matrix.hpp"
#include "../class/BinaryTree.hpp"
#include "../class/BinarySearchTree.hpp"

using namespace std;

const string outputFolder = "data/";

/// @brief namespace to streamline exporting data strcutures to csv files
namespace ExportUtils{

/// @brief anon private namespace for local helper functions
namespace{
	ofstream openFile(string name){
		ofstream file;
		file.open(outputFolder+name);
		// assert(file);
		return file;
	}
}

/// @brief export Matrix object to csv file
/// @tparam T type of elements in matrix
/// @param matrix matrix
/// @param fileName destination file name. "matrix.csv" by default. 
template<class T>
static void ExportMatrixToCSV(Matrix<T> matrix, string fileName = "matrix.csv"){
	ofstream file = openFile(fileName);
	for(size_t i=0;i<matrix.Rows();i++){
		for(size_t j=0;j<matrix.Columns()-1;j++){
			file<<matrix(i,j)<<", ";
		}
		file<<matrix(i, matrix.Columns()-1)<<"\n";
	}
	file.close();
	return;
}


/// @brief export BinaryTree object to csv file
/// @tparam T type of elements in BinaryTree
/// @param tree BinaryTree to export
/// @param order 0->pre-order, 1->in-order, 2->post-order
/// @param fileName destination file name. "tree.csv" by default. 
template<class T>
static void ExportBinaryTreeToCSV(BinaryTree<T> tree, int order=1, string fileName = "tree.csv"){
	assert(order<=3);
	assert(order>0);

	ofstream file = openFile(fileName);
	// file<<returnTraversalString(tree);
	file.close();
	return;
}

template<class T>
string returnTraversalString(BinaryTree<T> tree, int order=0){
	string part1, part2, part3;
	part1=(tree.Left())?TraversalString(tree.Left(), order):"0";
	part2=tree.data();
	part3=(tree.Right())?TraversalString(tree.Right(), order):"0";

	switch(order){
		case 1:
			return part1+part2+part3;
		case 2:
			return part2+part1+part3;
		case 3:
			return part3+part2+part1;
		default:
			return "ExportUtils: returnTraversalString: ERROR";
	}
}


} // end namespace