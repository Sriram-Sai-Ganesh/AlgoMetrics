#pragma once
using namespace std;

// Node
template<class T>
struct Node {
	T data;
	Node<T>* next;
};

// LinkedList
template<class T>
struct LinkedList{

public:
Node<T> *head;
Node<T> *last;
int length;
// constructor
LinkedList<T>() {
	head = NULL;
	last = NULL;
	length=0;
}

// append node
void Add(T data) {
	if(!head) {
		// when there is no element in the list
		head = new Node<T>;
		head->data = data;
		head->next = NULL;
		last = head;
	} else {
		// when the list is not empty
		if(last == head) {
			// when the list has one element
			last = new Node<T>;
			last->data = data;
			last->next = NULL;
			head->next = last;
		} else {
			// when the list has more than one element
			Node<T>* insdata = new Node<T>;
			insdata->data = data;
			insdata->next = NULL;
			last->next = insdata;
			last = insdata;
		}
	}
	length++;
}

// remove first occurence of 'bad'
void RemoveValue(T bad) {
	if(length==0)return;
	if(head->data==bad){	// remove head
		this->head=head->next;
		this->length--;
	}
	Node<T> *current = head;
	while(current->next!=NULL){
		if(current->next->data==bad){
			if(current->next == this->last){
				this->last=current;
			}
			current->next=current->next->next;
			this->length--;
			return;
		}
		current=current->next;
	}
}

// remove node at index 'n' from head
void RemoveNode(T n) {
	if(length<=n)return;
	if(n==0){	// remove head
		head=head->next;
	}
	else{
		Node<T> *current=head;
	while(--n>0){
		current=current->next;
		}
		if(current->next==last)
		{
			last=current;
		}
		current->next=current->next->next;
	}
	length--;
}

// overload () operator
T operator()(int index) {
	return GetNode(index);
}

private:
// return data at the ith element of ll
T GetNode(int n) const{
	n=(n<0)?length-n:n;	// support negative index params
	Node<T> *current = this->head;
	if(n>=this->length || current==NULL)return NULL; // todo
	// Get the ith element
	for(int i = 0; i < n;current = current->next, i++);
	return current->data;
}


};