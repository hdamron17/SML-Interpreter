/* 
 * Virtual CPU for interpreting simple machine language (SML)
 * File:   cpu.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "cpu.h"

using namespace std;

static const string RED = "\u001B[31;1m";
static const string RESET = "\u001B[0m";

/**
 * Constructor from stream containing "machine code"
 * @param file input file stream containing "machine code"
 */
cpu::cpu(istream *file) {
    this->load_mem(file);
    ip = 0;
    sp = 99;
    this->loop();
}

/**
 * Default destructor
 */
cpu::~cpu() {
}

void cpu::load_mem(istream *file) {
    string stringop;
    int opcode;
    size_t index = 0;
    (*file) >> stringop;
    while(!(*file).eof()) {
        opcode = stoi(stringop);
        ram[index] = opcode;
        (*file) >> stringop;
        index++;
    }
    while(index < ram.size()) {
        ram[index] = 0;
        index++;
    }
}

void cpu::loop() {
    bool quit = false;
    int input_num = 1;
    while(!quit) {
        ir = ram[ip];
        ip++;
        int opcode = ir / 100; //top half
        int address = ir % 100; //bottom half
        if(address < 0 || address > 99) {
            //TODO check if address is between 0 and 99
            cerr << RED << "Broken address" << RESET << endl;
        }
        switch(opcode) {
            case 10: { //read to address
                string input;
                cout << "Input %" << input_num << ": ";
                cin >> input;
                bool correct = false;
                int data = 0;
                while(true) { //loop terminated by break statement
                    try {
                        data = stoi(input);
                        if(data > 99 || data < -100) {
                            cerr << RED << "Number out of range" 
                                                               << RESET << endl;
                            cout << "Try again for input %" << input_num <<": ";
                            cin >> input;
                            continue; //tries again after out of bounds
                        }
                        input_num++;
                        break; //breaks out of loop
                    } catch(invalid_argument& e) {
                        cerr << RED << "Invalid number format" << RESET << endl;
                    } catch(out_of_range& e) {
                        cerr << RED << "Number out of range" << RESET << endl;
                    }
                    cout << "Try again for input %" << input_num <<": ";
                    cin >> input;
                }
                ram[address] = data;
                break;
            } case 11: { //write from address
                cout << ram[address] << endl;
                break;
            } case 20: { //load acc
                acc = ram[address];
                break;
            } case 21: { //store acc
                ram[address] = acc;
                break;
            } case 30: { //add to acc
                acc += ram[address];
                if(acc > 99) {
                    //TODO throw error (for now reset from bottom)
                    cerr << RED << "Accumulator overflow" << RESET << endl;
                    acc = -200 + acc;
                }
                break;
            } case 31: { //sub from acc
                acc -= ram[address];
                if(acc < -99) {
                    //TODO throw error (for now reset to top)
                    cerr << RED << "Accumulator overflow" << RESET << endl;
                    acc = 199 + acc;
                }
                break;
            } case 32: { //div into acc
                if(ram[address] == 0) {
                    cerr << RED << "Cannot divide by zero - I ignored you"
                                                               << RESET << endl;
                    // TODO throw error (for now yell at user)
                } else {
                    acc /= ram[address];
                }
                break;
            } case 33: { //mult by acc
                acc *= ram[address];
                if(acc > 99) {
                    //TODO throw error (for now reset to bottom)
                    cerr << RED << "Accumulator overflow" << RESET << endl;
                    acc = -101 + (acc % 100 + 1);
                } else if(acc < -99) {
                    //TODO throw errors (for now reset to top)
                    cerr << RED << "Accumulator overflow" << RESET << endl;
                    acc = 100 + (acc % 100 - 1);
                }
                break;
            } case 40: { //branch
                //TODO make sure address is between 0 and 99
                ip = address;
                break;
            } case 41: { //branch if negative
                //TODO make sure address is between 0 and 99
                if(acc < 0) {
                    ip = address;
                }
                break;
            } case 42: { //branch if zero
                //TODO make sure address is between 0 and 99
                if(acc == 0) {
                    ip = address;
                }
                break;
            } case 43: { //halt
                quit = true;
                break;
            } case 00: { //easter egg
                int size = int(log10(ram[address]));
                cout << "  "; for(int i = 0; i <= size + 2; i++) {cout << "_";}
                cout << "\n < " << ram[address] << " >\n  ";
                for(int i = 0; i <= size + 2; i++) {cout << "-";}
                cout << "\n    \\\n     \\  __\n       UooU\\.'" 
                     << RED << "@@@@@@" << RESET << "`.\n       \\__/("
                     << "\u001B[32;1m@@@@@@@@@@" << RESET << ")\n            ("
                     << "\u001B[33;1m@@@@@@@@" << RESET << ")\n            `YY"
                     << "\u001B[34;1m~~~~" << RESET << "YY'\n             ||   "
                     << " ||\n"; //Don't hate me - it's intentionally obfuscated
                // Thanks to cowsay sheep.cow file for the design
                break;
            } default: {
                //TODO broken opcode
                cerr << RED << "Unknown opcode" << RESET << endl;
                quit = true;
                break;
            }
        }
    }
}

string cpu::dump() const {
    stringstream output;
    for(int i = 0; i < ram.size(); i++) {
        if((i + 1) % 10 == 0)
            output << ram[i] << " \n";
        else
            output << ram[i] << " \t";
    }
    return output.str();
}