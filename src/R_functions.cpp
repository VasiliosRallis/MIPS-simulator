#include "R_functions.hpp"
using namespace std;

void r_type(bitset<26>& instr, State& mips_state) {
	bitset<6> funct_field = (instr & 0x3F);
	bitset<5> shamt_field = (instr & 0x7C0);
	bitset<5> dest_field = (instr & 0xF800); //rd
	bitset<5> source2_field = (instr & 0x1F0000); //rt
	bitset<5> source1_field = (instr & 0x3E00000); //rs
	
	switch (funct_field) {
		
		case '0x20':
			mips_state.reg[dest_field] = add(mips_state,source1_field,source2_field);
		case '0x21':
			mips_state.reg[dest_field] = addu(mips_state,source1_field,source2_field);
		case '0x24':
			mips_state.reg[dest_field] = And(mips_state,source1_field,source2_field);
		case '0x8':
			jr(mips_state,source1_field);
		case '0x27':
			mips_state.reg[dest_field] = nor(mips_state,source1_field,source2_field);
		case '0x25':
			mips_state.reg[dest_field] = Or(mips_state,source1_field,source2_field);
		case '0x2A':
			mips_state.reg[dest_field] = slt(mips_state,source1_field,source2_field);
		case '0x2B':
			mips_state.reg[dest_field] = sltu(mips_state,source1_field,source2_field);
		case '0x0':
			mips_state.reg[dest_field] = sll(mips_state,source2_field,shamt_field);
		case '0x2':
			mips_state.reg[dest_field] = srl(mips_state,source2_field,shamt_field);
		case '0x22':
			mips_state.reg[dest_field] = sub(mips_state,source1_field,source2_field);
		case '0x23':
			mips_state.reg[dest_field] = subu(mips_state,source1_field,source2_field);
		case '0x1A':
			div(mips_state,source2_field,source1_field);
		case '0x1B':
			divu(mips_state,source2_field,source1_field);
		case '0x10':
			mfhi(mips_state,dest_field);
		case '0x12':
			mflo(mips_state,dest_field);
		case '0x18':
			mult(mips_state,source2_field,source1_field);
		case '0x19':
			multu(mips_state,source2_field,source1_field);
		case '0x3':
			mips_state.reg[dest_field] = sra(mips_state,source2_field,shamt_field);
		default:
			return; //this should be changed to the appropriate error code
	}
}

int32_t add(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	signed int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field]
	return  rs+rt ;
}

uint32_t addu(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	unsigned int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field]
	return  rs+rt ;
}

bitset<32> And(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	return mips_state.reg[source1_field] & mips_state.reg[source2_field];
}

void jr(State& mips_state,bitset<5>& source1_field){
	mips_state.pc = mips_state.reg[source1_field];
}

bitset<32> nor(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	return ~(mips_state.reg[source1_field] | mips_state.reg[source2_field])
}

bitset<32> Or(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	return (mips_state.reg[source1_field] | mips_state.reg[source2_field])
}

bool slt(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	signed int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	if(rs - rt < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bool sltu(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	unsigned int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	if(rs - rt < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bitset<32> sll(State& mips_state,bitset<5>& source2_field,bitset<5> shamt_field){
	return (mips_state.reg[source2_field] << shamt_field);
}

bitset<32> srl(State& mips_state,bitset<5>& source2_field,bitset<5> shamt_field){
	unsigned int32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}

int32_t sub(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	signed int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field]
	return  rs-rt ;
}

uint32_t subu(State& mips_state,bitset<5>& source1_field,bitset<5>& source2_field){
	unsigned int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field]
	return  rs-rt ;
}

void div(State& mips_state,bitset<5>& source2_field,bitset<5>& source1_field){
	signed int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void divu(State& mips_state,bitset<5>& source2_field,bitset<5>& source1_field){
	unsigned int32_t rs,rt;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void mfhi(State& mips_state,bitset<5>& dest_field){
	mips_state.reg[dest_field] = mips_state.Hi;
}

void mflo(State& mips_state,bitset<5>& dest_field){
	mips_state.reg[dest_field] = mips_state.Lo;
}

void mult(State& mips_state,bitset<5>& source2_field,bitset<5>& source1_field){
	signed int32_t rs,rt;
	signed int64_t result;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	result = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void multu(State& mips_state,bitset<5>& source2_field,bitset<5>& source1_field){
	unsigned int32_t rs,rt;
	unsigned int64_t result;
	rs = mips_state.reg[source1_field];
	rt = mips_state.reg[source2_field];
	result = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

bitset<32> sra(State& mips_state,bitset<5>& source2_field,bitset<5> shamt_field){
	signed int32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}
