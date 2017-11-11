#include "I_functions.hpp"
#include <cmath>
using namespace std;

bool i_type(State& mips_state){
	uint32_t instr = mips_state.pc;
	uint32_t source2_field = (instr & (0x001F0000)); //rt
	uint32_t index = source2_field >> 16;
	uint32_t source1_field = (instr & (0x03E00000)); //rs
	uint32_t opcode_field = (instr & (0xFC000000)); //op
	int32_t SignExtImm = instr & 0x0000FFFF; //immediate

	if(SingExtImm >> 15){
		SingExtImm = SingExtImm | 0xFFFF0000;
	}
	else{
		//Do nothing
	}


	if(opcode_field == (0x00000008))
		mips_state.reg[index] = addi(mips_state,source1_field,source2_field,SignExtImm,overflow);
	else if(opcode_field == (0x00000009))
		mips_state.reg[index] = addiu(mips_state,source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x0000000C))
		mips_state.reg[index] = andi(mips_state,source1_field,source2_field,ZeroExtImm);
	else if(opcode_field == (0x00000004))
		beq(source1_field,source2_field,BranchAddr);
	else if(opcode_field == (0x00000005))
		bne(source1_field,source2_field,BranchAddr);
	else if(opcode_field == (0x00000024))
		lbu(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000020)
		lb(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000025)
		lhu(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000021)
		lh(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x0000000F)
		lui(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000023)
		lw(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000022)
		lwl(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000026)
		lwr(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000028)
		sb(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x00000029)
		sh(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x0000002B)
		sw(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x0000000A)
		mips_state.reg[index] = slti(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x0000000B)
		mips_state.reg[index] = sltiu(source1_field,source2_field,SignExtImm);
	else if(opcode_field == (0x000000E)
		mips_state.reg[index] = xori(source1_field,source2_field,ZeroExtImm);
	else if(opcode_field == (0x0000000D)
		mips_state.reg[index] = ori(source1_field,source2_field,ZeroExtImm);
	else
		return;
}


int32_t addi(State& mips_state, uint32_t source1_field, uint32_t source2_field, int32_t SignExtImm, bool& overflow){
	int32_t rs = mips_state.reg[source1_field];
	if((SignExtImm >> 15) == 1) {
		SignExtImm = SignExtImm | (0xFFFF0000);
	}
	else {
		SignExtImm = SignExtImm & (0x0000FFFF);
	}
	int32_t temp = rs + SignExtImm;
	if (((rs<0)&&(SignExtImm<0)&&(rs+SignExtImm>0)) || ((rs>0)&&(SignExtImm>0)&&(rs+SignExtImm<0))){
		overflow = true;
	}
	else {
		overflow = false;
		return temp;
	}

uint32_t addiu(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm){
	int32_t rs = mips_state.reg[source1_field];
	if((SignExtImm >> 15) == 1) {
		SignExtImm = SignExtImm | (0xFFFF0000);
	}
	else {
		SignExtImm = SignExtImm & (0x0000FFFF);
	}
	return rs + SignExtImm;
	
int32_t Andi(State& mips_state,uint32_t source1_field, uint32_t ZeroExtImm){
	ZeroExtImm = ZeroExtImm & (0x0000FFFF);
	return mips_state.reg[source1_field] & ZeroExtImm;
}

void beq(State& mips_state,uint32_t source1_field,uint32_t source2_field,uint32_t offset){
	int32_t tgt_offset = offset << 2;
	if(mips_state.reg[source1_field] == mips_state.reg[source2_field]){
		mips_state.pc += tgt_offset;
		return;
	}
	else{
		return;
	}
}

void bne(State& mips_state,uint32_t source1_field,uint32_t source2_field,uint32_t offset){
	int32_t tgt_offset = offset << 2; //allign to be multiple of 4
	if(mips_state.reg[source1_field] != mips_state.reg[source2_field]){
		mips_state.pc += tgt_offset;
		return;
	}
	else{
		return;
	}
}

void lbu(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm){
	SignExtImm = SignExtImm & (0x0000FFFF);
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 4 != 0){
		uint32_t multiple = abs(Addr) - (abs(Addr) % 4);
		uint32_t temp_storage = mips_state.ram[multiple];
		temp_storage = temp_storage << pow(8,abs(Addr) % 4);
		temp_storage = temp_storage >> pow(8,4-(abs(Addr) % 4));
		mips_state.reg[source2_field] =  (0x000000FF) & temp_storage;
	}
	else{
		mips_state.reg[source2_field] = (0x000000FF) & mips_state.ram[multiple] >> 24;
	}
	return;
}

void lb(State& mips_state, uint32_t source1_field, uint32_t source2_field, int32_t SignExtImm){
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 4 != 0){
		uint32_t multiple = abs(Addr) - (abs(Addr) % 4);
		uint32_t temp_storage = mips_state.ram[multiple];
		temp_storage = temp_storage << pow(8,abs(Addr) % 4);
		temp_storage = temp_storage >> pow(8,4-(abs(Addr) % 4));
		if(temp_storage & 0x00000080){
		mips_state.reg[source2_field] =  (0xFFFFFF00) | temp_storage;
		}
		else if (!(temp_storage & 0x00000080)){
		mips_state.reg[source2_field] =  (0x00000000) | temp_storage;
		}
	}
	else{	
		uint32_t temp_storage = mips_state.ram[Addr] >> 24; 
		if(temp_storage & 0x00000080){
		mips_state.reg[source2_field] =  (0xFFFFFF00) | temp_storage;
		}
		else if (!(temp_storage & 0x00000080)){
		mips_state.reg[source2_field] =  (0x000000FF) & temp_storage;
		}
	}
	return;
}

void lhu(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm){
	SignExtImm = SignExtImm & (0x0000FFFF);
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 2 != 0){
		uint32_t multiple = abs(Addr) - (abs(Addr) % 2);
		uint32_t temp_storage = mips_state.ram[multiple];
		temp_storage = temp_storage << pow(16,abs(Addr) % 2);
		temp_storage = temp_storage >> pow(16,2-(abs(Addr) % 2));
		temp_storage = temp_storage & 0x0000FFFF;
		mips_state.reg[source2_field] = temp_storage;
		return;
	}
	else{	
		uint32_t temp_storage = mips_state.ram[Addr] >> 16;
		temp_storage = temp_storage & 0x0000FFFF;
		mips_state.reg[source2_field] = temp_storage;
		return;
	}
}
	
void lh(State& mips_state,uint32_t source1_field,int32_t SignExtImm){
	SignExtImm = SignExtImm & (0x0000FFFF);
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 2 != 0){
		uint32_t multiple = abs(Addr) - (abs(Addr) % 2);
		uint32_t temp_storage = mips_state.ram[multiple];
		temp_storage = temp_storage << pow(16,abs(Addr) % 2);
		temp_storage = temp_storage >> pow(16,2-(abs(Addr) % 2));
		if(temp_storage & 0x00008000){
		mips_state.reg[source2_field] =  (0xFFFF0000) | temp_storage;
		}
		else if (!(temp_storage & 0x00008000)){
		mips_state.reg[source2_field] =  (0x0000FFFF) & temp_storage;
		}
	}
	else{	
		uint32_t temp_storage = mips_state.ram[Addr] >> 24; 
		if(temp_storage & 0x00008000){
		mips_state.reg[source2_field] =  (0xFFFF0000) | temp_storage;
		}
		else if (!(temp_storage & 0x00008000)){
		mips_state.reg[source2_field] =  (0x0000FFFF) & temp_storage;
		}
	}
	return;
}

void lui(State& mips_state,uint32_t source2_field,int32_t SignExtImm){
	SignExtImm = SignExtImm << 16;
	mips_state.reg[source2_field] = SignExtImm & (0xFFFF0000);
}

void lw(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm){
	SignExtImm = SignExtImm & (0x0000FFFF);
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 4 != 0){
		return; //Exception : Address not aligned (we should make an ExceptionHandler() function) which takes input parameter the opcode of
			//the instruction that went bad and return the appropriate error code
	}
	else {
		mips_state.reg[source2_field] = mips_state.ram[Addr];
		return;
	}
}

void lwl(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm){
	SignExtImm = SignExtImm & (0x0000FFFF);
	uint32_t Addr = SignExtImm + mips_state.reg[source1_field];
	if(Addr % 4 != 0){
		uint32_t multiple = abs(Addr) - (abs(Addr) % 4);
		uint32_t temp_storage = mips_state.ram[multiple];
		temp_storage = temp_storage << pow(8,abs(Addr) % 4);
		temp_storage = temp_storage >> pow(8,4-(abs(Addr) % 4));
		if(temp_storage & 0x00000080){
		mips_state.reg[source2_field] =  (0xFFFFFF00) | temp_storage;
		}
		else if (!(temp_storage & 0x00000080)){
		mips_state.reg[source2_field] =  (0x00000000) | temp_storage;
		}
	}
	else{	
		uint32_t temp_storage = mips_state.ram[Addr] >> 24; 
		if(temp_storage & 0x00000080){
		mips_state.reg[source2_field] =  (0xFFFFFF00) | temp_storage;
		}
		else if (!(temp_storage & 0x00000080)){
		mips_state.reg[source2_field] =  (0x000000FF) & temp_storage;
		}
	}
	return;
}
	
