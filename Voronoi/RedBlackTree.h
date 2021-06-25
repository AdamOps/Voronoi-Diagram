#pragma once
#include "VoronoiEvents.h"

// Need to keep track of whether the nodes are black or red
// 0 means it's a black node
// 1 means it's a red node
enum class nodeColor { black, red };

// Useful to keep track of whether a node is the left or the right child of its parent.
// 0 means left child
// 1 means right child
enum class nodeDirection { left, right };


struct RBNode {
	// Store pointers to the parent and the two potential children. The children are set to nullptr by default.
	RBNode* parent;
	RBNode* leftChild;
	RBNode* rightChild;

	// Voronoi circle events require at least three sites. 
	//		The circle event will be based on whether there is a common circle between the current node and the two neighbouring nodes on the beachfront.
	// Circle events can also be based on the left two neighbours, or the right two neighbours.
	//		This can be checked by running checkCircleEvent() for the this->leftNeighbour node and for the this->rightNeighbour node.
	RBNode* leftNeighbour;
	RBNode* rightNeighbour;

	// Determine whether the current node is the left child or the right child of the parent
	nodeDirection direction = (this->parent->leftChild == this) ? nodeDirection::left : nodeDirection::right;

	// Store whether it's a black or a red node
	nodeColor color;

	// The position of the site. Should probably include some other useful variables in here (e.g. range of x coordinates covered by the arc)
	float siteX;
	float siteY;
	
	// The node may have a circle event attached to it
	voronoiEvent* circleEvent;

	// Internal nodes are stored as tuples. Leaves are singular sites. If it is indeed a tuple, then we'll be using the breakpoint between the tuple for comparisons.
	bool tuple;
	float breakpointX;

};

struct RBTree {
	RBNode* root;

	// Tree should be empty by default
	RBTree() : root(nullptr) {

	}
	void RBTreeInsert(float siteX_, float siteY_);
	void fixInsertion(RBNode* node);

	RBNode* getParent(RBNode* node);
	RBNode* getGrandParent(RBNode* node);
	RBNode* getSibling(RBNode* node);
	RBNode* getUncle(RBNode* node);
	RBNode* getNearestNephew(RBNode* node);
	RBNode* getFurtherNephew(RBNode* node);
	RBNode* rotateLeft(RBNode* node);
	RBNode* rotateRight(RBNode* node);
};