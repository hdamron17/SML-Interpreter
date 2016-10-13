/* 
 * Virtual CPU for interpreting simple machine language (SML)
 * File:   cpu.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include "cpu.h"

using namespace std;

static string RED = "\u001B[31;1m";
static string RESET = "\u001B[0m";

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
                input_num++;
                int data = stoi(input);
                //TODO use try catch and make sure data is less between 0 and 99
                //for now casting to range
                if(data > 99) {
                    cerr << RED << "Invalid input" << RESET << endl;
                    data = -101 + (data % 100 + 1);
                } else if(data < -99) {
                    cerr << RED << "Invalid input" << RESET << endl;
                    data = 100 + (data % 100 - 1);
                }
                //TODO remove above casting
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
            } default: {
                //TODO broken opcode
                cerr << RED << "Broken opcode" << RESET << endl;
                break;
            }
        }
    }
}

string cpu::dump() {
    stringstream output;
    for(int i = 0; i < ram.size(); i++) {
        if((i + 1) % 10 == 0)
            output << ram[i] << " \n";
        else
            output << ram[i] << " \t";
    }
    return output.str();
}