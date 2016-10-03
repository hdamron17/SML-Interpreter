/* 
 * Main run file for SML virtual machine
 * File:   main.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:24 AM
 */

#include <cstdlib>
#include "src/cpu.h"

//TODO remove
#include <sstream>
#include <iostream>

using namespace std;

/*
 * Main function for SML VM
 */
int main(int argc, char** argv) {
    string input;
    cin >> input;
    istringstream test;
    test.str(input);
    cpu vm(&test);
    return 0;
}

