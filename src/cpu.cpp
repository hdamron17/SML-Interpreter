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
#include <string>
#include <stdexcept>
#include <limits.h>
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
    sheeped = false;
}

/**
 * Constructor from stream containing "machine code" and "sheeped" boolean
 * @param file input file stream containing "machine code"
 * @param sheep if true, outputs with a cute, colorful sheep
 */
cpu::cpu(istream *file, bool sheep) {
    this->load_mem(file);
    ip = 0;
    sp = 99;
    sheeped = sheep;
}

/**
 * Default destructor
 */
cpu::~cpu() {
}

/**
 * Loads memory from an input file stream into 100 index array
 * @param file input file stream with machine code
 */
void cpu::load_mem(istream *file) {
    string stringop;
    int opcode;
    size_t index = 0;
    (*file) >> stringop;
    while(!(*file).eof()) {
        opcode = manual_stoi(stringop);
        ram[index] = opcode;
        (*file) >> stringop;
        index++;
    }
    while(index < ram.size()) {
        ram[index] = 0;
        index++;
    }
}

/**
 * Executes main loop of code - loops until 4300 HALT is reached
 */
void cpu::run() {
    run(false);
}

/**
 * Executes main loop of code - loops until 4300 HALT is reached
 * @param: debug: prints debug dump after each command
 */
void cpu::run(bool debug) {
    bool quit = false;
    int input_num = 1;
    acc = 0;
    while(!quit) {
        ir = ram[ip];
        int opcode = ir / 100; //top half
        int address = ir % 100; //bottom half
        if(address < 0 || address > 99) {
            cerr << RED << "Error: Invalid address accessing - thrown from [" 
                                << ip << "] -> " << ram[ip] << RESET << endl;
        }
        switch(opcode) {
            case 10: { //read to address
                string input;
                cout << "Input #" << input_num << ": ";
                cin >> input;
                bool correct = false;
                int data = 0;
                while(true) { //loop terminated by break statement
                    try {
                        data = manual_stoi(input);
                        if(data > 9999 || data < -9999) {
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
                ram[address] = ram[address] + data;
                break;
            } case 11: { //write from address
                if(sheeped) {
                    cout << sheepout(ram[address]);
                    break;
                } else {
                    cout << ram[address] << endl;
                    break;
                }
            } case 20: { //load acc
                acc = ram[address];
                break;
            } case 21: { //store acc
                ram[address] = acc;
                break;
            } case 30: { //add to acc
                acc += ram[address];
                if(acc > 9999) {
                    cerr << RED << "Error: Accumulator overflow - thrown from ["
                                   << ip << "] -> " << ram[ip] << RESET << endl;
                    quit = true;
                }
                break;
            } case 31: { //sub from acc
                acc -= ram[address];
                if(acc < -9999) {
                    cerr << RED << "Error: Accumulator overflow - thrown from ["
                                   << ip << "] -> " << ram[ip] << RESET << endl;
                    quit = true;
                }
                break;
            } case 32: { //div into acc
                if(ram[address] == 0) {
                    cerr << RED << "Error: Division by zero - thrown from ["
                                   << ip << "] -> " << ram[ip] << RESET << endl;
                    quit = true;
                } else {
                    acc /= ram[address];
                }
                break;
            } case 33: { //mult by acc
                acc *= ram[address];
                if(acc > 9999) {
                    cerr << RED << "Error: Accumulator overflow - thrown from [" 
                                   << ip << "] -> " << ram[ip] << RESET << endl;
                    quit = true;
                } else if(acc < -9999) {
                    cerr << RED << "Error: Accumulator overflow - thrown from [" 
                                   << ip << "] -> " << ram[ip] << RESET << endl;
                    quit = true;
                }
                break;
            } case 40: { //branch
                ip = address-1; //minus 1 because of increment later
                break;
            } case 41: { //branch if negative
                if(acc < 0) {
                    ip = address-1; //minus 1 because of increment later
                }
                break;
            } case 42: { //branch if zero
                if(acc == 0) {
                    ip = address-1; //minus 1 because of increment later
                }
                break;
            } case 43: { //halt
                quit = true;
                break;
            } case 00: { //NOP
                break;
            } default: {
                cerr << RED << "Error: Unknown opcode - thrown from [" << ip 
                                         << "] -> " << ram[ip] << RESET << endl;
                quit = true;
                break;
            }
        }
        if(debug) {
            cout << dump();
        }
        ip++;
    }
}

/**
 * Dumps memory into readable format
 * @return Returns string containing 10 x 10 array of memory values
 */
string cpu::dump() const {
    stringstream output;
    output << "=====\nMemory Dump from [" << ip << "] -> " << ram[ip]
                                    << "; acc = " << acc << "\n";
    for(int i = 0; i < ram.size(); i++) {
        if((i + 1) % 10 == 0)
            output << ram[i] << " \n";
        else
            output << ram[i] << " \t";
    }
    output << "=====\n";
    return output.str();
}

/**
 * Does stoi but manually
 * @param str String to be parsed to int
 * @return Returns string as an int
 * @throws Throws out_of_range if number is too big or small
 * @throws Throws invalid_argument if str does not have valid number
 */
int cpu::manual_stoi(string str)
{
    bool negative = false; //true if str starts with negative sign
    int value = 0; //value parsed
    bool first = true; //true if first instance
    for(char i : str)
    {
        if(first && str[0] == '-') 
        {
            negative = false;
        }
        else 
        {
            int digit = ((int)i) - 48; //Subtract 30 hex to be 0 - 10 if number
            if(digit >= 0 && digit < 10) 
            {
                if(value > INT_MAX / 10) //multiplying by 10 will overflow
                    throw out_of_range("Number too big");
                value *= 10; //go up by power of 10
                
                if(value > INT_MAX - digit) //adding digit will overflow
                    throw out_of_range("Number too big");
                value += digit; //add digit
            } 
            else
            {
                throw invalid_argument("Invalid character " + i);
            }
        }
        first = false;
    }
    if(negative)
        value = -value;
    return value;
}

/**
 * Makes string representation of string with a colorful sheep
 * @param str string to be outputted
 * @return returns string with sheep saying the string
 */
string cpu::sheepout(string str) {
    int size = str.length();
    stringstream ret;
    ret << "  "; for(int i = 0; i <= size + 1; i++) {ret << "_";}
    ret << "\n < " << str << " >\n  ";
    for(int i = 0; i <= size + 1; i++) {ret << "-";}
    ret << "\n    \\\n     \\  __\n       UooU\\.'" 
         << RED << "@@@@@@" << RESET << "`.\n       \\__/("
         << "\u001B[32;1m@@@@@@@@@@" << RESET << ")\n            ("
         << "\u001B[33;1m@@@@@@@@" << RESET << ")\n            `YY"
         << "\u001B[34;1m~~~~" << RESET << "YY'\n             ||   "
         << " ||\n"; //Don't hate me - it's intentionally obfuscated
    // Thanks to cowsay sheep.cow file for the design
    return ret.str();
}

/**
 * Makes string representation of string with a colorful sheep
 * @param num number to be displayed
 * @return returns string with sheep saying the string
 */
string cpu::sheepout(int num) {
    return cpu::sheepout(to_string(num));
}