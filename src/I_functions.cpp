#include "I_type.hpp"
using namespace std;

bool i_type(int32_t& instr, State& mips_state) {
	unsigned long index = source2_field >> 16;
	int32_t source2_field = (instr & (0x001F0000)); //rt
	int32_t source1_field = (instr & (0x03E00000)); //rs
	int32_t opcode_field = (instr & (0xFC000000)); //op


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


int32_t addi(State& mips_state,uint32_t source1_field,uint32_t source2_field,int32_t SignExtImm,bool& overflow){
	int32_t rs = mips_state.reg[source1_field];
	int32_t rt = mips_state.reg[source2_field];
	
	
