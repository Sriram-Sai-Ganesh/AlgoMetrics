#pragma once
#include <cstdlib>
#include "IGraph.hpp"
#include "ITree.hpp"
#include "BinaryTreeNode.hpp"

using namespace std;

/// @brief implementation of a BinaryTree object with BinaryTreeNode class
/// @tparam T type of data at each node of tree.
template <class T>
class BinaryTree2 : public ITree<T>{

private:
	BinaryTreeNode<T> *root;

public:

	/// @brief constructor.
	BinaryTree2() {
		this->root = allocateNode();
	}

	/// @brief value constructor.
	BinaryTree2(T val){
		this->root = allocateNode(val);
	}

	~BinaryTree2(){
		freeAllChildren(this->root);
		free(this->root);
	}

	BinaryTreeNode<T>* allocateNode(T val = T()){
		BinaryTreeNode<T>* newNode = (BinaryTreeNode<T>*)(malloc(sizeof(BinaryTreeNode<T>)));
		newNode->value = val;
		newNode->left = NULL;	
		newNode->right = NULL;	
		newNode->parent = NULL;	
		return newNode;
	}

	void freeAllChildren(BinaryTreeNode<T>* start){
		if(start==NULL) return;
		freeAllChildren(start->left);
		freeAllChildren(start->right);
	}

	// helper doing recursive calls to find height
	size_t getNodeHeight(BinaryTreeNode<T> *start){
		size_t leftHeight = (start->left==NULL)?0:getNodeHeight(start->left);
		size_t rightHeight = (start->right==NULL)?0:getNodeHeight(start->right);
		return 1+max(leftHeight,rightHeight);
	}

	size_t Height(){
		return getNodeHeight(this->root);
	}

	size_t getNodeSize(BinaryTreeNode<T> *start){
		size_t leftSize = (start->left==NULL)?0:getNodeSize(start->left);
		size_t rightSize = (start->right==NULL)?0:getNodeSize(start->right);
		return 1+leftSize+rightSize;
	
	}

	size_t Size(){
		return getNodeSize(this->root);
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	void InsertLeftmost(T val){
		
		// create new node to hold @param val
		BinaryTreeNode<T>* newNode = allocateNode();
		newNode->value=val;
		insertNodeLeftmost(this->root, newNode);
		return;		
	}


	void insertNodeLeftmost(BinaryTreeNode<T>* start, BinaryTreeNode<T>* newNode){
		// find parent
		BinaryTreeNode<T>* nodeParent = findMyLeftmostNode(start);
		// add to tree
		nodeParent->left = newNode;
		newNode->parent = nodeParent;
	}


	// general helper
	BinaryTreeNode<T>* findMyLeftmostNode(BinaryTreeNode<T>* start){
		// traverse down leftmost branch
		BinaryTreeNode<T>* temp = start;
		return findLeftmostChild(temp);
	}

	// helper to helper findMyLeftmostNode()
	// assumes 'start' is NOT NULL
	BinaryTreeNode<T>* findLeftmostChild(BinaryTreeNode<T>* start){
		// traverse down leftmost branch
		while(start->left!=NULL){
			start = start->left;
		}
		return start;
	}

	// general helper
	BinaryTreeNode<T>* findNode(T value){
		return findInChildren(this->root, value);
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
		else {
			BinaryTreeNode<T>* left = findInChildren(start->left, value);
			BinaryTreeNode<T>* right = findInChildren(start->right, value);
			return (left==NULL)?right:left;
		}
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void Insert(T val){
		InsertLeftmost(val);
		return;
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void Delete(T val){
		BinaryTreeNode<T>* toDelete = findInChildren(this->root, val);
		if(toDelete==NULL)return;
		
		return;
	}

	virtual bool Contains(T val){
		return findNode(val)!=NULL;
	}

	std::string getTreeTraversal(BinaryTreeNode<T>* start){
		string result="";
		if(start==NULL)return result;
		if(start->parent!=NULL){
			result=to_string(start->parent->value)+", "+to_string(start->value)+"\n";
		}
		result+=getTreeTraversal(start->left);
		result+=getTreeTraversal(start->right);
		return result;
	}
	std::string getTraversalString(){
		return getTreeTraversal(this->root);		
	}

	// debug
	virtual T rootValue(){
		cout<<"Getting root val\n";
		return this->root->value;
	}

	// returns number of DIRECT children of root.
	size_t NumberOfChildren(){
		size_t ans=((this->root->left==NULL)?0:1);
		return ans + ((this->root->right==NULL)?0:1);
	}
};