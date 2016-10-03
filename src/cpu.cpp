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
    
}

string cpu::dump() {
    stringstream output;
    for(int i = 0; i < ram.size(); i++) {
        output << ram[i];
        if(i % 10)
            output << endl;
        else
            output << "\t";
        return output.str();
    }
}