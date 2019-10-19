//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//  Written by Ramakrishna Natarajan.
//

/*
    * ISSUE UPDATES:
    * is it ok if shape type is a number?
    * is it ok if locX/(any int argument) if float is passed - does it truncate the value
    * if "create ani triangle" (ani exists) - should error be: "shape exists" or "too few arguments"
    * shapeArray is full!! erorr message needs to be implemented
    *  
    * RESOLVED ISSUES:
    * problem: namenot found for shapes in the middle of the array (AFFECTING ALL FUNCTIONS)
    * Need to check for too little or much arguments case
    * PROBLEM: littleArgument_checker is eating stream, it is not suppose to
    * 
*/

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void command_maxShape(stringstream *input);
void command_create(stringstream *input);
void command_move(stringstream *input);
void command_rotate(stringstream *input);
void command_draw(stringstream *input);
void command_delete(stringstream *input);
bool manyArgument_checker(stringstream *input);
bool littleArgument_checker(stringstream *input, int order);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        if (littleArgument_checker(&lineStream, 1)) 
            return;

        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        if (command == "maxShapes") {
            command_maxShape(&lineStream);
            shapesArray = new shape*[max_shapes];
            for (int i=0; i<max_shapes; i++)
                shapesArray[i] = NULL;
            
        } else if (command == "create") {
            if (shapeCount == max_shapes) {
                cout << "shape array is full" << endl;
            } else {   
                command_create(&lineStream);
            }
            
        } else if (command == "move") {
            command_move(&lineStream);

        } else if (command == "rotate") {
            command_rotate(&lineStream);

        } else if (command == "draw") {
            command_draw(&lineStream);

        } else if (command == "delete") {
            command_delete(&lineStream);
        } else {
            // It has to be one of these, if input
            cout << "Error: invalid command" << endl; //No need to flush stream as getline function is being used
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    cout << "terminate program" << endl;
    return 0;
}

void command_maxShape(stringstream *input) {
    float input_maxShape; 
    *input >> input_maxShape;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } 

    if (input_maxShape >= 0 && input_maxShape-input_maxShape==0) {
        max_shapes = input_maxShape;
    }

    cout << "New database: max shapes is " << max_shapes << endl;
}

void command_create(stringstream *input) {
    string name, type;
    int locX, locY, sizeX, sizeY;

    // checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    
    // cout << "main: AFTER name EXTRACTION original: " << (*input).str() << endl;
    cout << "main: name EXTRACTED from original: " << name << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions        
        for (int i=0; i<7; i++) { //if shape name is command name
            if (name == keyWordsList[i]) {
                cout << "invalid shape name" << endl;
                return;
            }
        }
        
        for (int i=0; i<3; i++) { //if shape name is shapetype name
            if (name == shapeTypesList[i]) {
                cout << "invalid shape name" << endl;
                return;
            }
        }

        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                cout << "shape name exists" << endl;
                return;
            } 
        }
    } 

    //name is valid here, proceed with type

    //checking if too few arguments
    if (littleArgument_checker(input, 2)) 
        return;

    *input >> type;

    // cout << "main: AFTER type EXTRACTION original: " << (*input).str() << endl;
    cout << "main: type EXTRACTED from original: " << type << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //vallid argument, check for other conditions
        bool validArgument = false;
        for (int i=0; i<3; i++) {
            if (type == shapeTypesList[i]) {//if correct shape type, trigger validArgument 
                validArgument = true;
            }
        }
        //if forloop doesn't break, type is invalid
        if (!validArgument) {
            cout << "invalid shape type" << endl;
            return;    
        }
    } 

    //type is valid here, proceed with locX

    //checking if too few arguments
    if (littleArgument_checker(input, 3))
        return;

    *input >> locX;
    // cout << "main: AFTER locX EXTRACTION original: " << (*input).str() << endl;
    cout << "main: locX EXTRACTED from original: " << locX << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locX<0) {
            cout << "invalid value" << endl;
            return;
        }
    } 

    //locX is valid here, proceed with locY

    //checking if too few arguments
    if (littleArgument_checker(input, 4)) 
        return;

    *input >> locY;
    // cout << "main: AFTER locY EXTRACTION original: " << (*input).str() << endl;
    cout << "main: locY EXTRACTED from original: " << locY << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locY<0) {
            cout << "invalid value" << endl;
            return;
        }
    } 

    //locY is valid here, proceed with Size

    //checking if too few arguments
    if (littleArgument_checker(input, 5)) 
        return;

    *input >> sizeX;
    // cout << "main: AFTER sizeX EXTRACTION original: " << (*input).str() << endl;
    cout << "main: sizeX EXTRACTED from original: " << sizeX << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (sizeX<0) {
            cout << "invalid value" << endl;
            return;
        }
    } 

    //sizeX is valid here, proceed with SizeY

    //checking if too few arguments
    if (littleArgument_checker(input, 6)) 
        return;

    *input >> sizeY;
    // cout << "main: AFTER sizeY EXTRACTION original: " << (*input).str() << endl;
    cout << "main: sizeY EXTRACTED from original: " << sizeY << endl;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (sizeY<0) {
            cout << "invalid value" << endl;
            return;
        }
    }

    //sizeY is valid here

    //check if too many arguments exist
    if (manyArgument_checker(input)) 
        return;

    //all arguments are valid, create the object
    shapesArray[shapeCount] = new shape(name, type, locX, locY, sizeX, sizeY); 
    shapeCount++; //increment counter after successull creation
    cout << "Created " << name << ": " << type << " "  << locX << " "  << locY << " "  << sizeX << " "  << sizeY << endl;
}

void command_move(stringstream *input) {
    string name;
    int locX, locY;
    int location;
    bool nameFound = false;

    //checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check if name exists
        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "shape name not found" << endl; 
            return;
        }
    } 

    //location now knows the array position to manipulate
    //name is valid, proceed to locX

    //checking if too few arguments
    if (littleArgument_checker(input, 2)) 
        return;

    *input >> locX;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locX<0) {
            cout << "invalid value" << endl;
            return;
        }
    }

    //locX is valid, proceed to locY

    //checking if too few arguments
    if (littleArgument_checker(input, 3)) 
        return;

    *input >> locY;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locY<0) {
            cout << "invalid value" << endl;
            return;
        }
    }

    //locY is valid

    //check if too many arguments exist
    if (manyArgument_checker(input)) 
        return;

    //all arguments are valid, move the object now.
    (*shapesArray[location]).setXlocation(locX);
    (*shapesArray[location]).setYlocation(locY);
    cout << "Moved " << name << " to " << locX << " " << locY << " " << endl;
}

void command_rotate(stringstream *input) {
    string name;
    int angle, location;
    bool nameFound = false;

    //checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check if name exists
        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "shape name not found" << endl; 
            return;
        }
    } 

    //location now knows the array position to manipulate
    //name is valid, proceed to angle

    //checking if too few arguments
    if (littleArgument_checker(input, 2)) 
        return;
    
    *input >> angle;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (angle<0 || angle>360) {
            cout << "invalid value" << endl;
            return;
        }
    }

    //angle is valid

    //check if too many arguments exist
    if (manyArgument_checker(input)) 
        return;

    //all arguments are valid, rotate    the object now.
    (*shapesArray[location]).setRotate(angle);
    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
}

void command_draw(stringstream *input) {
    string name;
    int location;
    bool nameFound = false;

    //checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else {
        //if "all" , draw all and return
        if (name == "all") { 
            //check if too many arguments exist
            if (manyArgument_checker(input)) 
                return;
            
            cout << "Drew all shapes" << endl;        
            for (int i=0; i<shapeCount; i++) { 
                (*shapesArray[i]).draw();
            }
            
            return;
        }
           
        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "shape name not found" << endl; 
            return;
        }

        //check if too many arguments exist
        if (manyArgument_checker(input)) 
            return;

        //shape name is present, draw the shape
        (*shapesArray[location]).draw();
    } 
}

/*
void command_delete(stringstream *input) {
    string name;
    int location;
    bool nameFound = false;

    //checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else {
        if (name == "all") {
            //check if too many arguments exist
            if (manyArgument_checker(input)) 
                return;
            
            for (int i=0; i<shapeCount; i++) {
                delete shapesArray[i];
                shapesArray[i] = NULL;
            }
            
            cout << "Deleted: all shapes" << endl;
            shapeCount = 0; //resetting shapecounter
            return;
        } 

        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "shape name not found" << endl; 
            return;
        }

        //check if too many arguments exist
        if (manyArgument_checker(input)) 
            return;

        //shape name is present, delete the shape
        cout << "Deleted shape " << name << endl;
        delete shapesArray[location];

        //rearrange order
        for (location; location<shapeCount; location++) {
            shapesArray[location] = shapesArray[location+1];
        }
        shapesArray[location] = NULL; //last location is now null

        //need to edit the shapecounter
        shapeCount--;
    } 
}
*/

void command_delete(stringstream *input) {
    string name;
    int location;
    bool nameFound = false;

    //checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else {
        if (name == "all") {
            //check if too many arguments exist
            if (manyArgument_checker(input)) 
                return;
            
            for (int i=0; i<shapeCount; i++) {
                delete shapesArray[i];
                shapesArray[i] = NULL;
            }
            
            cout << "Deleted: all shapes" << endl;
            return;
        } 

        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "shape name not found" << endl; 
            return;
        }

        //check if too many arguments exist
        if (manyArgument_checker(input)) 
            return;

        //shape name is present, delete the shape
        cout << "Deleted shape " << name << endl;
        delete shapesArray[location];
        shapesArray[location] = NULL;
    } 
}

bool manyArgument_checker(stringstream *input) { //return true if too many arguments
    string excessChecker;
    *input >> excessChecker;

    if (!((*input).fail())) { //if input is correct (!true) excess arguments are present, return true
        cout << "too many arguments" << endl;
        return true;
    }

    //input is incorrect (only possibility is NULL or ----- ?EOF?) so, returun false 
    return false;
}

bool littleArgument_checker(stringstream *input, int order) { //return true if too little arguments
    string eol_checker;
    stringstream duplicateStream((*input).str()); //stringstream ss2(ss1.str());

    for (int i=1; i<=order+1; i++)
        duplicateStream >> eol_checker;

    cout << "help: EXTRACTED from duplicate: " << eol_checker << endl;

    if (duplicateStream.fail()) {// if it hits \n it'll fail
        cout << "too few arguments" << endl;
        return true;
    }

    return false;
}


/* NOTES FOR buffer copying

#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss1;
    ss1 << "some " << 123 << " stuff" << std::flush;

    std::stringstream ss2;
    ss2 << ss1.rdbuf(); // copy everything inside ss1's buffer to ss2's buffer

    std::cout << ss1.str() << std::endl;
    std::cout << ss2.str() << std::endl;
}

OR can do this

stringstream ss2(ss1.str());

*/