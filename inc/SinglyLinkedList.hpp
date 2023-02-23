#pragma once
#include<iterator>
using namespace std;

/// @brief Singly linked list class with 1 leading bookend.
/// @tparam T type of data at each node.
template<class T>
class SinglyLinkedList{

private:
/// @brief Node class for singly linked list.
/// @tparam T data type.
typedef struct Node {
	T data;
	Node* next;
}Node;
int size;

public:
Node *head;
Node *last;

/// @brief constructor.
SinglyLinkedList<T>() {
	head = new Node;
	last = new Node;
	size=0;
}

/// @brief Iterator implementation for singly linked list.
class Iterator {
    /// @brief specifics about iterator type
    using iterator_category = forward_iterator_tag;
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

    /// @brief dereference
    /// @return data at current node
    reference operator*() const { 
		return this->myNode->data; 
	}
    /// @brief dereference
    /// @return data at current node
    pointer operator->() { 
		return this->myNode->data; 
	}



    /// @brief prefix increment
    /// @return data at next node
    Iterator& operator++() { 
		if(this->myNode){
			this->myNode=this->myNode->next; 
		}
		return *this; 
	}  

    /// @brief postfix increment
    /// @param dummy passed to change signature
    /// @return data at original node
    Iterator operator++(int) { 
		Iterator tmp = *this; 
		++*this; 
		return tmp; 
	}
    /// @brief equality check
    /// @param inc incoming value to compare with
    /// @return true if equal
    bool operator== (const Iterator& inc) { 
		return (this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next); 
	};

    /// @brief non-equality check
    /// @param inc incoming value to compare with 
    /// @return true if dissimilar
    bool operator!= (const Iterator& inc) { 
		return !(this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next); 
	};  

};

/// @brief required for iterator implementation
/// @return first of class
Iterator begin(){
	return Iterator(head->next);
}

/// @brief required for iterator implementation
/// @return last of class
Iterator end(){ 
	return Iterator(last);
}

/// @brief obtain pointer to node at index n
/// @param n index to get pointer from
/// @return Node* at 'n'
Node* GetNodePtr(T n){
	n=(n<0)?n+size:n;
	if(n>=size){
		cout<<"\nERROR: SinglyLinkedList.GetNodePtr : index out of bounds.";
		return NULL;
	}
	Node *current=head->next;
	while(n-->0){
		current=current->next;
	}
	return current;
}

/// @brief add a node to the end of the list.
/// @param data stored in the new added node.
void Add(T data) {
	Node* insert = new Node;
	insert->data = data;
	// list has 2 bookend nodes
	if(size==0){
		// when ll has no elements
		last = new Node;
		head = new Node;
		head->next = insert;
		insert->next = last;
	}
	else{
		Node* preLast = GetNodePtr(size-1);
		// when ll has more than one element, append to LL
		// maintain bookend at back
		insert->next = last;
		preLast->next=insert;
	}
	size++;
}
/// @brief remove node at index 'n'
/// @param n index to remove node from
/// @return data in removed node
T RemoveNode(int n) {
	Node* before = GetNodePtr(n-1);
	T bad = before->next->data;
	before->next = before->next->next;
	size--;
	return bad;
}

/// @brief number of data elements in linked list
/// @return int length of linked list
int Size(){
	return this->size;
}

/// @brief get data at index 'index'
/// @param index location from which data is obtained
/// @return value of the data
T operator()(int index) {
	return GetNodePtr(index)->data;
}

/// @brief clear out contents of linked list
void Clear(){
	head->next=last;
	last->prev=head;
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
static SinglyLinkedList<C> Initialize(array<C, len> ar){
	SinglyLinkedList<C> ll;
	for(C val:ar){
		ll.Add(val);
	}
	return ll;
}

};