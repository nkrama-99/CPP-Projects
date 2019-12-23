/* 
 * Written by: Ramakrishna Natarajan
 * 
 */

#include <iostream>
#include <sstream>
#include <string>

#include "TreeDB.h"

using namespace std;

// PROTOTYPES
void command_insert(stringstream *input, TreeDB* dataBase);
void command_find(stringstream *input, TreeDB* dataBase);
void command_remove(stringstream *input, TreeDB* dataBase);
void command_printprobes(stringstream *input, TreeDB* dataBase);
void command_updatestatus(stringstream *input, TreeDB* dataBase);

int main() {

    string line;
    string command;

    TreeDB dataBase;
    
    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;
        
        if (command == "insert") {
            command_insert(&lineStream, &dataBase);
        } else if (command == "find") { 
            command_find(&lineStream, &dataBase);
        } else if (command == "remove") {
            command_remove(&lineStream, &dataBase);
        } else if (command == "printall") {
            cout << dataBase;

        } else if (command == "printprobes") {
            command_printprobes(&lineStream, &dataBase);
        } else if (command == "removeall") {
            dataBase.clear();
            cout << "Success" << endl;
        } else if (command == "countactive") {
            dataBase.countActive();
        } else if (command == "updatestatus") {
            command_updatestatus(&lineStream, &dataBase);
        }

        cout << "> "; // Prompt for input
        command = "reset"; // just making it is resetted
        getline(cin, line);
    }  // End input loop until EOF.
    
    dataBase.clear();
    return 0;
}

void command_insert(stringstream *input, TreeDB* dataBase) {
    string name;
    unsigned int IPaddress;
    string input_active;
    bool active;
    bool insertSuccess;

    *input >> name;
    *input >> IPaddress;
    *input >> input_active;

    if (input_active == "active") { // is active
        active = true;
    } else { // if not active, means inactive
        active = false;
    }
    
    // cout << "INSERT (" << name << " " << IPaddress << " " << input_active << ")" << endl;
    
    DBentry* newEntry = new DBentry(name, IPaddress, active);
    insertSuccess = dataBase->insert(newEntry); // insert checks if duplicate exists (return false if exists)

    if (insertSuccess)
        cout << "Success" << endl;
    else {
        delete newEntry;
        cout << "Error: entry already exists" << endl;
    }

    return;
}

void command_find(stringstream *input, TreeDB* dataBase) {
    string name;
    
    *input >> name;
    DBentry* entryFound = dataBase->find(name);
    
    if (entryFound == nullptr) // means name is not found
        cout << "Error: entry does not exist" << endl;
    else 
        cout << (*entryFound);

    return;
}

void command_remove(stringstream *input, TreeDB* dataBase) {
    string name;
    bool removeSuccess;

    *input >> name;
    removeSuccess = dataBase->remove(name);

    if (removeSuccess)
        cout << "Success" << endl;
    else
        cout << "Error: entry does not exist" << endl;

    return;
}

void command_printprobes(stringstream *input, TreeDB* dataBase) {
    string name;
    
    *input >> name;
    DBentry* entryFound = dataBase->find(name);
    
    if (entryFound == nullptr) // means name is not found
        cout << "Error: entry does not exist" << endl;
    else 
        dataBase->printProbes(); //NEED TO BE FIXED

    return;
}

void command_updatestatus(stringstream *input, TreeDB* dataBase) {
    string name;
    string input_active;
    
    *input >> name;
    *input >> input_active;

    DBentry* entryFound = dataBase->find(name);
    
    if (entryFound == nullptr) {// means name is not found
        cout << "Error: entry does not exist" << endl;
    } else { 
        if (input_active == "active") // is active
            entryFound->setActive(true);
        else // if not active, means inactive
            entryFound->setActive(false);
        cout << "Success" << endl;
    }

    return;
}

ostream& operator<< (ostream& out, const DBentry& rhs) {
    out << rhs.name << " : " << rhs.IPaddress << " : ";
    
    if (rhs.getActive())
        cout << "active" << endl;
    else
        cout << "inactive" << endl;

    return out;  
}

// prints in ascending order of the tree
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    if (rhs.dbEmpty() == false)
        out << rhs.root;    
}

ostream& operator<< (ostream& out, TreeNode* rhs) { //must implement LNR to print in ascending order
    if (rhs->getLeft() != nullptr) 
        out << rhs->getLeft();
    
    out << *(rhs->getEntry());
    
    if (rhs->getRight() != nullptr)
        out << rhs->getRight();
}

