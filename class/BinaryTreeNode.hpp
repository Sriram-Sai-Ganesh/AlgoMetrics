#pragma once
#include <iostream>
#include "INode.hpp"

using namespace std;

template<class T>
class BinaryTreeNode;

template<class T>
class BinaryTreeNode : public INode<T>{

	public:
	BinaryTreeNode<T> *parent;
	BinaryTreeNode<T> *left;
	BinaryTreeNode<T> *right;
	
	BinaryTreeNode(){
		this->value = T();
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
	}
	
	BinaryTreeNode(T val){
		this->value = val;
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
	}

	BinaryTreeNode(T val, BinaryTreeNode* p, BinaryTreeNode* l, BinaryTreeNode* r){
		this->value=val;
		this->parent=p;
		this->right=r;
		this->left=l;

	}

};