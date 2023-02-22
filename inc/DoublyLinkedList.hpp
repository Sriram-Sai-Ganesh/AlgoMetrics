#include <iterator>
#pragma once
using namespace std;

// DoublyLinkedList
// implementation with 2 bookend nodes
template<class T>
class DoublyLinkedList{
private:
int size;

// Node
typedef struct Node {
	T data;
	Node* prev;
	Node* next;
}Node;

public:
Node *head;
Node *last;

// constructor
DoublyLinkedList<T>() {
	head = new Node;
	last = new Node;
	size=0;
}

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

    // Prefix increment
    Iterator& operator++() { 
		if(this->myNode){
			this->myNode=this->myNode->next; 
		}
		return *this; 
	}  

    // Postfix increment
    Iterator operator++(int) { 
		Iterator tmp = *this; 
		++*this; 
		return tmp; 
	}

    bool operator== (const Iterator& inc) { 
		return (this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next && this->myNode->prev==inc.myNode->prev); 
	};

    bool operator!= (const Iterator& inc) { 
		return !(this->myNode->data==inc.myNode->data && this->myNode->next==inc.myNode->next && this->myNode->prev==inc.myNode->prev); 
	};  

};

Iterator begin(){
	return Iterator(head->next);
}
Iterator end(){ 
	return Iterator(last);
}


// get pointer to node at index n
Node* GetNodePtr(T n){
	n=(n<0)?n+size:n;
	if(n>=size){
		cout<<"\nERROR: DoublyLinkedList.GetNodePtr : index out of bounds.";
		return NULL;
	}
	Node *current;
	if(n<size/2){
		current=head->next;
		while(n-->0){
			current=current->next;
		}
	}else{
		n++;
		current = last->prev;
		while(n++<size){
			current=current->prev;
		}
	}
	return current;
}

// append node to end of linked list
void Add(T data) {
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
		// when ll has more than one element, append
		insert->next = last;
		insert->prev = last->prev;
		last->prev->next = insert;
		last->prev=insert;
	}
	size++;
}


// remove node at index 'n' from head
T RemoveNode(T n) {
	Node* bad = GetNodePtr(n);
	bad->next->prev = bad->prev;
	bad->prev->next = bad->next;
	size--;
	return bad->data;
}

// overload () operator
T operator()(int index) {
	return GetNodePtr(index)->data;
}
void Clear(){
	head->next=last;
	last->prev=head;
}
int Size() {
	return size;
}
};