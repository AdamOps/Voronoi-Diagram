#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

struct binaryTreeNode {
	float value;
	binaryTreeNode* leftChildNode;
	binaryTreeNode* rightChildNode;
	//binaryTreeNode* parentNode;
	int treeLevel;
	sf::CircleShape nodeShape;

	binaryTreeNode()
	: value(0.f), leftChildNode(nullptr), rightChildNode(nullptr), /*parentNode(nullptr),*/ treeLevel(0) {
		this->nodeShape.setRadius(10.f);
		this->nodeShape.setFillColor(sf::Color::White);
		this->nodeShape.setOrigin(nodeShape.getOrigin().x + nodeShape.getRadius(), nodeShape.getOrigin().x + nodeShape.getRadius());
	}
};

class binaryTree
{
public:
	binaryTreeNode* insertNode(binaryTreeNode* nodePtr, float value, int depth_);
	binaryTreeNode* searchNodeByValue(binaryTreeNode* nodePtr, float value_);

	void removeNodeByValue(float value);
	void removeNodeByPtr(binaryTreeNode* nodePtr);

private:
	binaryTreeNode* root;
};