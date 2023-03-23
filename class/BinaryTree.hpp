#pragma once
using namespace std;

/// @brief implementation of a BinaryTree object
/// @tparam T type of data at each node.
template<class T>
class BinaryTree{

private:

typedef struct binaryTreeNode{
	T data;
	binaryTreeNode* left;
	binaryTreeNode* right;
}binaryTreeNode;

binaryTreeNode myRoot;


public:

/// @brief constructor.
BinaryTree<T>() {
	this->myRoot.data=0l;
}

T root(){
	return this->myRoot.data;
}








};