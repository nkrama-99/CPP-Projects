/* 
 * NOTES:
 * 1. will i call dbentry destructor automatically? (delete node->getEntry())
 * 2. do i need to set (left and right) to nullptr after deletring (delete_tree/remove)
 * 3. REMOVE IS NOT DONE
 * 
 * what is probe?
 * how to remove?
 * why is my name giving error?
 * 
 */

#include "TreeDB.h"
#include <iostream>
#include <string.h>

// constructors
TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

// destructors
TreeDB::~TreeDB() {
    clear();
}

// methods
bool TreeDB::dbEmpty() const {
    if (root == nullptr)
        return true;
    else
        return false;
}

bool TreeDB::insert(DBentry* newEntry) {
    if (find(newEntry->getName()) != nullptr) {
        return false;
    }

    TreeNode* newNode = new TreeNode(newEntry);
    
    bool success = insert_bst(newNode, root);
    if (success) {
        return true;
    } else {
        delete newNode;
        return false;
    }
}

bool TreeDB::insert_bst(TreeNode* newNode, TreeNode* root_ptr) {
    // if db tree is empty (NOTE USING "root" HERE)
    if (dbEmpty()) {
        // cout << "DB is empty" << endl;
        root = newNode;        
        return true;
    }
    
    // entry exists, return false
    if (newNode->getEntry()->getName() == root_ptr->getEntry()->getName()) {
        return false;
    }

    // if newNode is before root_ptr
    if (newNode->getEntry()->getName() < root_ptr->getEntry()->getName()) {
        if (root_ptr->getLeft() == nullptr) {
            root_ptr->setLeft(newNode);
            return true;
        } else {
            // cout << "navigate left" << endl;
            insert_bst(newNode, root_ptr->getLeft());
        }
    }
    
    // if newNode is after root_ptr
    if (newNode->getEntry()->getName() > root_ptr->getEntry()->getName()) {
        if (root_ptr->getRight() == nullptr) {
            root_ptr->setRight(newNode);
            return true;
        } else {
            // cout << "navigate right" << endl;
            insert_bst(newNode, root_ptr->getRight());
        }
    }
}

DBentry* TreeDB::find(string name) { //PROBECOUNT MUST BE MANIPULATED
    probesCount = 0; //reset probesCount

    TreeNode* node_found = find_bst(root, name);

    if (node_found == nullptr) //checking if null_ptr is pointing to nullptr
        return nullptr;
    else
        return node_found->getEntry();
}

TreeNode* TreeDB::find_bst(TreeNode* node_ptr, string name) {
    probesCount++; //incrementing probesCount everytime the function is called recursively

    // if node not found - does not exist
    if (node_ptr == nullptr) {
        return nullptr;
    }

    // if node is found
    if (name == node_ptr->getEntry()->getName()) {
        return node_ptr;
    }

    // if name is before node_ptr
    if (name < node_ptr->getEntry()->getName()) {
        return find_bst(node_ptr->getLeft(), name);
    }

    //if name is after node_ptr
    if (name > node_ptr->getEntry()->getName()) {
        return find_bst(node_ptr->getRight(), name);
    }
}

bool TreeDB::remove(string name) {
    if (find_bst(root, name) == nullptr) { //node does not exist
        return false;
    } else {
        remove_bst(root, name);
        return true;
    }    
}

// TreeNode* TreeDB::remove_bst(TreeNode* node_ptr, string name) { //failign if root is node or has one child

//     if (node_ptr == nullptr) {
//         return nullptr;
//     }

//     else if (name < node_ptr->getEntry()->getName()) { //node to delete is on the left, navigate left
//         node_ptr->setLeft(remove_bst(node_ptr->getLeft(), name));
//     }

//     else if (name > node_ptr->getEntry()->getName()) { //node to delete is on the right, navigate right
//         node_ptr->setRight(remove_bst(node_ptr->getRight(), name));
//     }

//     else if (node_ptr->getLeft() != nullptr && node_ptr->getRight() != nullptr) { //node to delete has 2 child
//         TreeNode* maxNode_ptr = findMax(node_ptr->getLeft());
        
//         // manipulate node to be deleted with information from maxNode
//         node_ptr->getEntry()->setName(maxNode_ptr->getEntry()->getName());
//         node_ptr->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
//         node_ptr->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

//         // delete node recursively
//         node_ptr->setLeft(remove_bst(node_ptr->getLeft(), node_ptr->getEntry()->getName()));

//     }

//     else if (root->getEntry()->getName() == name) { //special case for root node
//         TreeNode* node_toDelete = root; //backup the root to be deleted, before linking the following 
        
        
//         if (root->getLeft() != nullptr && root->getRight() != nullptr) { //root to delete has 2 child
//             TreeNode* maxNode_ptr = findMax(root->getLeft());
            
//             // manipulate node to be deleted with information from maxNode
//             root->getEntry()->setName(maxNode_ptr->getEntry()->getName());
//             root->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
//             root->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

//             // delete node recursively
//             root->setLeft(remove_bst(root->getLeft(), root->getEntry()->getName()));

//         }
        
//         else if (root->getLeft() == nullptr) 
//             root = root->getRight();

//         else if (root->getRight() == nullptr)
//             root = root->getLeft();

//         delete node_toDelete;
//     }

//     else { //if node has 1 child or leaf node
//         TreeNode* node_toDelete = node_ptr; //backup the node to be deleted, before linking the following 

//         if (node_ptr->getLeft() == nullptr) 
//             node_ptr = node_ptr->getRight();

//         else if (node_ptr->getRight() == nullptr)
//             node_ptr = node_ptr->getLeft();

//         delete node_toDelete;
//     }

//     return node_ptr;
// }

// TreeNode* TreeDB::remove_bst(TreeNode* node_ptr, string name) { //failign if root is node or has one child

//     if (node_ptr == nullptr) {
//         return nullptr;
//     }

//     else if (root->getEntry()->getName() == name) { //special case for root node
//         TreeNode* node_toDelete = root; //backup the root to be deleted, before linking the following 
        
        
//         if (root->getLeft() != nullptr && root->getRight() != nullptr) { //root to delete has 2 child
//             TreeNode* maxNode_ptr = findMax(root->getLeft());
            
//             // manipulate node to be deleted with information from maxNode
//             root->getEntry()->setName(maxNode_ptr->getEntry()->getName());
//             root->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
//             root->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

//             // delete node recursively
//             root->setLeft(remove_bst(root->getLeft(), root->getEntry()->getName()));

//         }
        
//         else if (root->getLeft() == nullptr) 
//             root = root->getRight();

//         else if (root->getRight() == nullptr)
//             root = root->getLeft();

//         delete node_toDelete;
//     }

//     else if (name < node_ptr->getEntry()->getName()) { //node to delete is on the left, navigate left
//         node_ptr->setLeft(remove_bst(node_ptr->getLeft(), name));
//     }

//     else if (name > node_ptr->getEntry()->getName()) { //node to delete is on the right, navigate right
//         node_ptr->setRight(remove_bst(node_ptr->getRight(), name));
//     }

//     else if (node_ptr->getLeft() != nullptr && node_ptr->getRight() != nullptr) { //node to delete has 2 child
//         TreeNode* maxNode_ptr = findMax(node_ptr->getLeft());
        
//         // manipulate node to be deleted with information from maxNode
//         node_ptr->getEntry()->setName(maxNode_ptr->getEntry()->getName());
//         node_ptr->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
//         node_ptr->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

//         // delete node recursively
//         node_ptr->setLeft(remove_bst(node_ptr->getLeft(), node_ptr->getEntry()->getName()));

//     }

//     else { //if node has 1 child or leaf node
        
//         TreeNode* node_toDelete = node_ptr; //backup the node to be deleted, before linking the following 

//         if (node_ptr->getLeft() == nullptr) 
//             node_ptr = node_ptr->getRight();

//         else if (node_ptr->getRight() == nullptr)
//             node_ptr = node_ptr->getLeft();

//         delete node_toDelete;
//     }

//     return node_ptr;
// }


TreeNode* TreeDB::remove_bst(TreeNode* node_ptr, string name) { //failign if root has 2 child

    if (node_ptr == nullptr) {
        return nullptr;
    }

    if (root->getEntry()->getName() == name) { //special case for root node

//        cout << "It is root node" << endl;

        if (node_ptr->getLeft() != nullptr && node_ptr->getRight() != nullptr) { //root to delete has 2 child
            TreeNode* maxNode_ptr = findMax(root->getLeft());
            
            // manipulate node to be deleted with information from maxNode
            root->getEntry()->setName(maxNode_ptr->getEntry()->getName());
            root->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
            root->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

            // delete node recursively
            node_ptr->setLeft(remove_bst(node_ptr->getLeft(), node_ptr->getEntry()->getName()));

        }
        
        else if (root->getLeft() == nullptr) {
            TreeNode* node_toDelete = root; //backup the root to be deleted, before linking the following 
            root = root->getRight();
            delete node_toDelete;
        }

        else if (root->getRight() == nullptr) {
            TreeNode* node_toDelete = root; //backup the root to be deleted, before linking the following 
            root = root->getLeft();
            delete node_toDelete;
        }

    }
    
    else { // node to delete is not root node

//        cout << "It is NOT root node" << endl;

        if (name < node_ptr->getEntry()->getName()) { //node to delete is on the left, navigate left
            node_ptr->setLeft(remove_bst(node_ptr->getLeft(), name));
        }

        else if (name > node_ptr->getEntry()->getName()) { //node to delete is on the right, navigate right
            node_ptr->setRight(remove_bst(node_ptr->getRight(), name));
        }

        else if (node_ptr->getLeft() != nullptr && node_ptr->getRight() != nullptr) { //node to delete has 2 child
            TreeNode* maxNode_ptr = findMax(node_ptr->getLeft());
            
            // manipulate node to be deleted with information from maxNode
            node_ptr->getEntry()->setName(maxNode_ptr->getEntry()->getName());
            node_ptr->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
            node_ptr->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

            // delete node recursively
            node_ptr->setLeft(remove_bst(node_ptr->getLeft(), node_ptr->getEntry()->getName()));

        }

        else { //if node has 1 child or leaf node
            TreeNode* node_toDelete = node_ptr; //backup the node to be deleted, before linking the following 

            if (node_ptr->getLeft() == nullptr) 
                node_ptr = node_ptr->getRight();

            else if (node_ptr->getRight() == nullptr)
                node_ptr = node_ptr->getLeft();

            delete node_toDelete;
        }
        
    }

    return node_ptr;
}



// TreeNode* TreeDB::remove_bst(TreeNode* node_ptr, string name) { //failign if root is node or has one child

//     if (node_ptr == nullptr) {
//         return nullptr;
//     }

//     else if (name < node_ptr->getEntry()->getName()) { //node to delete is on the left, navigate left
//         node_ptr->setLeft(remove_bst(node_ptr->getLeft(), name));
//     }

//     else if (name > node_ptr->getEntry()->getName()) { //node to delete is on the right, navigate right
//         node_ptr->setRight(remove_bst(node_ptr->getRight(), name));
//     }

//     else if (node_ptr->getLeft() != nullptr && node_ptr->getRight() != nullptr) { //node to delete has 2 child
//         TreeNode* maxNode_ptr = findMax(node_ptr->getLeft());
        
//         // manipulate node to be deleted with information from maxNode
//         node_ptr->getEntry()->setName(maxNode_ptr->getEntry()->getName());
//         node_ptr->getEntry()->setIPaddress(maxNode_ptr->getEntry()->getIPaddress());
//         node_ptr->getEntry()->setActive(maxNode_ptr->getEntry()->getActive());

//         // delete node recursively

//         // node_ptr->setLeft(remove_bst(node_ptr->getLeft(), node_ptr->getEntry()->getName()));
//         delete maxNode_ptr; // attempting to use other method then afshin

//     }

//     else { //if node has 1 child or leaf node
            
//         if (root->getEntry()->getName() == name) { //special case for root node - 1child/leaf
//             TreeNode* node_toDelete = root; //backup the root to be deleted, before linking the following 
            
//             if (root->getLeft() == nullptr) 
//                 root = root->getRight();

//             else if (root->getRight() == nullptr)
//                 root = root->getLeft();

//             delete node_toDelete;
//         }

//         TreeNode* node_toDelete = node_ptr; //backup the node to be deleted, before linking the following 

//         if (node_ptr->getLeft() == nullptr) 
//             node_ptr = node_ptr->getRight();

//         else if (node_ptr->getRight() == nullptr)
//             node_ptr = node_ptr->getLeft();

//         delete node_toDelete;
//     }

//     return node_ptr;
// }


TreeNode* TreeDB::findMax(TreeNode* node_ptr) {
    if (node_ptr != nullptr) {
        while (node_ptr->getRight() != nullptr) //navigates to right most of the tree with root as node to be deleted
            node_ptr = node_ptr->getRight();
    }
    return node_ptr; 
}

TreeNode* TreeDB::findPrev_bst(TreeNode* rootname, string name) {
    //if the parent node has been found
    if (rootname == nullptr) return nullptr;
    if (rootname->getEntry()->getName() == name) return rootname;
    if ((rootname->getLeft() != nullptr && rootname->getLeft()->getEntry()->getName() == name) || (rootname->getRight() != nullptr && rootname->getRight()->getEntry()->getName() == name)) return rootname;
    //if not, move to the sub left or sub right tree
    //left tree
    if (rootname->getLeft() != nullptr && rootname->getEntry()->getName() > name) {
        return findPrev_bst(rootname->getLeft(), name);
    }
    //right tree
    else if (rootname->getRight() != nullptr && rootname->getEntry()->getName() < name) {
        return findPrev_bst(rootname->getRight(), name);
    }
    
    else return nullptr;
    
}



void TreeDB::clear() {
    delete_tree(root);
    root = nullptr;
}

void TreeDB::delete_tree(TreeNode* node_ptr) {
    //if node does not exist, don't do anything
    if (node_ptr == nullptr) {
        return;
    }

    delete_tree(node_ptr->getLeft()); // delete left subtree
    delete_tree(node_ptr->getRight()); // delete right subtree

    // now, we are at the node to be deleted
    delete node_ptr;
}

void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

void TreeDB::countActive() const {
    int counter = 0;
    countActive_bst(root, &counter);
    cout << counter << endl;
}

void TreeDB::countActive_bst(TreeNode* node_ptr, int* counter) const{ // performing NLR traversal - doesn't matter which one we choose here
    if (node_ptr == nullptr) { //base condition to go backwords and modify the results
        return;
    }

    if (node_ptr->getEntry()->getActive()) {
        (*counter)++;
    }

    countActive_bst(node_ptr->getLeft(), counter); // go left subtree
        
    countActive_bst(node_ptr->getRight(), counter); // go right subtree
}
