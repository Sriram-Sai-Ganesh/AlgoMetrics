#pragma once
using namespace std;



/// @brief Singly linked list class. Keeps track of its own size.
/// @tparam T data type of data at each node.
template<class T>
struct SinglyLinkedList{

/// @brief Node class for singly linked list.
/// @tparam T data type.
struct Node {
	T data;
	Node* next;
};

private:
int size;
public:
Node *head;
Node *last;
/// @brief constructor.
SinglyLinkedList<T>() {
	head = NULL;
	last = NULL;
	size=0;
}

/// @brief add a node to the end of the list.
/// @param data stored in the new added node.
void Add(T data) {
	Node* insert = new Node;
	insert->data = data;
	// assign pointers based on initial list length
	switch(size){
		case 0:
			// when ll has no elements
			head = insert;
			head->next = NULL;
			last = head;
			break;
		case 1:
			// when ll has one element
			last = insert;
			last->next = NULL;
			head->next = last;
			break;
		default:
			// when ll has more than one element, append
			insert->next = NULL;
			last->next = insert;
			last = insert;
	}
	size++;
}

/// @brief removes node with first occurrence of param 'bad'
/// @param bad value to be removed from the list.
void RemoveValue(T bad) {
	if(size==0)return;
	if(head->data==bad){	// remove head
		this->head=head->next;
		this->size--;
	}
	Node *current = head;
	while(current->next!=NULL){
		if(current->next->data==bad){
			if(current->next == this->last){
				this->last=current;
			}
			current->next=current->next->next;
			this->size--;
			return;
		}
		current=current->next;
	}
}

// remove node at index 'n' from head
void RemoveNode(int n) {

	
	if(size<=n)return;
	if(n==0){	// remove head
		head=head->next;
	}
	else{
		Node *current=head;
	while(--n>0){
		current=current->next;
		}
		if(current->next==last)
		{
			last=current;
		}
		current->next=current->next->next;
	}
	size--;
}
int length(){
	return this->size;
}
// overload () operator
T operator()(int index) {
	return GetNode(index);
}

Node *GetHeadPtr(){
	return head;
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