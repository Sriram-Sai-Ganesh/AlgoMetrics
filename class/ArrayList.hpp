#pragma once

#include <cstdlib>	// malloc and free
#include <array>	// AddAll(array)
#include <typeinfo>	// typechecking
#include <cassert>	// type errors
using namespace std;

/// @brief implementation of variable-length array using table doubling
/// @tparam T type of data in the ArrayList
template<class T>
class ArrayList{

private:

// implementation-specific constants
const int defaultSize=50;
const float doubleSizeThreshold=0.5;
const float halveSizeThreshold=0.25;


/// @brief private array
T* array;
int limit;
int last;

/// @brief allocate array space in memory for table doubling
/// @param size number of elements in allocated array
/// @return pointer to allocated array
T* allocateArray(int size){
	T* result = (T*)malloc(sizeof(T)*size);
	if(result==NULL)
	{
		cerr<<"ERROR: ArrayList: failed to allocate array of size "<<size<<endl;
	}
	return result;
}

/// @brief handle table doubling and move elements to new array
void handleDoubling(){
	if(last>=(int)limit*doubleSizeThreshold){
		// double the limit of the array and copy elements over
		T* temp = array;
		array = allocateArray(limit*2);
		memcpy(array,temp,last*sizeof(T));
		free(temp);
		limit*=2;
	}
}

/// @brief handle table halving and move elements to new array
void handleHalving(){
	if(limit/2 >= defaultSize && last<=(int)limit*halveSizeThreshold){
		// halve the limit of the array and copy elements over
		T* temp = array;
		array = allocateArray(limit/2);
		memcpy(array,temp,last*sizeof(T));
		free(temp);
		limit/=2;
	}
}

public:
/// @brief constructor.
ArrayList<T>() {
	limit=defaultSize;
	last=0;
	array = allocateArray(limit);
}


/// @brief insert element to position 'index' in the ArrayList.
/// @param value 
void Insert(T value, int index) {
	handleDoubling();
	if(index>last || index<0 || index>=limit){ 
		cerr<<"ERROR: ArrayList.Insert(): Index must be in range [0, " <<last<<"], "<<index<<" invalid."<<endl;
		return;
	}
	for(int i=last;i>index;i--){
		array[i]=array[i-1];
	}
	array[index] = value;
	this->last++;
}

/// @brief Insert value at end of this ArrayList.
/// @param value to be inserted
void Insert(T value){
	this->Insert(value, this->last);
}


/// @brief remove element from 'index' in the ArrayList.
/// @return value of element removed
T Remove(int index) {
	// cannot remove from empty list
	assert(last>0);
	// index is non-negative
	assert(index>=0);

	T bad = array[index];
	for(int i=index;i<last;i++){
		array[i]=array[i+1];
	}
	last--;
	handleHalving();
	return bad;
}

/// @brief remove element from end of this ArrayList.
/// @return removed value
T Remove(){
	return this->Remove(this->last-1);
}

/// @brief get element at position 'index' in the ArrayList.
T Get(int index)const{
	// cannot get element from empty list
	assert(this->last!=0);	
	// Index must be in range [0, 'last')
	assert(index>=0 && index<this->last);
	
	return array[index];
}

T operator()(int index)const{
	return (*this).Get(index);
}

/// @brief get number of valid elements in the current ArrayList.
/// @return int length.
int Length() {
	return last;
}

/// @brief get max possible number of elements in the current ArrayList.
/// @return int limit.
int Limit() {
	return limit;
}

/// @brief check if ArrayList is empty.
/// @return true if ArrayList is empty.
bool IsEmpty() {
	return !last;
}

/// @brief clears all entries from the ArrayList.
void Clear(){
	free(array);
	this->limit=this->defaultSize;
	this->last=0;
	this->array = allocateArray(this->limit);
}
/// @brief add all elements from (Iterator) first to (Iterator) last to ArrayList.
/// @param first first element to add
/// @param last element terminating iterator.
template<typename Iter>
void AddAll(Iter first, Iter last) {
	assert(typeid(*first) != typeid(T()));
	while(first!= last) {
		this->Insert(*first);
		first++;
	}
}

/// @brief Add all elements from param array to this
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<size_t len>
void AddAll(std::array<T, len> ar){
	assert(typeid(T()) == typeid(ar[0]));
	this->AddAll(ar.begin(), ar.end());
}

/// @brief Construct and initialize a ArrayList<C> with all elements of param array
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<size_t len>
void Initialize(std::array<T, len> ar){
	this->Clear();
	this->AddAll(ar.begin(), ar.end());
}

};