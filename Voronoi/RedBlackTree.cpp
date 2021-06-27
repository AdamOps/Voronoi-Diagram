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

void RBTree::insert(float siteX_, float siteY_) {
	// Since a node has been inserted, the number of nodes has gone up.
	this->nodeCount++;

	// Set default node properties
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
		newNode->direction = nodeDirection::left;
	}
	else {
		currParent->rightChild = newNode;
		newNode->direction = nodeDirection::right;
	}

	// If the new node has no grandparent, it is impossible for the RB-Tree properties to be violated already, so the function call can be ended here again.
	if (getGrandParent(newNode) == nullptr) {
		return;
	}

	// If there is a grandparent, then it could be that one of the RB-Tree rules is violated (in particular, having two red nodes in a row).
	fixInsertion(newNode);
}

// TODO
void RBTree::deleteNode(RBNode* node) {
	// With the node deleted, the number of nodes decreases.
	this->nodeCount--;
}

void RBTree::updateDirection(RBNode* node) {
	if (node->parent == nullptr) {
		node->direction = nodeDirection::rootDir;
		return;
	}
	if (node == node->parent->leftChild) {
		node->direction = nodeDirection::left;
	}
	else if (node == node->parent->rightChild) {
		node->direction = nodeDirection::right;
	}
}

void RBTree::rotateLeft(RBNode* node) {
	// What used to be the node's right child will now become the top of the subtree
	RBNode* newTopNode = node->rightChild;
	// Meanwhile, what used to be this former right child's left child will now become directly connected to the node being rotated.
	node->rightChild = newTopNode->leftChild;
	// If this left child being moved over actually exists, then its parent is updated to be the former top node.
	if (newTopNode->leftChild != nullptr) {
		newTopNode->leftChild->parent = node;
	}
	// Since the new top node is moving up, it needs its parent updated, as well as its direction.
	newTopNode->parent = node->parent;
	updateDirection(newTopNode);

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
	// Its direction may have changed, so best to update it.
	updateDirection(newTopNode->leftChild);
}

// Almost identical to rotateLeft, but with the directions flipped where appropriate.
void RBTree::rotateRight(RBNode* node) {
	RBNode* newTopNode = node->leftChild;
	node->leftChild = newTopNode->rightChild;
	if (newTopNode->rightChild != nullptr) {
		newTopNode->rightChild->parent = node;
	}
	newTopNode->parent = node->parent;
	updateDirection(newTopNode);
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
	updateDirection(newTopNode->rightChild);
}



// Two sets of symmetric cases that need fixing after a new red node is inserted, creating a connection between two red nodes.
// Case 1:
//		- The tree is empty (potential parent is nullptr)
// Solution 1:
//		- Just make the new node the root node and paint it black.
//		- return;

// Case 2:
//		- The uncle of the new node is red
// Solution 2:
//		- Flip the colours of the parent, the uncle and the grandparent.
//		- Then check whether the double red condition is violated for the grandparent 
//		- fixInsertion(grandparent)

// Case 3:
//		- The uncle of the new node is black
//		- The new node is on the opposite side of where the parent is compared to the grandparent (i.e. parent's parent)
//			- That is, the new node is the left (right) child and the parent of the new node is the right (left) child of its parent.
// Solution 3:
//		- Rotate the parent of the new node.
//		- The tree will now be in case 4.
//		- fixInsertion(parent)

// Case 4:
//		- The uncle of the new node is black
//		- The new node is on the same side as the parent is compared to the grandparent.
//			- That is, the new node is left (right) and the parent of the new node is also left (right).
// Solution 4:
//		- Rotate grandparent
//		- Flip the colours of the parent and the grandparent.
//		- Then check whether the double red condition is violated for the grandparent.
//		- fixInsertion(grandparent)


void RBTree::fixInsertion(RBNode* node) {

	// Check if parent exists. Only if the parent exists do we check for the colour, so that there's no memory violation (trying to access an attribute of a nullptr)
	RBNode* parent = node->parent;
	if (parent != nullptr) {
		if (parent->color == nodeColor::red) {
			// Check if uncle exists and set uncle properties. If uncle is nullptr, it's black by default. Useful for case 2-4
			RBNode* uncle = getUncle(node);
			nodeColor uncleColor;

			if (uncle == nullptr) {
				uncleColor = nodeColor::black;
			}
			else {
				uncleColor = uncle->color;
			}

			// Grandpa also often shows up, so may as well fix him so that he doesn't have to be looked up.
			RBNode* grandpa = node->parent->parent;

			// Case 1:
			if (this->root == nullptr) {
				node->color = nodeColor::black;
				this->root = node;
			}
			// Case 2:
			else if (uncleColor == nodeColor::red) {
				// Flip grandpa's colour
				grandpa->color = (grandpa->color == nodeColor::red) ? nodeColor::black : nodeColor::red;
				// Flip the parent's colour. This must've been red before, as there wouldn't have been a violation otherwise.
				node->parent->color = nodeColor::black;
				// Flip the uncle's colour. Since he must be red in case 2, he gets flipped to black.
				uncle->color = nodeColor::black;
				std::cout << "Direction of parent << " << parent->siteX << " >> is " << (parent->direction == nodeDirection::left ? "left" : "right") << std::endl;
				std::cout << "Flipped an uncle << " << (parent->direction == nodeDirection::left ? parent->parent->rightChild->siteX : parent->parent->leftChild->siteX ) << " >> from red to black" << std::endl;
				// Grandpa's flip might introduce a new problems, so it's time to re-run fixInsertion on grandpa.
				fixInsertion(grandpa);
			}
			// Case 3 and 4:
			else {
				// Case 3:
				if (node->direction != parent->direction) {
					// If the node is the left child, we want to rotate the tree right. If it is the right child, we want to rotate it left. In both cases, the node ends up swapping parent/child roles with the current parent.
					if (node->direction == nodeDirection::right) {
						rotateLeft(parent);
					}
					else {
						rotateRight(parent);
					}
					// This rotation puts the tree in case 4, as now the former parent is the bottom of the two nodes violating the RB properties, but the child direction for both red nodes is the same.
					fixInsertion(parent);
				}
				// Case 4:
				else {
					if (node->direction == nodeDirection::left) {
						rotateRight(grandpa);
					}
					else {
						rotateLeft(grandpa);
					}
					parent->color = (parent->color == nodeColor::red) ? nodeColor::black : nodeColor::red;
					grandpa->color = (grandpa->color == nodeColor::red) ? nodeColor::black : nodeColor::red;
				}
			}
		}
	}

	this->root->color = nodeColor::black;
}

// Helpful function to see what the tree looks like
#include <fstream>
#include <queue>
#include <string>

// Generates a .dot file containing the whole tree (maintaining the stored colour).
void RBTree::printTree() {
	std::ofstream dotFile("RBTree.dot", std::ofstream::out);
	//dotFile.open("RBTree.dot");
	dotFile << "digraph{" << std::endl;

	int nodeNum = 0;
	RBNode* currNode;

	std::queue<RBNode*> newQ;
	newQ.push(this->root);
	while (newQ.empty() == false) {
		currNode = newQ.front();
		newQ.pop();

		std::string nodeNumStr = std::to_string(static_cast<int>(currNode->siteX));
		if (currNode->leftChild != nullptr) {
			std::string newConnect = nodeNumStr + "->" + std::to_string(static_cast<int>(currNode->leftChild->siteX)) + "\n";
			dotFile << newConnect;
			newQ.push(currNode->leftChild);
			std::cout << "Left child found. Adding: " << newConnect << std::endl;
		}
		if (currNode->rightChild != nullptr) {
			std::string newConnect = nodeNumStr + "->" + std::to_string(static_cast<int>(currNode->rightChild->siteX)) + "\n";
			dotFile << newConnect;
			newQ.push(currNode->rightChild);
			std::cout << "Right child found. Adding: " << newConnect << std::endl;
		}


		std::string pushColor;
		if (currNode->color == nodeColor::red) {
			pushColor = std::to_string(static_cast<int>(currNode->siteX)) + "[color = red]\n";
		}
		else {
			pushColor = std::to_string(static_cast<int>(currNode->siteX)) + "[color = black]\n";
		}
		dotFile << pushColor;
	}
	dotFile << "}";
	
	dotFile.close();
}