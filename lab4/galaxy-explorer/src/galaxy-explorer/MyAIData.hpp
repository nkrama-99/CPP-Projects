/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#include <galaxy-explorer/GameAI.hpp>

#include <iostream>

using namespace std;

/**
 * Student editable struct for storing their ai state
 * Yes, you may change this header.
 * Maybe you want to remember the last asteroid Id you shot at?
 */
struct MyAIData {
    bool debug_on = true;
    bool firstShot = true;
    bool flag = true;
    int acw = 3000;
    int cw = 3000;
    int init = 1;
    
    void setFalse() {
        cout << "FIRST SHOT is set to false" << endl;
        firstShot = false;
    }
};


#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
