#include "R_functions.hpp"
using namespace std;

bool r_type(int32_t& instr, State& mips_state, bool overflow) {
	int32_t funct_field = (instr & (0x0000003F));
	int32_t shamt_field = (instr & (0x000007C0));
	int32_t dest_field = (instr & (0x0000F800)); //rd
	unsigned long index = dest_field >> 11;
	int32_t source2_field = (instr & (0x001F0000)); //rt
	int32_t source1_field = (instr & (0x03E00000)); //rs
	int32_t opcode_field = (instr & (0xFC000000)); //op
	overflow = false;
	
	if(funct_field == (0x00000020))
			mips_state.reg[index] = add(mips_state,source1_field,source2_field,overflow); //can change overflow
	else if(funct_field == (0x00000021))
			mips_state.reg[index] = addu(mips_state,source1_field,source2_field);
	else if(funct_field == (0x00000024))
			mips_state.reg[index] = And(mips_state,source1_field,source2_field);
	else if(funct_field == (0x00000008))
			jr(mips_state,source1_field);
	else if(funct_field == (0x00000027))
			mips_state.reg[index] = nor(mips_state,source1_field,source2_field);
	else if(funct_field == (0x00000025))
			mips_state.reg[index] = Or(mips_state,source1_field,source2_field);
	else if(funct_field == (0x0000002A))
			mips_state.reg[index] = slt(mips_state,source1_field,source2_field);
	else if(funct_field == (0x0000002B))
			mips_state.reg[index] = sltu(mips_state,source1_field,source2_field);
	else if(funct_field == (0x00000000))
			mips_state.reg[index] = sll(mips_state,source2_field,shamt_field);
	else if(funct_field == (0x00000002))
			mips_state.reg[index] = srl(mips_state,source2_field,shamt_field);
	else if(funct_field == (0x00000022))
			mips_state.reg[index] = sub(mips_state,source1_field,source2_field,overflow); //can change overflow
	else if(funct_field == (0x00000023))
			mips_state.reg[index] = subu(mips_state,source1_field,source2_field);
	else if(funct_field == (0x0000001A))
			div(mips_state,source2_field,source1_field);
	else if(funct_field == (0x0000001B))
			divu(mips_state,source2_field,source1_field);
	else if(funct_field == (0x00000010))
			mfhi(mips_state,dest_field);
	else if(funct_field == (0x00000012))
			mflo(mips_state,dest_field);
	else if(funct_field == (0x00000018))
			mult(mips_state,source2_field,source1_field);
	else if(funct_field == (0x00000019))
			multu(mips_state,source2_field,source1_field);
	else if(funct_field == (0x00000003)){
			mips_state.reg[index] = sra(mips_state,source2_field,shamt_field);
	}
return overflow;
	}

int32_t add(State& mips_state,int32_t& source1_field,int32_t& source2_field, bool& overflow){
	 int32_t rs = mips_state.reg[source1_field];
	 int32_t rt = mips_state.reg[source2_field];
	 int32_t sign1 = (rs >> 31);
	 int32_t sign2 = (rt >> 31);
	 if(~(sign1 ^ sign2) & (((rs + rt >> 31) ^ sign1))){
		overflow = true;
	}
	else {
		overflow = false;
	}
	return  rs + rt;
}


uint32_t addu(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	uint32_t  rs = mips_state.reg[source1_field];
	uint32_t  rt = mips_state.reg[source2_field];
	return  rs+rt ;
}

int32_t And(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	return mips_state.reg[source1_field] & mips_state.reg[source2_field];
}

void jr(State& mips_state,int32_t& source1_field){
	mips_state.pc = mips_state.reg[source1_field];
}

int32_t nor(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	return ~(mips_state.reg[source1_field] | mips_state.reg[source2_field]);
}

int32_t Or(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	return (mips_state.reg[source1_field] | mips_state.reg[source2_field]);
}

bool slt(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	if( (rs - rt) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool sltu(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	if(rs < rt) {
		return true;
	}
	else {
		return false;
	}
}

int32_t sll(State& mips_state,int32_t& source2_field,int32_t shamt_field){
	return (mips_state.reg[source2_field] << shamt_field);
}

uint32_t srl(State& mips_state,int32_t& source2_field,int32_t shamt_field){
	uint32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}

int32_t sub(State& mips_state,int32_t& source1_field,int32_t& source2_field, bool& overflow){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	int32_t sign1 = (rs >> 31);
	int32_t sign2 = (rt >> 31);
	if(~(sign1 ^ sign2) & (((rs - rt) >> 31) ^ sign1)){
		overflow = true;
	}
	else {
		overflow = false;
	}
	return  (int)rs - (int)rt;
}

uint32_t subu(State& mips_state,int32_t& source1_field,int32_t& source2_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	return  rs-rt ;
}

void div(State& mips_state,int32_t& source2_field,int32_t& source1_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void divu(State& mips_state,int32_t& source2_field,int32_t& source1_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void mfhi(State& mips_state,int32_t& dest_field){
	mips_state.reg[dest_field] = mips_state.Hi;
}

void mflo(State& mips_state,int32_t& dest_field){
	mips_state.reg[dest_field] = mips_state.Lo;
}

void mult(State& mips_state,int32_t& source2_field,int32_t& source1_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	int64_t result  = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void multu(State& mips_state,int32_t& source2_field,int32_t& source1_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	uint64_t result = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

int32_t sra(State& mips_state,int32_t& source2_field,int32_t shamt_field){
	int32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}
