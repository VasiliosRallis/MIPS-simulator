#include "J_functions.hpp"
using namespace std;


void j_type(State& mips_state){
	int32_t instr = mips_state.ram[mips_state.pc];
	int32_t address_field = instr & 0x03FFFFFF; //address
	int32_t opcode_field = instr & 0xFC000000; //op
	opcode_field = opcode_field >> 26;

	if(opcode_field == 0x00000002)
		j(mips_state, address_field);
	else if(opcode_field == 0x00000003)
		jal(mips_state, address_field);
	else
		return;
}


void j(State& mips_state, int32_t address_field){
	mips_state.pc = ((mips_state.pc & 0x0F000000) | address_field);
}

void jal(State& mips_state, int32_t address_field){
	mips_state.reg[31] = (mips_state.pc) + 2;
	mips_state.pc = ((mips_state.pc & 0x0F000000) | address_field);
}
