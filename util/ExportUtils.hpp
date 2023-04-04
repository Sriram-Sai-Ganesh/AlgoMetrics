#pragma once
#include <iostream>
#include <cstdlib>

#include "../util/Constants.hpp"
#include "../util/TestRunner.hpp"
#include "../util/HelperUtils.hpp"

#include "../class/BinaryTree.hpp"
#include "../class/Matrix.hpp"

using namespace std;

const string outputFolder = "data/";

namespace ExportUtils{


namespace{
	ofstream openFile(string name){
		ofstream file;
		file.open(outputFolder+name);
		// assert(file);
		return file;
	}
}


template<class T>
void ExportMatrixToCSV(Matrix<T> m, string fileName = "matrix.csv"){
	ofstream file = openFile(fileName);
	for(int i=0;i<m.Rows();i++){
		for(int j=0;j<m.Columns()-1;j++){
			file<<m(i,j)<<", ";
		}
		file<<m(i, m.Columns()-1)<<"\n";
	}
	file.close();
	return;
}



} // end namespace