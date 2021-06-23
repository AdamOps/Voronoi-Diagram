#include "BinaryTree.h"

binaryTreeNode* getNewNode(float value_) {
	binaryTreeNode* newNode = new binaryTreeNode();
	newNode->value = value_;
	newNode->leftChildNode = nullptr;
	newNode->rightChildNode = nullptr;
	return newNode;
}

binaryTreeNode* binaryTree::insertNode(binaryTreeNode* nodePtr, float value_, int depth_) {
	if (nodePtr == nullptr) {
		nodePtr = getNewNode(value_);
		std::cout << "New node at depth ( " << depth_ << " ), value ( " << value_ << " ), address ( " << nodePtr << " )" << std::endl;
	}
	else if (value_ <= root->value) {
		nodePtr->leftChildNode = insertNode(root->leftChildNode, value_, ++depth_);
	}
	else {
		nodePtr->rightChildNode = insertNode(root->rightChildNode, value_, ++depth_);
	}
	return nodePtr;
}

binaryTreeNode* binaryTree::searchNodeByValue(binaryTreeNode* nodePtr, float value_) {
	if (nodePtr == nullptr) {
		return nullptr;
	}
	else if (nodePtr->value == value_) {
		return nodePtr;
	}
	else if(nodePtr->value > value_) {
		return searchNodeByValue(nodePtr->leftChildNode, value_);
	}
	else {
		return searchNodeByValue(nodePtr->rightChildNode, value_);
	}
}

void binaryTree::removeNodeByValue(float value_) {

}

void binaryTree::removeNodeByPtr(binaryTreeNode* nodePtr) {

}