/* 
 * Header for virtual CPU class
 * File:   cpu.h
 * Author: Hunter Damron
 * Created on September 28, 2016, 10:25 AM
 */

#ifndef CPU_H
#define CPU_H

#include <fstream>

using namespace std;

class cpu {
public:
    cpu(); //default constructor
    cpu(ifstream); //passes stream containing 
    virtual ~cpu(); //default destructor
private:
    

};

#endif /* CPU_H */

