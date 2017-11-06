#ifndef R_TYPE
#define R_TYPE
#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <stdint.h>
using namespace std;


void r_type(bitset<32>& instr,State& mips_state);


bitset<32> add(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> addu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> And(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
void jr(State& mips_state,bitset<32>& source1_field);
bitset<32> nor(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> Or(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bool slt(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bool sltu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> sll(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);
bitset<32> srl(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);
bitset<32> sub(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> subu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
void div(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void divu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void mfhi(State& mips_state,bitset<32>& dest_field);
void mflo(State& mips_state,bitset<32>& dest_field);
void mult(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void multu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
bitset<32> sra(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);

#endif
