#pragma once
#include <cstdlib>	// malloc and free
#include <iterator>	// TODO std::iterator
#include <array>	// AddAll(array)

using namespace std;

/// @brief implementation of Matrix with 2D Arrays
/// @tparam T type of data in the ArrayList
template<class T>
class Matrix{

private:

/// @brief private 2D array
T** ar;
int rows;
int cols;

public:
/// @brief constructor. mallocs space for array.
Matrix<T>(int row, int col) {
	rows=row;
	cols=col;
	ar = (T**)malloc(sizeof(T*)*rows);
	for(int i=0;i<rows;i++){
		ar[i]=(T*)malloc(sizeof(T)*cols);
	}
}

// TODO: implement destructor, this.multiply(matrix)

/// @brief matrix transpose
/// @return returns transpose of this
decltype(auto) Transpose(){
	auto result = Matrix<T>(cols,rows);
	for(int i=0;i<rows*cols;i++){
		result(i/cols, i%cols) = (*this)(i%rows, i/rows);
	}
	return result;
}

/// @brief get number of rows in this matrix.
/// @return size_t numrows.
size_t Rows() {
	return rows;
}

/// @brief get number of columns in this matrix.
/// @return size_t numrows.
size_t Columns() {
	return cols;
}

/// @brief operator() overload for matrix access
/// @param rowIndex row to get element from
/// @param colIndex column to get element from
/// @return value at index (row, column)
T operator()(size_t rowIndex, size_t colIndex)const{
	if(rowIndex<0 || rowIndex>=this->rows || colIndex<0 || colIndex>=this->cols){
		cerr<<"ERROR: Matrix(row, col): Index out of bounds.\n";
	}
	else return this->ar[rowIndex][colIndex];
}

/// @brief operator() overload for matrix assignment
/// @param rowIndex row to get reference to
/// @param colIndex column to get reference to
/// @return reference to index (row, column)
T& operator()(size_t rowIndex, size_t colIndex){
	if(rowIndex<0 || rowIndex>=this->rows || colIndex<0 || colIndex>=this->cols){
		cerr<<"ERROR: Matrix(row, col): Index out of bounds.\n";
	}
	else return this->ar[rowIndex][colIndex];
}
};