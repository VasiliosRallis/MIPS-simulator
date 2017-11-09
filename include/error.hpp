#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <cstdlib> //for std::exit
#include <cstdint>
#include "setUp.hpp"

//This header file will include all the functions we need for error checking

//These "check" functions take as input the address you want to verify that
//you have the specific rights to and if you do not it will exit with the 
//memory exception code (-11)

void checkWrite(int32_t addr);
void checkRead(int32_t addr);
void checkExec(int32_t addr);

#endif
