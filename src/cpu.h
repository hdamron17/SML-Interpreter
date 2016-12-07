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
    explicit cpu(istream*, bool); //passes code stream and "sheeped" boolean
    virtual ~cpu(); //default destructor
    void load_mem(istream*); //loads RAM from ifstream
    void run(); //main loop which executes until halting
    void run(bool); //main loop which executes until halting
    string dump() const; //dumps all memory
    static int manual_stoi(string); //manual stoi
    static string sheepout(string); //sheep output
    static string sheepout(int); //sheep output
private:
    array<int, 100> ram;
    unsigned int ip, //instruction pointer
                 sp; //stack pointer
    int acc, //accumulator
        ir; //instruction register
    bool sheeped; //boolean for if program is sheeped
};

#endif /* CPU_H */

