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
    short opcode;
    size_t index = 0;
    (*file) >> stringop;
    while(!(*file).eof()) {
        opcode = short(stoi(stringop));
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
    while(true) { //HAHAHA
        break;
    }
}

string cpu::dump() {
    stringstream output;
    for(int i = 0; i < ram.size(); i++) {
        if((i + 1) % 10 == 0)
            output << ram[i] << endl;
        else
            output << ram[i] << "\t";
    }
    return output.str();
}