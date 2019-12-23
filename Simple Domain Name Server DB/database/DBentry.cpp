/* 
 * Written by: Ramakrishna Natarajan
 * 
 */

#include "DBentry.h"

// Constructors
DBentry::DBentry() { //default constructor
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

// Destructor
DBentry::~DBentry() { //default destructor
}

// Accessors
string DBentry::getName() const {
    return name;
}

unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

bool DBentry::getActive() const {
    return active;
}

// Mutators
void DBentry::setName(string _name) {
    name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}

void DBentry::setActive(bool _active) {
    active = _active;
}
