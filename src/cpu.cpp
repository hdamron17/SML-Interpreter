/* 
 * Virtual CPU for interpreting simple machine language (SML)
 * File:   cpu.cpp
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#include <fstream>
#include "cpu.h"

/**
 * Constructor from stream containing "machine code"
 * @param file input file stream containing "machine code"
 */
cpu::cpu(ifstream file) {
    
}

/**
 * Default destructor
 */
cpu::~cpu() {
}

struct byte {
    bool sign; //true = positive; false = negative
    unsigned char data; //8 bit unsigned value (will have mav_value = 99)
};