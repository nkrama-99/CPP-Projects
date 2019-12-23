/* 
 * Written by: Ramakrishna Natarajan
 * 
 * Notes:
 * 1. Should i need to set left and right to null in destructor?
 * 2. Should i need to set entryPtr to null?
 * 
 */

#include "TreeNode.h"

// Constructors
TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = _entryPtr;
    left = nullptr;
    right = nullptr;
}

// Destructor
TreeNode::~TreeNode() {
    delete entryPtr;
    entryPtr = nullptr;
    left = nullptr;
    right = nullptr;
}

// Accessors
TreeNode* TreeNode::getLeft() const {
    return left;
}

TreeNode* TreeNode::getRight() const {
    return right;
}

DBentry* TreeNode::getEntry() const {
    return entryPtr;
}

// Mutators
void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}