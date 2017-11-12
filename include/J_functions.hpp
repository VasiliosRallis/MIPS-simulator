#ifndef J_TYPE
#define J_TYPE

#include <iostream>
#include "mips.hpp"
#include <cstdint>
using namespace std;

void j_type(State& mips_state);


void j(State& mips_state, int32_t address);
void jal(State& mips_state, int32_t address);

#endif
