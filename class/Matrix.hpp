#pragma once
#include <cstdlib>	// malloc and free
#include <cassert>	// assertions
#include <array>	// AddAll(array)

using namespace std;

/// @brief implementation of Matrix with 2D Arrays
/// @tparam T type of data in the ArrayList
template<class T>
class Matrix{

private:

/// @brief private 2D array
T** ar;
size_t rows;
size_t cols;

public:

/// @brief constructor. mallocs space for array.
Matrix<T>(int row, int col) {
	
	assert(row>0);
	assert(col>0);

	rows=row;
	cols=col;
	ar = (T**)malloc(sizeof(T*)*rows);
	for(size_t i=0;i<rows;i++){
		ar[i]=(T*)malloc(sizeof(T)*cols);
	}
}


/// @brief operator () overload for matrix access
/// @param rowIndex row to get element from
/// @param colIndex column to get element from
/// @return value at index (row, column)
T operator()(size_t rowIndex, size_t colIndex)const{
	assert(rowIndex < this->rows && colIndex < this->cols);
	return this->ar[rowIndex][colIndex];
}

/// @brief operator () overload for matrix assignment
/// @param rowIndex row to get reference to
/// @param colIndex column to get reference to
/// @return reference to index (row, column)
T& operator()(size_t rowIndex, size_t colIndex){
	// Index cannot be out of bounds."
	assert(rowIndex<this->rows && colIndex<this->cols);
	return this->ar[rowIndex][colIndex];
}

/// @brief operator * overload for matrix multiplication
/// @return this*mat
Matrix<T> operator*(Matrix<T> m1){
	return this->Multiply(m1);
}



/// @brief matrix transpose
/// @return returns transpose of this
Matrix<T> Transpose(){
	auto result = Matrix<T>(cols,rows);
	for(size_t i=0;i<rows*cols;i++){
		result(i/cols, i%cols) = (*this)(i%rows, i/rows);
	}
	return result;
}

/// @brief Matrix dot product
/// @param mat matrix multiplier
/// @return this*mat
Matrix<T> Multiply(Matrix<T> mat){

	// ensure dimensions are compatible
	assert(this->cols == mat.rows);
	Matrix<T> result = Matrix<T>(this->rows, mat.cols);
	for(size_t i = 0, lim=this->rows; i < lim;i++){
		for(size_t j = 0; j < mat.cols;j++){
			
			result(i,j)=0;
			for(size_t x=0,y=0;x<lim;x++,y++){
				result(i,j)+=(*(this))(i,x)*mat(y,j);
			}

		}
	}
	return result;
}

/// @brief Iterative matrix exponentiation
/// @param exp exponent
/// @return this^exp
Matrix<T> NaivePower(int exp){

	// ensure matrix is square
	assert(this->rows == this->cols);
	// positive powers only
	assert(exp>0);
	auto result=*this;
	while(--exp)result = result.Multiply(*(this));
	return result;
}

/// @brief Iterative matrix exponentiation
/// @param exp exponent
/// @return this^exp
Matrix<T> Square(){
	// ensure matrix is square
	assert(this->rows == this->cols);
	return (*this) * (*this);
}

/// @brief Matrix exponentiation with fast powering
/// @param exp exponent
/// @return this^exp
Matrix<T> Power(int exp){

	// ensure matrix is square
	assert(this->rows == this->cols);
	assert(exp>0);

	auto result=*this;
	for(int i=1;i<exp;){
		if(i*2<exp){
			result=result.Square();
			i*=2;
		}
		else return result*this->Power(exp-i);
	}
	return result;
}

/// @brief returns a zero matrix with side 'dim'
/// @param dim number of rows in zero matrix
/// @return dim x dim zero matrix
static Matrix<T> Zeroes(size_t dim) {
	Matrix<T> result = Matrix<T>(dim, dim);
	return result;
}

/// @brief returns an identity matrix with side 'dim'
/// @param dim number of rows in identity matrix
/// @return dim x dim identity matrix
static Matrix<T> Identity(size_t dim) {
	Matrix<T> result = Zeroes(dim);
	for(size_t i=0;i<dim;i++){
		result(i,i)=1;
	}
	return result;
}

/// @brief perform LUDecomposition on this and return result
/// @return std::pair of (lower, upper) triangular matrices 
/// code adapted from https://www.codingninjas.com/codestudio/library/doolittle-algorithm
decltype(auto) LUDecomposition(){

	// ensure matrix is square
	assert(this->rows==this->cols);

	// create result matrices
	size_t side = this->cols;
	auto matrix = *this;
	auto lower = Matrix<double>::Zeroes(side);
	auto upper = Matrix<double>::Zeroes(side);

	// perform LU Decomposition
    for (size_t i = 0; i < side; i++){
        // Upper Triangular
        for (size_t k = i; k < side; k++){
            // Summation of L(i, j) * U(j, k)
            double sum = 0;
            for (size_t j = 0; j < i; j++){
                sum += (lower(i, j) * upper(j, k));
            }
			// Evaluating U(i, k)
            upper(i, k) = matrix(i, k) - sum;
        }
        // Lower Triangular
        for (size_t k = i; k < side; k++){
            if (i == k){
                lower(i, i) = 1; // Diagonal as 1
			}
			else{
                // Summation of L(k, j) * U(j, i)
                double sum = 0;
                for (size_t j = 0; j < i; j++){
                    sum += (lower(k, j) * upper(j, i));
				}
				// Evaluating L(k, i)
                lower(k, i) = (matrix(k, i) - sum) / upper(i, i);
            }
        }
    }
	// return tuple result
	return make_pair(lower, upper);
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

};