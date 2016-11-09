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
    string filename = "";
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
        if(num > 10 | num < 0) {
            cerr << "\u001B[31mInvalid unittest selection. Using Sum1 by default"
                    "\u001B[0m" << endl;
            num = 1;
        }
    } catch(invalid_argument& e) {
        cerr << "\u001B[31mInvalid unittest selection. Using \'Sum1\' by default"
                "\u001B[0m" << endl;
        num = 1;
    }
    cout << "Would you like to sheep out your code (y/n | default: n)?\n>>> ";
    cin >> sheepstr;
    if(sheepstr.size() == 0 | sheepstr[0] == 'n')
        sheep = false;
    else if(sheepstr[0] == 'y') {
        sheep = true;
    } else {
        cerr << "\u001B[31mThe sheep is confused and refuses to speak"
                "\u001B[0m" << endl;
    }
    switch(num) {
        case 1: {
            filename = "tests/Sum1.txt";
            break;
        } case 2: {
            filename = "tests/Sub1.txt";
            break;
        } case 3: {
            filename = "tests/Mul1.txt";
            break;
        } case 4: {
            filename = "tests/Div1.txt";
            break;
        } case 5: {
            filename = "tests/GreaterTest.txt";
            break;
        } case 6: {
            filename = "tests/TinyLoop.txt";
            break;
        } case 7: {
            filename = "tests/LargeLoop.txt";
            break;
        } case 8: {
            filename = "tests/LargerLoop.txt";
            break;
        } case 9: {
            filename = "tests/Err1.txt";
            break;
        } case 10: {
            filename = "tests/Err2.txt";
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
        if(sheepstr.size() == 0 | sheepstr[0] == 'n')
            sheep = false;
        else if(sheepstr[0] == 'y') {
            sheep = true;
        } else {
            cerr << "\u001B[31mThe sheep is confused and refuses to speak"
                    "\u001B[0m" << endl;
        }
        
        cpu vm(&test, sheep);
        vm.run(true);
    } else {
        unittest();
    }
    return 0;
}


