// A self-balancing binary search tree used to store beachfront sites, as well as the intersections of the corresponding arcs with neighbouring sites.
//
// Five rules for the red-black tree:
//	1) The nodes must be either red or black
//	2) The root node is always black
//	3) The leaf nodes are null nodes, and each leaf is black.
//	4) A red node cannot have red children. They must always be black.
//	5) The downward path to a leaf from a node must always encounter the same number of black nodes.


#include "RedBlackTree.h"

RBNode* RBTree::getParent(RBNode* node) {
	// Return the parent if the node itself is well defined. node->parent is nullptr by default, but node->parent will only exist if node itself isn't a nullptr.
	if (node == nullptr) {
		return nullptr;
	}
	else {
		return node->parent;
	}
}

RBNode* RBTree::getGrandParent(RBNode* node) {
	// Simply use the getParent function twice to get the parent of the parent.
	return getParent(getParent(node));
}

RBNode* RBTree::getSibling(RBNode* node) {
	// First check whether there is a parent. If not, we are looking at the root node, which has no siblings (but only offspring)
	RBNode* parent = getParent(node);
	if (parent == nullptr) {
		return nullptr;
	}
	// If the current node is the left child, then get the pointer to the right child.
	if (node->direction == nodeDirection::left) {
		return node->parent->rightChild;
	}
	// Otherwise, the current node is the right child, so we want the pointer to the left child instead.
	else {
		return node->parent->leftChild;
	}
}

RBNode* RBTree::getUncle(RBNode* node) {
	// Check whether the current node has a parent. If it does not, then it is the root node, which does not have an uncle.
	RBNode* parent = getParent(node);
	if (parent == nullptr) {
		return nullptr;
	}
	else{
		// Note that since the children are set to nullptr by default, if there happens not to be a sibling, we simply get nullptr back.
		return getSibling(parent);
	}
}


RBNode* RBTree::getNearestNephew(RBNode* node) {
	// The nearest nephew is the child of the sibling with the same direction as the current node.
	//		That is, if the current node is left, the nearest nephew is also a left nephew.
	// First, it's necessary to check whether the parent exists (so that there can be a sibling).
	RBNode* parent = getParent(node);
	if (parent != nullptr) {
		RBNode* sibling = getSibling(node);
		// The sibling needs to actually exist, so that we can get its child.
		if (sibling != nullptr) {
			if (node->direction == nodeDirection::left) {
				return sibling->leftChild;
			}
			else {
				return sibling->rightChild;
			}
		}
	}

	// If either one of the conditions isn't met, we simply get nullptr back.
	return nullptr;

}

RBNode* RBTree::getFurtherNephew(RBNode* node) {
	// Same function as getNearestNephew, but returns the other child of the sibling instead.
	RBNode* parent = getParent(node);
	if (parent != nullptr) {
		RBNode* sibling = getSibling(node);
		if (sibling != nullptr) {
			if (node->direction == nodeDirection::left) {
				return sibling->rightChild;
			}
			else {
				return sibling->leftChild;
			}
		}
	}

	return nullptr;
}

void RBTree::RBTreeInsert(float siteX_, float siteY_) {
	RBNode* newNode = new RBNode;
	newNode->parent = nullptr;
	newNode->siteX = siteX_;
	newNode->siteY = siteY_;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;
	newNode->color = nodeColor::red;

	RBNode* currParent = nullptr;
	RBNode* potentialParent = this->root;

	// If the potential parent is a nullptr from the start, then the tree is empty and the loop breaks.
	// If the potential parent is not nullptr, then the cell has already been filled.
	//		- If the key value of the new node is less than the potential parent key value, then we have a look at the left child.
	//			-- If the left child is nullptr (empty node), then the loop breaks and the new node will become the left child.
	//		- If the key value is bigger instead, then we do the same but look at the right child instead.
	// currParent is the last verified parent candidate. potentialParent considers a new candidate, which could turn out to be nullptr (empty).
	while (potentialParent != nullptr) {
		currParent = potentialParent;
		if (newNode->siteX < potentialParent->siteX) {
			potentialParent = potentialParent->leftChild;
		}
		else {
			potentialParent = potentialParent->rightChild;
		}
	}

	// Set the new node's parent to the last verified, non-empty parent candidate (determined by the preceding loop)
	newNode->parent = currParent;
	// If it turns out that no such non-empty parent was found, then the tree must've been empty and the new node becomes the root of the tree.
	if (currParent == nullptr) {
		this->root = newNode;
		newNode->color = nodeColor::black;
		// At this point, there'll be nothing to fix so we can end the function call here.
		return;
	}
	// If a non-empty parent was found, then we want to pass on whether the new node has become the left child or the right child.
	else if (newNode->siteX < currParent->siteX) {
		currParent->leftChild = newNode;
	}
	else {
		currParent->rightChild = newNode;
	}

	// If the new node has no grandparent, it is impossible for the RB-Tree properties to be violated already, so the function call can be ended here again.
	if (getGrandParent(newNode) == nullptr) {
		return;
	}

	// If there is a grandparent, then it could be that one of the RB-Tree rules is violated (in particular, having two red nodes in a row).
	fixInsertion(newNode);
}

// Two sets of symmetric cases that need fixing after a new red node is inserted, creating a connection between two red nodes.
// Case 1:
//		- The tree is empty (potential parent is nullptr)
// Solution 1:
//		- Just make the new node the root node and paint it black.
//		- This is already in the RBTreeInsert function.

// Case 2:
//		- The uncle of the new node is red
// Solution 2:
//		- Flip the colours of the parent, the uncle and the grandparent.
//		- Then check whether the double red condition is violated for the grandparent (and check again for case 1-4)

// Case 3:
//		- The uncle of the new node is black
//		- The new node is on the opposite side of where the parent is compared to the grandparent (i.e. parent's parent)
//			- That is, the new node is left (right) and the parent of the new node is right (left).
// Solution 3:
//		- Rotate the parent of the new node.

// Case 4:
//		- The uncle of the new node is black
//		- The new node is on the same side as the parent is compared to the grandparent.
//			- That is, the new node is left (right) and the parent of the new node is also left (right).
//		- Flip the colours of the parent and the grandparent.
//		- Then check whether the double red condition is violated for the grandparent.




// TODO

void RBTree::fixInsertion(RBNode* node) {

}

RBNode* RBTree::rotateLeft(RBNode* node) {
	// What used to be the node's right child will now become the top of the subtree
	RBNode* newTopNode = node->rightChild;
	// Meanwhile, what used to be this former right child's left child will now become directly connected to the node being rotated.
	node->rightChild = newTopNode->leftChild;
	// If this left child being moved over actually exists, then its parent is updated to be the former top node.
	if (newTopNode->leftChild != nullptr) {
		newTopNode->leftChild->parent = node;
	}
	// Since the new top node is moving up, it needs its parent updated.
	newTopNode->parent = node->parent;
	// If this new parent doesn't actually exist (nullptr), then we must be at the root of the whole tree
	if (node->parent == nullptr) {
		this->root = newTopNode;
	}
	// If the former top node was its parent's left child, then now the new top node is the left child. Same logic if it was the right child.
	else if (node == node->parent->leftChild) {
		node->parent->leftChild = newTopNode;
	}
	else {
		node->parent->rightChild = newTopNode;
	}
	// Since the new top node is now above the former top node, this former top node has become its left child.
	newTopNode->leftChild = node;
	// Symmetrically, the former top node has become the new top node's child instead.
	node->parent = newTopNode;
}

// Almost identical to rotateLeft, but with the directions flipped where appropriate.
RBNode* RBTree::rotateRight(RBNode* node) {
	RBNode* newTopNode = node->leftChild;
	node->leftChild = newTopNode->rightChild;
	if (newTopNode->rightChild != nullptr) {
		newTopNode->rightChild->parent = node;
	}
	newTopNode->parent = node->parent;
	if (node->parent == nullptr) {
		this->root = newTopNode;
	}
	else if (node == node->parent->leftChild) {
		node->parent->leftChild = newTopNode;
	}
	else {
		node->parent->rightChild = newTopNode;
	}
	newTopNode->rightChild = node;
	node->parent = newTopNode;
}