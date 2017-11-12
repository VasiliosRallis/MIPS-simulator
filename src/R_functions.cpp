#include "R_functions.hpp"
using namespace std;

bool r_type(State& mips_state){
	int32_t instr = mips_state.ram[mips_state.pc];
	uint32_t funct_field = instr & 0x0000003F;
	uint32_t shamt_field = (instr & 0x000007C0) >> 6;
	uint32_t index = (instr & 0x0000F800) >> 11; //rd
	uint32_t source2_field = (instr & 0x001F0000) >> 16; //rt
	uint32_t source1_field = (instr & 0x03E00000) >> 21; //rs
	bool overflow = false;
	
	if(funct_field == (0x00000020)){
			int32_t temp = add(mips_state, source1_field, source2_field, overflow); //can change overflow
			if(overflow) {
				std::exit(static_cast<int>(Exception::ARITHMETIC));
			}
			else {
				mips_state.reg[index] = temp;
			}
	}
	else if(funct_field == 0x00000021)
			mips_state.reg[index] = addu(mips_state, source1_field, source2_field);
	else if(funct_field == 0x00000024)
			mips_state.reg[index] = And(mips_state, source1_field, source2_field);
	else if(funct_field == 0x00000008)
			jr(mips_state,source1_field);
	else if(funct_field == 0x00000027)
			mips_state.reg[index] = nor(mips_state, source1_field, source2_field);
	else if(funct_field == 0x00000025)
			mips_state.reg[index] = Or(mips_state, source1_field, source2_field);
	else if(funct_field == 0x0000002A)
			mips_state.reg[index] = slt(mips_state, source1_field, source2_field);
	else if(funct_field == 0x0000002B)
			mips_state.reg[index] = sltu(mips_state, source1_field, source2_field);
	else if(funct_field == 0x00000000)
			mips_state.reg[index] = sll(mips_state, source2_field, shamt_field);
	else if(funct_field == 0x00000002)
			mips_state.reg[index] = srl(mips_state, source2_field, shamt_field);
	else if(funct_field == 0x00000022){
			int32_t temp = sub(mips_state, source1_field, source2_field, overflow); //can change overflow
			if(overflow) {
				std::exit(static_cast<int>(Exception::ARITHMETIC));
			}
			else{
				mips_state.reg[index] = temp;
			}
	}
	else if(funct_field == 0x00000023)
			mips_state.reg[index] = subu(mips_state, source1_field, source2_field);
	else if(funct_field == 0x0000001A)
			div(mips_state, source2_field, source1_field);
	else if(funct_field == 0x0000001B)
			divu(mips_state, source2_field, source1_field);
	else if(funct_field == 0x00000010)
			mfhi(mips_state, index);
	else if(funct_field == 0x00000012)
			mflo(mips_state, index);
	else if(funct_field == 0x00000018)
			mult(mips_state, source2_field, source1_field);
	else if(funct_field == 0x00000019)
			multu(mips_state, source2_field, source1_field);
	else if(funct_field == 0x00000003)
			mips_state.reg[index] = sra(mips_state, source2_field, shamt_field);
	else if(funct_field == 0x00000011)
			mthi(mips_state,source1_field);
	else if(funct_field == 0x00000013)
			mtlo(mips_state,source1_field);
	else if(funct_field == 0x00000004)
			mips_state.reg[index] = sllv(mips_state,source2_field,source1_field);
	else if(funct_field == 0x00000007)
			mips_state.reg[index] = srav(mips_state,source2_field,source1_field);
	else if(funct_field == 0x00000006){
			mips_state.reg[index] = srlv(mips_state,source2_field,source1_field);
	}

return false;
	}

int32_t add(State& mips_state, uint32_t source1_field, uint32_t source2_field, bool& overflow){
	 int32_t rs = mips_state.reg[source1_field];
	 int32_t rt = mips_state.reg[source2_field];
	 if (((rs<0)&&(rt<0)&&(rs+rt>0)) || ((rs>0)&&(rt>0)&&(rs+rt<0))){
		overflow = true;
	}
	else {
		overflow = false;
		return  rs + rt;
	}
}


uint32_t addu(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	uint32_t  rs = mips_state.reg[source1_field];
	uint32_t  rt = mips_state.reg[source2_field];
	return  rs+rt ;
}

int32_t And(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	return mips_state.reg[source1_field] & mips_state.reg[source2_field];
}

void jr(State& mips_state, uint32_t source1_field){
	if(mips_state.reg[source1_field] % 4 != 0){
		return; //Exception Call
	}
	else{
		mips_state.pc = mips_state.reg[source1_field] / 4;
	}
}

int32_t nor(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	return ~(mips_state.reg[source1_field] | mips_state.reg[source2_field]);
}

int32_t Or(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	return (mips_state.reg[source1_field] | mips_state.reg[source2_field]);
}

bool slt(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	if( (rs - rt) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool sltu(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	if(rs < rt) {
		return true;
	}
	else {
		return false;
	}
}

int32_t sll(State& mips_state, uint32_t source2_field, uint32_t shamt_field){
	return (mips_state.reg[source2_field] << shamt_field);
}

int32_t srl(State& mips_state, uint32_t source2_field, uint32_t shamt_field){
	uint32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}

int32_t sub(State& mips_state, uint32_t source1_field, uint32_t source2_field, bool& overflow){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	if(((rs-rt) < rs) != (rt > 0)){
		overflow = true;
	}
	else {
		overflow = false;
	}
	return  rs-rt;
}

uint32_t subu(State& mips_state, uint32_t source1_field, uint32_t source2_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	return  rs - rt ;
}

void div(State& mips_state, uint32_t source2_field, uint32_t source1_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void divu(State& mips_state, uint32_t source2_field, uint32_t source1_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void mfhi(State& mips_state, uint32_t index){
	mips_state.reg[index] = mips_state.Hi;
}

void mflo(State& mips_state, uint32_t index){
	mips_state.reg[index] = mips_state.Lo;
}

void mult(State& mips_state, uint32_t source2_field, uint32_t source1_field){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	int64_t result  = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void multu(State& mips_state, uint32_t source2_field, uint32_t source1_field){
	uint32_t rs = mips_state.reg[source1_field];
	uint32_t rt = mips_state.reg[source2_field];
	uint64_t result = rs * rt;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

int32_t sra(State& mips_state, uint32_t source2_field, uint32_t shamt_field){
	int32_t result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}

void mthi(State& mips_state,uint32_t source1_field){
	mips_state.Hi = mips_state.reg[source1_field];
}

void mtlo(State& mips_state,uint32_t source1_field){
	mips_state.Lo = mips_state.reg[source1_field];
}

int32_t sllv(State& mips_state,uint32_t source2_field,uint32_t source1_field){
	return (mips_state.reg[source2_field] << (uint32_t)mips_state.reg[source1_field]);
}

int32_t srav(State& mips_state,uint32_t source2_field,uint32_t source1_field){
	return (mips_state.reg[source2_field] >> (uint32_t)mips_state.reg[source1_field]);
}

uint32_t srlv(State& mips_state,uint32_t source2_field,uint32_t source1_field){
	uint32_t temp = mips_state.reg[source2_field];
	return temp >> (uint32_t)mips_state.reg[source1_field];
}
