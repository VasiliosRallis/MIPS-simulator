#ifndef J_TYPE
#define J_TYPE
#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <stdint.h>
using namespace std;

void j_type(int32_t& instr, State& mips_state);


void j(State& mips_state, int32_t& address_field);
void jal(State& mips_state, int32_t& address_field);

#endif
