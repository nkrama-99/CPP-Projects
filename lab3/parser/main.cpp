//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//  Written by Ramakrishna Natarajan.
//


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

        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        if (command == "maxShapes") {
            command_maxShape(&lineStream);
        } else if (command == "create") { 
            command_create(&lineStream);
        } else if (command == "move") {
            command_move(&lineStream);
        } else if (command == "rotate") {
            command_rotate(&lineStream);
        } else if (command == "draw") {
            command_draw(&lineStream);
        } else if (command == "delete") {
            command_delete(&lineStream);
        } else {
            cout << "Error: invalid command" << endl; //No need to flush stream as getline function is being used
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        command = "reset"; //without this, just \n is causing the program to enter the previous command's helper function
        getline(cin, line);   // Get the command line
    }  // End input loop until EOF.
    
    return 0;
}

void command_maxShape(stringstream *input) {
    int input_maxShape; 

    if (littleArgument_checker(input, 1)) 
        return;
    
    *input >> input_maxShape;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } 

    if (input_maxShape < 0) {
        cout << "Error: invalid value" << endl; //No need to flush stream as getline function is being used
        return;
    }

    // making sure buffer is empty, coz the error should be invalid argument if 11abc is the final int_input
    
    if (manyArgument_checker(input)) 
        return;

    max_shapes = input_maxShape;

    shapesArray = new shape*[max_shapes];
            
    for (int i=0; i<max_shapes; i++)
        shapesArray[i] = NULL;
            
    cout << "New database: max shapes is " << max_shapes << endl;
}

void command_create(stringstream *input) {
    string name, type;
    int locX, locY, sizeX, sizeY;

    // checking if too few arguments
    if (littleArgument_checker(input, 1)) 
        return;

    *input >> name;
    
    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions        
        for (int i=0; i<7; i++) { //if shape name is command name
            if (name == keyWordsList[i]) {
                cout << "Error: invalid shape name" << endl;
                return;
            }
        }
        
        for (int i=0; i<3; i++) { //if shape name is shapetype name
            if (name == shapeTypesList[i]) {
                cout << "Error: invalid shape name" << endl;
                return;
            }
        }

        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (name == (*shapesArray[i]).getName()) {
                cout << "Error: shape " << name << " exists" << endl;
                return;
            } 
        }
    } 

    //name is valid here, proceed with type

    //checking if too few arguments
    if (littleArgument_checker(input, 2)) 
        return;

    *input >> type;

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
            cout << "Error: invalid shape type" << endl;
            return;    
        }
    } 

    //type is valid here, proceed with locX

    //checking if too few arguments
    if (littleArgument_checker(input, 3))
        return;

    *input >> locX;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locX<0) {
            cout << "Error: invalid value" << endl;
            return;
        }
    } 

    //locX is valid here, proceed with locY

    //checking if too few arguments
    if (littleArgument_checker(input, 4)) 
        return;

    *input >> locY;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (locY<0) {
            cout << "Error: invalid value" << endl;
            return;
        }
    } 

    //locY is valid here, proceed with Size

    //checking if too few arguments
    if (littleArgument_checker(input, 5)) 
        return;

    *input >> sizeX;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (sizeX<0) {
            cout << "Error: invalid value" << endl;
            return;
        }
    } 

    //sizeX is valid here, proceed with SizeY

    //checking if too few arguments
    if (littleArgument_checker(input, 6)) 
        return;

    *input >> sizeY;

    if ((*input).fail()) {
        cout << "Error: invalid argument" << endl; //No need to flush stream as getline function is being used
        return;
    } else { //valid argument, check for other conditions
        if (sizeY<0) {
            cout << "Error: invalid value" << endl;
            return;
        }
    }

    //sizeY is valid here

    //check if too many arguments exist
    if (manyArgument_checker(input)) 
        return;

    //if array is full
    if (shapeCount == max_shapes) {
        cout << "Error: shape array is full" << endl;
        return;
    }

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
            if (shapesArray[i] != NULL && name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "Error: shape " << name << " not found" << endl; 
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
            cout << "Error: invalid value" << endl;
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
            cout << "Error: invalid value" << endl;
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
            if (shapesArray[i] != NULL && name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "Error: shape " << name << " not found" << endl; 
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
            cout << "Error: invalid value" << endl;
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
                if (shapesArray[i] != NULL) { 
                    (*shapesArray[i]).draw();
                }
            }
            
            return;
        }
           
        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (shapesArray[i] != NULL && name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "Error: shape " << name << " not found" << endl; 
            return;
        }

        //check if too many arguments exist
        if (manyArgument_checker(input)) 
            return;

        //shape name is present, draw the shape
        cout << "Drew " << name << endl;
        (*shapesArray[location]).draw();
    } 
}

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
                if (shapesArray[i] != NULL) {   
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
            }
            
            cout << "Deleted: all shapes" << endl;
            return;
        } 

        for (int i=0; i<shapeCount; i++) { //if shape name exists
            if (shapesArray[i] != NULL && name == (*shapesArray[i]).getName()) {
                location = i;
                nameFound = true; //if shape name is present, name found == true
            }
        }
        if (!nameFound) {
            cout << "Error: shape " << name << " not found" << endl; 
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

    char peekContent = (*input).peek();
    string excessChecker;
    
    *input >> excessChecker;

    if (peekContent == ' ') {
        cout << "Error: too many arguments" << endl;
        return true;
    }

    if (!((*input).fail())) { //if input is correct (!true) excess arguments are present, return true
        cout << "Error: invalid argument" << endl;
        return true;
    }

    return false;
}

bool littleArgument_checker(stringstream *input, int order) { //return true if too little arguments
    string eol_checker;
    stringstream duplicateStream((*input).str()); 

    for (int i=1; i<=order+1; i++)
        duplicateStream >> eol_checker;

    if (duplicateStream.fail()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }

    return false;
}