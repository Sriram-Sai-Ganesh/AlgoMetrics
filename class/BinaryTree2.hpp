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

protected:
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
		// freeAllChildren(this->root);
		// free(this->root);
	}

	virtual void freeAllChildren(BinaryTreeNode<T>* start){
		if(start==NULL) return;
		freeAllChildren(start->left);
		freeAllChildren(start->right);
	}

	virtual void Clear(){
		(*this).~BinaryTree2<T>();
		BinaryTree2<T>();
	}


	BinaryTreeNode<T>* allocateNode(T val = T()){
		BinaryTreeNode<T>* newNode = (BinaryTreeNode<T>*)(malloc(sizeof(BinaryTreeNode<T>)));
		newNode->value = val;
		newNode->left = NULL;	
		newNode->right = NULL;	
		newNode->parent = NULL;	
		return newNode;
	}


	// helper doing recursive calls to find height
	virtual size_t getNodeHeight(BinaryTreeNode<T> *start){
		size_t leftHeight = (start->left==NULL)?0:getNodeHeight(start->left);
		size_t rightHeight = (start->right==NULL)?0:getNodeHeight(start->right);
		return 1+max(leftHeight,rightHeight);
	}

	virtual size_t Height(){
		return getNodeHeight(this->root);
	}

	virtual size_t getNodeSize(BinaryTreeNode<T> *start){
		size_t leftSize = (start->left==NULL)?0:getNodeSize(start->left);
		size_t rightSize = (start->right==NULL)?0:getNodeSize(start->right);
		return 1+leftSize+rightSize;
	
	}

	virtual size_t Size(){
		return getNodeSize(this->root);
	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void InsertLeftmost(T val){
		
		// create new node to hold @param val
		BinaryTreeNode<T>* newNode = allocateNode();
		newNode->value=val;
		insertNodeLeftmost(this->root, newNode);
		return;		
	}


	virtual void insertNodeLeftmost(BinaryTreeNode<T>* start, BinaryTreeNode<T>* newNode){
		// find parent
		BinaryTreeNode<T>* nodeParent = findMyLeftmostNode(start);
		// add to tree
		nodeParent->left = newNode;
		newNode->parent = nodeParent;
	}


	// general helper
	virtual BinaryTreeNode<T>* findMyLeftmostNode(BinaryTreeNode<T>* start){
		// traverse down leftmost branch
		BinaryTreeNode<T>* temp = start;
		return findLeftmostChild(temp);
	}

	// helper to helper findMyLeftmostNode()
	// assumes 'start' is NOT NULL
	virtual BinaryTreeNode<T>* findLeftmostChild(BinaryTreeNode<T>* start){
		// traverse down leftmost branch
		while(start->left!=NULL){
			start = start->left;
		}
		return start;
	}

	// general helper
	virtual BinaryTreeNode<T>* findNode(T value){
		return findInChildren(this->root, value);
	}

	// helper to helper findNode(T value)
	// returns node with value='value'.
	// returns NULL if 'value' isn't found in tree starting at 'start'.
	virtual BinaryTreeNode<T>* findInChildren(BinaryTreeNode<T>* start, T value){
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

	virtual void RightRotate(BinaryTreeNode<T>* pivot){
		if(pivot==NULL)return;
		if(pivot->left==NULL){
			pivot->left=pivot->right;
			pivot->right=pivot->parent;
			pivot->parent=NULL;
			return;
		}
		cout<<"rotating about node with val "<<pivot->value<<endl;
		BinaryTreeNode<T>* temp = pivot->left;
		pivot->left = temp->right;
		temp->right = pivot;
		temp->parent = pivot->parent;
		pivot->parent = temp;

	}

	/// @brief insert a node at the leftmost position in the tree.
	/// @param val value of the node to insert
	virtual void Delete(T val){
		BinaryTreeNode<T>* toDelete = findInChildren(this->root, val);
		if(toDelete==NULL)return;
		if(toDelete->parent==NULL){
			if(toDelete->right==NULL){
				this->root=toDelete->left;
				this->root->parent=NULL;
			}
			else{
				insertNodeLeftmost(toDelete->right, toDelete->left);
				toDelete->right->parent = NULL;
			}
		}
		else{
			// TODO handle case for non-null parent of bad node
		}
		
		return;
	}

	virtual bool Contains(T val){
		return findNode(val)!=NULL;
	}

	virtual std::string getTreeTraversal(BinaryTreeNode<T>* start){
		string result="";
		if(start==NULL)return result;
		if(start->parent!=NULL){
			result=to_string(start->parent->value)+", "+to_string(start->value)+"\n";
		}
		result+=getTreeTraversal(start->left);
		result+=getTreeTraversal(start->right);
		return result;
	}
	virtual std::string getTraversalString(){
		return getTreeTraversal(this->root);		
	}

	// debug
	virtual T rootValue(){
		// cout<<"Getting root val\n";
		return this->root->value;
	}

	// returns number of DIRECT children of root.
	virtual size_t NumberOfChildren(){
		size_t ans=((this->root->left==NULL)?0:1);
		return ans + ((this->root->right==NULL)?0:1);
	}
};