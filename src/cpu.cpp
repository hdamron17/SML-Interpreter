/* 
 * Virtual CPU for interpreting simple machine language (SML)
 * File:   cpu.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#include <fstream>
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
    char c[5];
    while(file->get(c, 9000)) {
        cout << c << endl;
    }
}

void cpu::loop() {
    
}