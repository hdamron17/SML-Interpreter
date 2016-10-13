/* 
 * Main run file for SML virtual machine
 * File:   main.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:24 AM
 */

#include <fstream>
#include "src/cpu.h"

using namespace std;

/*
 * Main function for SML VM
 */
int main(int argc, char** argv) {
    ifstream test("testcode.txt");
    cpu vm(&test);
    return 0;
}

