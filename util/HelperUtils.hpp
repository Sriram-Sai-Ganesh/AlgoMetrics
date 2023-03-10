#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <typeinfo>
#include <random>

#include "../util/ExecTimer.hpp"

#include "../class/SinglyLinkedList.hpp"
#include "../class/DoublyLinkedList.hpp"
#include "../class/Matrix.hpp"

using namespace std;

const unsigned seed=chrono::system_clock::now().time_since_epoch().count();		// prng seed
static random_device rd;
static mt19937 engine(rd());

namespace HelperUtils{

// print array 'arr' separated by ', '
template<class T, size_t len> 
void PrintArray(array<T, len> arr, ostream &out=cout)
{
	out<<"Printing array of "<<len<<" (type'"<<typeid(T).name()<<"').\n\t";
	out<<"[";
    for(size_t i=0;i<len-1;i++){
        out << arr[i] << ", ";
	}
	out<<arr[len-1]<<"]";
}


// print singly linked list 'link'
template<class T> 
void PrintSinglyLinkedList(SinglyLinkedList<T> link, ostream &out=cout){
	out<<"Printing SinglyLinkedList of length "<<link.Size()<<" (type'"<<typeid(T).name()<<"'):\n";
	out<<"[  ";
	for(auto h:link)
	{
		out<<h<<"  ";
	}
	out<<"]\n";
}


// print doubly linked list 'link'
template<class T> 
void PrintDoublyLinkedList(DoublyLinkedList<T> link, ostream &out=cout){
	
	out<<"Printing DoublyLinkedList of length "<<link.Size()<<" (type'"<<typeid(T).name()<<"'):\n";
	out<<"[  ";
	for(auto h:link){
		out<<h<<"  ";
	}
	out<<"]\n";
}

/// @brief print matrix with large brackets.
/// @tparam T class contained in matrix
/// @param mat object to print
/// @param out output stream, &cout by default.
template<class T>
void PrintMatrix(Matrix<T> mat, ostream &out=cout){
	unsigned char dash = 196;
	unsigned char line = 179;
	unsigned char topLeft = 218;
	unsigned char bottomLeft = 192;
	unsigned char topRight = 191;
	unsigned char bottomRight = 217;
	out<<topLeft<<dash;
	for(size_t i=0;i<=mat.Columns();i++)out<<"\t";
	out<<dash<<topRight<<endl;
	for(size_t i=0;i<mat.Rows();i++){
		out<<line<<"\t";
		for(size_t j=0;j<mat.Columns();j++){
			out<<mat(i,j)<<"\t";
		}
		out<<" "<<line<<endl;
	}

	out<<bottomLeft<<dash;
	for(size_t i=0;i<=mat.Columns();i++)out<<"\t";
	out<<dash<<bottomRight<<endl;
}

// returns array populated with random (INTEGRAL TYPE) T in range [min, max)
template <class T, size_t len, enable_if_t<std::is_integral_v<T>, int> = 0> 
array<T, len> GetRandomArray(T min, T max){
	array<T, len> result;
	uniform_int_distribution<T> distr(min, max);
	for (size_t i=0; i<result.size(); i++)
        result[i]=distr(engine);
	return result;
}

// returns array populated with random (FLOAT TYPE) T in range [min, max)
template <class T, size_t len,
enable_if_t<std::is_floating_point_v<T>, int> = 0> 
array<T, len> GetRandomArray(T min, T max){
	array<T, len> result;
	uniform_real_distribution<T> distr(min, max);
	for (size_t i=0; i<result.size(); i++)
        result[i]=distr(engine);
	return result;
}

// return random T (INTEGRAL TYPE) number in range [min,max]
template<class T, enable_if_t<std::is_integral_v<T>, int> = 0> 
T GetRandomNumber(T min, T max){
	uniform_int_distribution<T> distr(min, max);
	return distr(engine);
}
// return random T (FLOAT TYPE) number in range [min,max]
template<class T, enable_if_t<std::is_floating_point_v<T>, int> = 0> 
T GetRandomNumber(T min, T max){
	uniform_real_distribution<T> distr(min, max);
	return distr(engine);
}

// returns std::array populated with uniform distribution from [min, max]
template <class T, size_t len> 
array<T, len> GetUniformArray(T min=0, T max=len){
	array<T, len> result;
	for (size_t i=0; i<result.size(); i++)
        result[i] = min + ((max-min)*(i*1.0/result.size()));
	return result;	
}

// returns std::array with values uniform in [min, max) in random order.
template <class T, size_t len>
array<T, len> GetUniformRandomArray(T min=0, T max=len){
	auto result = GetUniformArray<T, len>(min, max);
	shuffle (begin(result), end(result), default_random_engine(seed));
	return result;
}

template<class T, size_t len>
decltype(auto) CreateSorterVector(){
	// create vector of (string,ExecTimers)
	vector<pair<string, ExecTimer<void (array<T, len> &)>>> result;
	result.push_back(make_pair("QuickSort", CreateTimer(ArrayUtils::QuickSort<T, len>)));
	result.push_back(make_pair("Tail Recursive QuickSort", CreateTimer(ArrayUtils::TailRecursiveQuickSort<T, len>)));
	result.push_back(make_pair("MergeSort", CreateTimer(ArrayUtils::MergeSort<T, len>)));
	return result;
}


template<class T, size_t rows, size_t cols>
decltype(auto) InitializeMatrix(array<T, rows*cols> ar){
	Matrix<T> m = Matrix<T>(rows, cols);
	for(size_t i = 0; i < rows;i++){
		for(size_t j = 0; j < cols;j++){
			m(i,j)=ar[i*rows+j];
		}
	}
	return m;
}

template<class T, size_t rows, size_t cols>
decltype(auto) CreateUniformMatrix(int low=0, int high=rows*cols){
	return InitializeMatrix<T, rows, cols>(GetUniformArray<T, rows*cols>());
}

template<class T, size_t rows, size_t cols>
decltype(auto) CreateUniformRandomMatrix(int low=0, int high=rows*cols){
	return InitializeMatrix<T, rows, cols>(GetUniformRandomArray<T, rows*cols>(low, high));
}

}		// end namespace


void printchar(char c,int count,ostream &out=cout){
	while(count--){
		out<<c;
	}
}
// print 'n' blank lines
void endl(int n=1, ostream &out=cout){
	printchar('\n',n,out);
}