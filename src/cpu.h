/* 
 * Header for virtual CPU class
 * File:   cpu.h
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <array>

using namespace std;

class cpu {
public:
    explicit cpu(istream*); //passes stream containing machine code
    virtual ~cpu(); //default destructor
    void load_mem(istream*); //loads RAM from ifstream
    void loop(); //main loop which executes until halting
    string dump(); //dumps all memory
private:
    array<int, 100> ram;
    unsigned int ip, //instruction pointer
                 sp; //stack pointer
    int acc, //accumulator
        ir; //instruction register
};

#endif /* CPU_H */

