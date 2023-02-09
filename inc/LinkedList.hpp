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
struct LinkedList
{
	public:
	Node<T> *head;
	Node<T> *last;

	// constructor
	LinkedList<T>() {
		head = NULL;
		last = NULL;
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
	}

	void RemoveValue(T data) {
		
	}

	// return data at ith element of ll
	T Get(int n) {

		Node<T> *current = this->head;
		if(current==NULL)return NULL;
		// Get the ith element
		for(int i = 0; i < n;current = current->next, i++);
		return current->data;
		
	}

	// overload [] operator
	T operator[](int index) {
		return get(index);
	}

	// print contents
	void Print()
	{
		Node<T> *current = this->head;
		cout<<"[  ";
		while(current!=NULL){
			cout<<current->data<<"  ";
			current=current->next;
		}
		cout<<"]";
	}

};