/* 
 * Main run file for SML virtual machine
 * File:   main.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:24 AM
 */

#include <iostream>
#include <fstream>
#include "src/cpu.h"

using namespace std;

/**
 * Unittest selects from test code database
 */
void unittest() {
    string filename;
    string selection;
    int num; //selection number
    string sheepstr;
    bool sheep;
    cout << "Select a unittest (1-10)\n"
            "  1.  Sum1\n"
            "  2.  Sum1\n"
            "  3.  Mul1\n"
            "  4.  Div1\n"
            "  5.  GreaterTest\n"
            "  6.  TinyLoop\n"
            "  7.  LargeLoop\n"
            "  8.  LargerLoop\n"
            "  9.  Err1\n"
            "  10. Err2\n"
            ">>> ";
    cin >> selection;
    try{
        num = stoi(selection);
    } catch(invalid_argument& e) {
        cerr << "\u001B[31mInvalid unittest selection. Using Sum1 by default"
                "\u001B[0m" << endl;
        selection = 1;
    }
    cout << "Would you like to sheep out your code (y/n | default: n)?\n>>> ";
    cin >> sheepstr;
    if(sheepstr.size() == 0)
        sheep = false;
    else
        sheep = sheepstr[0] == 'y';
    switch(num) {
        case 1: {
            filename = "Sum1.txt";
            break;
        } case 2: {
            filename = "Sub1.txt";
            break;
        } case 3: {
            filename = "Mul1.txt";
            break;
        } case 4: {
            filename = "Div1.txt";
            break;
        } case 5: {
            filename = "GreaterTest.txt";
            break;
        } case 6: {
            filename = "TinyLoop.txt";
            break;
        } case 7: {
            filename = "LargeLoop.txt";
            break;
        } case 8: {
            filename = "LargerLoop.txt";
            break;
        } case 9: {
            filename = "Err1.txt";
            break;
        } case 10: {
            filename = "Err2.txt";
            break;
        } 
    }
    ifstream test(filename);
    cpu vm(&test, sheep);
    vm.run();
}

/*
 * Main function for SML VM
 * Note: accepts filename as only command line argument
 */
int main(int argc, char** argv) {
    if(argc > 1) {
        ifstream test(argv[1]);
        
        string sheepstr;
        bool sheep;
        cout << "Would you like to sheep out your code (y/n | default: n)?\n>>> ";
        cin >> sheepstr;
        if(sheepstr.size() == 0)
            sheep = false;
        else
        sheep = sheepstr[0] == 'y';
        
        cpu vm(&test, sheep);
        vm.run();
    } else {
        unittest();
    }
    return 0;
}


