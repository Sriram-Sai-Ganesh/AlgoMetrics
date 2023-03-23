#pragma once

#include <iterator>
#include "../class/DoublyLinkedList.hpp"

using namespace std;

/// @brief implementation of Queue on DoublyLinkedList.
/// @tparam T type of data in Queue.
template<class T>
class Queue{

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

/// @brief add element to the front of the queue
/// @param value value of the element to be added
void Enqueue(T value) {
	list.Add(value, 0);
}

/// @brief remove element at the end of the queue.
/// @return value of element removed
T Dequeue() {
	if(list.Size()>0){
		return list.Remove(list.Size()-1);
	}
	else{
		cout<<"ERROR: Queue.Dequeue: Cannot peek into empty queue.\n";
		return -1;
	}
}

/// @brief read element at the end of the queue (without removal)
/// @return value of last element
T Peek() {
	if(list.Size()>0){
		return list(list.Size()-1);
	}
	else{
		cout<<"ERROR: Queue.Peek: Cannot peek into empty queue.\n";
		return -1;
	}
}

/// @brief clears all entries from linked list.
void Clear(){
	list.Clear();
}

/// @brief get number of elements in the queue.
/// @return int size.
int Size() {
	return list.Size();
}

/// @brief check if queue is empty.
/// @return true if queue is empty.
bool IsEmpty() {
	return !list.Size();
}

/// @brief add all elements from (Iterator) first to (Iterator) last to this queue.
/// @param first first element to add
/// @param last element terminating iterator.
template<typename Iter>
void AddAll(Iter first, Iter last) {
	while(first!= last) {
		this->Enqueue(*first);
		first++;
	}
}

/// @brief Add all elements from param array to this
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<size_t len>
void AddAll(array<T, len> ar){
	this->AddAll(ar.begin(), ar.end());
}

/// @brief Construct and initialize a Queue<C> with all elements of param array
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<class C, size_t len>
static Queue<C> Initialize(array<C, len> ar){
	Queue<C> q;
	q.AddAll(ar.begin(), ar.end());
	return q;
}


};