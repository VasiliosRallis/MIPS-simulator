#ifndef R_TYPE
#define R_TYPE
#include <iostream>
#include "mips.hpp"
#include <stdint.h>
using namespace std;


bool r_type(State& mips_state);


int32_t add(State& mips_state, uint32_t source1_field, uint32_t source2_field, bool& overflow);
uint32_t addu(State& mips_state,uint32_t source1_field,uint32_t source2_field);
int32_t And(State& mips_state,uint32_t source1_field,uint32_t source2_field);
void jr(State& mips_state,uint32_t source1_field);
int32_t nor(State& mips_state,uint32_t source1_field,uint32_t source2_field);
int32_t Or(State& mips_state,uint32_t source1_field,uint32_t source2_field);
bool slt(State& mips_state,uint32_t source1_field,uint32_t source2_field);
bool sltu(State& mips_state,uint32_t source1_field,uint32_t source2_field);
int32_t sll(State& mips_state,uint32_t source2_field,uint32_t shamt_field);
int32_t srl(State& mips_state, uint32_t source2_field, uint32_t shamt_field);
int32_t sub(State& mips_state,uint32_t source1_field,uint32_t source2_field, bool& overflow);
uint32_t subu(State& mips_state,uint32_t source1_field,uint32_t source2_field);
void div(State& mips_state,uint32_t source2_field,uint32_t source1_field);
void divu(State& mips_state,uint32_t source2_field,uint32_t source1_field);
void mfhi(State& mips_state,uint32_t dest_field);
void mflo(State& mips_state,uint32_t dest_field);
void mult(State& mips_state,uint32_t source2_field,uint32_t source1_field);
void multu(State& mips_state,uint32_t source2_field,uint32_t source1_field);
int32_t sra(State& mips_state,uint32_t source2_field,uint32_t shamt_field);

#endif
