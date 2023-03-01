#pragma once

#include <iterator>
#include "../inc/DoublyLinkedList.hpp"

using namespace std;

/// @brief implementation of Stack on DoublyLinkedList.
/// @tparam T type of data in Stack.
template<class T>
class Stack{

private:
/// @brief DoublyLinkedList secret
DoublyLinkedList<T> list;

public:


/// @brief iterator begin() function
/// @return first element of doubly linked list.
decltype(auto) begin(){
	return Iterator(list.head->next);
}

/// @brief iterator end() function
/// @return last element of doubly linked list.
decltype(auto) end(){ 
	return Iterator(list.last);
}


/// @brief add element to the top of the stack
/// @param value 
void Push(T value) {
	list.Add(value, 0);
}

/// @brief remove element from the top of the stack
/// @return value of element removed
T Pop() {
	if(list.Size()>0){
		return list.Remove(0);
	}
	else{
		cout<<"ERROR: Stack.Pop: Cannot remove from empty stack.\n";
		return -1;
	}
}

/// @brief read element at the top of the stack (without removal)
/// @return value of the element at the top of the stack
T Peek() {
	if(list.Size()>0){
		return list(0);
	}
	else{
		cout<<"ERROR: Stack.Peek: Cannot peek into empty stack.\n";
		return -1;
	}
}

/// @brief clears all entries from the stack.
void Clear(){
	list.Clear();
}

/// @brief get number of elements in the stack.
/// @return int size.
int Size() {
	return list.Size();
}

/// @brief check if stack is empty.
/// @return true if stack is empty.
bool IsEmpty() {
	return !list.Size();
}

/// @brief add all elements from (Iterator) first to (Iterator) last to this stack.
/// @param first first element to add
/// @param last element terminating iterator.
template<typename Iter>
void AddAll(Iter first, Iter last) {
	while(first!= last) {
		this->Push(*first);
		first++;
	}
}


/// @brief Add all elements from param array to this
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<size_t len>
void AddAll(array<T, len> ar){
	// TODO check this.type = T
	this->AddAll(ar.begin(), ar.end());
}

/// @brief Construct and initialize a Stack<C> with all elements of param array
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<class C, size_t len>
static Stack<C> Initialize(array<C, len> ar){
	Stack<C> q;
	q.AddAll(ar.begin(), ar.end());
	return q;
}


};