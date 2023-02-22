#include <iterator> 
#include <cstddef>
#pragma once
using namespace std;


// DoublyLinkedList
template<class T>
struct DoublyLinkedList{
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
	head = NULL;
	last = NULL;
	size=0;
}

struct Iterator 
{
    using iterator_category = forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;  // or also value_type*
    using reference         = T&;  // or also value_type&
	private:
	Node *current;
	public:
	Iterator(Node *n){
		current=n;
	}

    reference operator*() const { return *current; }
    pointer operator->() { return current->data; }

    // Prefix increment
    Iterator& operator++() { current=current->next; return *this; }  

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator== (const Iterator& a, const Iterator& b) { return ((a->data == b->data) && (a->prev == b->prev) && (a->next==b->next)); };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return !((a->data == b->data) && (a->prev == b->prev) && (a->next==b->next)); };  

	// Iterator begin() { return Iterator(head); }
    // Iterator end()   { return Iterator(last); }
};

// append node
void Add(T data) {
	Node* insert = new Node;
	insert->data = data;
	// assign pointers based on initial list length
	switch(size){
		case 0:
			// when ll has no elements
			head = insert;
			head->next = NULL;
			head->prev = NULL;
			last = head;
			break;
		case 1:
			// when ll has one element
			last = insert;
			last->next = NULL;
			last->prev = head;
			head->next = last;
			break;
		default:
			// when ll has more than one element, append
			insert->next = NULL;
			insert->prev = last;
			last->next = insert;
			last = insert;
	}
	size++;
}

// remove first occurence of 'bad'
void RemoveValue(T bad) {
	if(size==0)return;
	if(head->data==bad){	// remove head
		head=head->next;
		head->prev=NULL;
		size--;
	}
	Node *current = head;
	while(current->next!=NULL){
		if(current->next->data==bad){
			if(current->next == last){
				current->next=NULL;
				last=current;
			}
			else{
				current->next=current->next->next;
			}
			size--;
			return;
		}
		current=current->next;
	}
}

// remove node at index 'n' from head
void RemoveNode(T n) {
	if(size<=n)return;
	if(n==0){	// remove head
		head=head->next;
		head->prev=NULL;
	}
	else{
		Node *current=head;
		while(--n>0){
			current=current->next;
		}
		if(current->next==last){
			last=current;
			last->next=NULL;
		}
		else{
			current->next=current->next->next;
		}
	}
	size--;
}

// overload () operator
T operator()(int index) {
	return GetNode(index);
}

Node *GetHeadPtr(){
	return head;
}
int length() {
	return size;
}

private:
// return data at the ith element of ll
T GetNode(int n) const{
	n=(n<0)?size-n:n;	// support negative index params
	Node *current = this->head;
	if(n>=this->size || current==NULL)return NULL; // todo
	// Get the ith element
	for(int i = 0; i < n;current = current->next, i++);
	return current->data;
}
};