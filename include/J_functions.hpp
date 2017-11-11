#ifndef J_TYPE
#define J_TYPE
#include <iostream>
#include "mips.hpp"
#include <stdint.h>
using namespace std;

void j_type(State& mips_state);


void j(State& mips_state, int32_t address_field);
void jal(State& mips_state, int32_t address_field);

#endif
