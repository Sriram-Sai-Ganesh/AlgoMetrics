#pragma once
#include "IGraph.hpp"
#include "ITree.hpp"

using namespace std;

// template<class T> class BinarySearchTree;

/// @brief implementation of a BinarySearchTree object
/// @tparam T type of data at each node of tree.
template <class T>
class BinarySearchTree : public BinaryTree<T>{

public:
	/// @brief insert a node at its correct position in the binary search tree.
	/// @param val value of the node to insert
	void Insert(T val){
		
		// create new node to hold @param val
		BinaryTree<T>* newNode = new BinaryTree<T>();
		newNode->Value=val;

		// add to tree
		// start the traverse pointer at tree's root
		BinaryTree<T>* trav=this;

		while(true){	// break once inserted
			if(val<trav->Value){
				if(trav->left==NULL){
					trav->left=newNode;
					break;
				}
				else {
					trav=trav->left;
					continue;
				}
			}
			else{
				if(trav->right==NULL){
					trav->right=newNode;
					break;
				}
				else {
					trav=trav->right;
					continue;
				}
			}
		}
		newNode->parent=trav;
		return;
	}

	// virtual bool Contains(T val){
	// 	bool result=(this->Value==val);
	// 	if(!result && this->left!=NULL){
	// 		result=this->left->Contains(val);
	// 	}
	// 	if(!result && this->right!=NULL){
	// 		result=this->right->Contains(val);
	// 	}
	// 	return result;
	// }

	// size_t NumberOfChildren(){
	// 	size_t ans=((this->left==NULL)?0:1);
	// 	return ans + ((this->right==NULL)?0:1);
	// }



};