#pragma once
#include <cstdlib>
#include "IGraph.hpp"
#include "ITree.hpp"
#include "BinaryTreeNode.hpp"
#include "BinaryTree2.hpp"

using namespace std;

/// @brief implementation of a BinarySearchTree object with BinaryTreeNode class
/// @tparam T type of data at each node of tree.
/// left <= root < right
template <class T>
class BinarySearchTree2 : public BinaryTree2<T>{

// private:
// 	BinaryTreeNode<T> *root;

public:

	/// @brief constructor.
	BinarySearchTree2() {
		this->root = this->allocateNode();
	}

	/// @brief value constructor.
	BinarySearchTree2(T val){
		this->root = this->allocateNode(val);
	}

	// helper to helper findNode(T value)
	// returns node with value='value'.
	// returns NULL if 'value' isn't found in tree starting at 'start'.
	BinaryTreeNode<T>* findInChildren(BinaryTreeNode<T>* start, T value){
		if(start==NULL){
			return NULL;
		}
		else if(start->value == value){
			return start;
		}
		else if(start->value<value){
			return findInChildren(start->right, value);
		}
		else return findInChildren(start->left, value);
	}

	/// @brief insert a node at the correct position in the binary search tree.
	/// @param val value of the node to insert
	void Insert(T val){
		// create new node to hold @param val
		BinaryTreeNode<T>* newNode = this->allocateNode();
		newNode->value=val;
		BinaryTreeNode<T>* trav = this->root;
		BinaryTreeNode<T>* parent;
		while(trav!=NULL){
			parent=trav;
			if(trav->value<val){
				trav = trav->right;
			}
			else{
				trav = trav->left;
			}
		}
		if(parent->value<val){
			parent->right=newNode;
		}
		else{
			parent->left=newNode;
		}
		newNode->parent=parent;
		return;
	}
	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void Delete(T val){
		BinaryTreeNode<T>* toDelete = findInChildren(this->root, val);
		if(toDelete==NULL)return;
		
		return;
	}

	// T rootValue(){
	// 	return 6060;
	// }
};