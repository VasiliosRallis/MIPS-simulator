#ifndef R_TYPE
#define R_TYPE
#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <stdint.h>
using namespace std;


<<<<<<< HEAD
bool r_type(bitset<32>& instr,State& mips_state,bool overflow);


bitset<32> add(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field, bool overflow);
=======
void r_type(bitset<32>& instr,State& mips_state);


bitset<32> add(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
bitset<32> addu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> And(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
void jr(State& mips_state,bitset<32>& source1_field);
bitset<32> nor(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> Or(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bool slt(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bool sltu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
bitset<32> sll(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);
bitset<32> srl(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);
<<<<<<< HEAD
bitset<32> sub(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field, bool overflow);
=======
bitset<32> sub(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
bitset<32> subu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field);
void div(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void divu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void mfhi(State& mips_state,bitset<32>& dest_field);
void mflo(State& mips_state,bitset<32>& dest_field);
void mult(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
void multu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field);
bitset<32> sra(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field);
<<<<<<< HEAD
void mfc0(State& mips_state,bitset<32> source1_field);
=======
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f

#endif
