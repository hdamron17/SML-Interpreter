/* 
 * Main run file for SML virtual machine
 * File:   main.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:24 AM
 */

#include <cstdlib>
#include <fstream>
#include "src/cpu.h"

//TODO remove
#include <sstream>
#include <iostream>

using namespace std;

/*
 * Main function for SML VM
 */
int main(int argc, char** argv) {
    ifstream test("testcode.txt");
    cpu vm(&test);
    cout << vm.dump();
    return 0;
}

