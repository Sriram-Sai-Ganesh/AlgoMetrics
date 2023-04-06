#pragma once
#include "IGraph.hpp"
#include "ITree.hpp"

using namespace std;

// forward declaration
template <class T>
class BinaryTree;

// TODO create binary tree node class and refactor this one

/// @brief implementation of a BinaryTree object
/// @tparam T type of data at each node of tree.
template <class T>
class BinaryTree : public ITree<T>{

private:
	BinaryTree<T> *left;
	BinaryTree<T> *right;
	BinaryTree<T> *parent;

public:
	template<class U> friend class BinarySearchTree;
	T Value;

	/// @brief constructor.
	BinaryTree() {
		// printf("using default constructor\n");
		this->Value = T();
		this->left = this->right = NULL;
		this->parent = NULL;
	}
	/// @brief constructor.
	BinaryTree(T val){
		// printf("using Value constructor\n");
		BinaryTree();
		this->Value = val;
	}
	
	BinaryTree<T>* Left(){
		return this->left;
	}

	BinaryTree<T>* Right(){
		return this->right;
	}

	BinaryTree<T>* Parent(){
		return this->parent;
	}

	size_t Height(){
		size_t leftHeight = (this->left!=NULL) ? this->left->Height() : 0;
		size_t rightHeight = (this->right!=NULL) ? this->right->Height() : 0;
		return 1+max(leftHeight, rightHeight);
	}

	size_t Size(){

		size_t leftSize = (this->left==NULL)?0:this->left->Size();
		size_t rightSize = (this->right==NULL)?0:this->right->Size();
		return 1+leftSize+rightSize;
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	void InsertLeftmost(T val){
		// traverse down leftmost branch
		BinaryTree<T>* temp=this;
		while(temp->left!=NULL){
			temp = temp->left;
		}
		// create new node to hold @param val
		BinaryTree<T>* newNode = new BinaryTree<T>();
		newNode->Value=val;
		// add to tree
		temp->left = newNode;
		newNode->parent = temp;
		return;		
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void Insert(T val){
		InsertLeftmost(val);
		return;
	}

	virtual bool Contains(T val){
		bool result=(this->Value==val);
		if(!result && this->left!=NULL){
			result=this->left->Contains(val);
		}
		if(!result && this->right!=NULL){
			result=this->right->Contains(val);
		}
		return result;
	}

	size_t NumberOfChildren(){
		size_t ans=((this->left==NULL)?0:1);
		return ans + ((this->right==NULL)?0:1);
	}



};