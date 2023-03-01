#pragma once
#include <iterator>
using namespace std;

/// @brief implementation of DoublyLinkedList.
/// 2 bookend nodes.
/// @tparam T type of data in linked list.
template<class T>
class DoublyLinkedList{

private:
/// @brief Node of doubly linked list.
typedef struct Node {
	T data;
	Node* prev;
	Node* next;
}Node;

int size;

public:
Node *head;
Node *last;

/// @brief constructor.
DoublyLinkedList<T>() {
	head = new Node;
	last = new Node;
	size=0;
}

/// @brief iterator implementation.
class Iterator {
    using iterator_category = bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;  // or also value_type*
    using reference         = T&;  // or also value_type&
	
	private:
	Node *myNode;
	
	public:
	Iterator(Node *n){
		myNode=n;
	}

    reference operator*() const { 
		return this->myNode->data; 
	}
    pointer operator->() { 
		return this->myNode->data; 
	}

    /// @brief prefix increment operator.
    /// @return value after increment.
    Iterator& operator++() { 
		if(this->myNode){
			this->myNode=this->myNode->next; 
		}
		return *this; 
	}  

    /// @brief postfix increment.
    /// @param  \dummy parameter to change signature.
    /// @return value prior to increment.
    Iterator operator++(int) { 
		Iterator tmp = *this; 
		++*this; 
		return tmp; 
	}

    /// @brief prefix decrement.
    /// @return value after decrement.
    Iterator& operator--() { 
		if(this->myNode){
			this->myNode=this->myNode->prev; 
		}
		return *this; 
	}  

    /// @brief postfix decrement.
    /// @param  \dummy parameter to change signature.
    /// @return value prior to decrement.
    Iterator operator--(int) { 
		Iterator tmp = *this; 
		--*this; 
		return tmp; 
	}

    /// @brief operator overload for equality comparison.
    /// @param inc incoming value to compare against.
    /// @return true if this==inc and vice versa.
    bool operator== (const Iterator& inc) { 
		return (this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next && this->myNode->prev==inc.myNode->prev); 
	};

    /// @brief operator overload for inequality comparison.
    /// @param inc incoming value to compare against.
    /// @return true if this!=inc and vice versa.
    bool operator!= (const Iterator& inc) { 
		return !(this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next && this->myNode->prev==inc.myNode->prev); 
	};

};

/// @brief iterator begin() function
/// @return first element of doubly linked list.
Iterator begin(){
	return Iterator(head->next);
}

/// @brief iterator end() function
/// @return last element of doubly linked list.
Iterator end(){ 
	return Iterator(last);
}

/// @brief get pointer to node at index 'n' from beginning of doubly linked list.
/// @param n index of linked list element
/// @return reference to 'n'th node of linked list.
Node* GetNodePtr(int n){
	// n=(n<0)?n+size:n;
	if(n>=size){
		cout<<"\nERROR: DoublyLinkedList.GetNodePtr : index out of bounds.";
		return NULL;
	}
	Node *current;
	// traverse from end of linked list if more efficient
	if(n<=size/2.0){
		current=head;
		while(n-->=0){
			current=current->next;
		}
	}
	else{
		n++;
		current = last->prev;
		while(n++<size){
			current=current->prev;
		}
	}
	return current;
}

/// @brief insert node 'data' at index 'location' in doubly linked list.
/// @param data node to be inserted
/// @param location index to be inserted at
/// @return true if insertion was successful.
bool Add(T data, int location) {
	if(location>size){
		cout<<"ERROR: DoublyLinkedList.Add : insertion location "<<location<<" out of bounds for size "<<size<<"\n";
		return false;
	}
	Node* insert = new Node;
	insert->data = data;
	// list has 2 bookend nodes
	if(size==0){
		// when ll has no elements
		last = new Node;
		head = new Node;
		head->next = insert;
		last->prev = insert;
		insert->next = last;
		insert->prev = head;
	}
	else{
		// when ll has more than one element, insert at 'location'
		Node* before = GetNodePtr(location-1);
		insert->prev=before;
		insert->next=before->next;
		before->next->prev=insert;
		before->next=insert;
	}
	size++;
	return true;
}

/// @brief overloaded add function. (overload necessary since parameter is class variable)
/// @param data node to be inserted
void Add(T data){
	Add(data,size);
}

/// @brief remove node at index 'n' from doubly linked list.
/// @param n index of node to be removed
/// @return data of removed node.
T Remove(T n) {
	Node* bad = GetNodePtr(n);
	bad->next->prev = bad->prev;
	bad->prev->next = bad->next;
	size--;
	return bad->data;
}

/// @brief overloaded () operator. Returns pointer to 'index'th node of doubly linked list.
/// @param index location of node to be returned
/// @return node at location 'index' in linked list.
T operator()(int index) {
	return GetNodePtr(index)->data;
}

/// @brief clears all entries from linked list.
void Clear(){
	head->next=last;
	last->prev=head;
}

/// @brief get number of nodes in doubly linked list.
/// @return int size.
int Size() {
	return size;
}

/// @brief Add all elements from param array to this
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<size_t len>
void AddAll(array<T, len> ar){
	// TODO check this.type = T
	this->Clear();
	for(T val:ar){
		this->Add(val);
	}
}

/// @brief Initialize this with all elements of param array
/// @tparam len length of array parameter
/// @param ar array containing values to initialize 
template<class C, size_t len>
static DoublyLinkedList<C> Initialize(array<C, len> ar){
	DoublyLinkedList<C> ll;
	ll.AddAll(ar);
	return ll;
}
};