#include "J_functions.hpp"
using namespace std;


void j_type(int32_t& instr, State& mips_state){
	int32_t address_field = (instr & int32_t(0x03FFFFFF)); //address
	int32_t opcode_field = (instr & int32_t(0xFC000000)); //op

	if(opcode_field == int32_t(0x00000002))
		j(mips_state, address_field);
	else if(opcode_field == int32_t(0x00000002))
		jal(mips_state, address_field);
	else
		return;
}


void j(State& mips_state, int32_t address_field){
	mips_state.pc = address_field;
}

void jal(State& mips_state, int32_t address_field){
	mips_state.reg[31] = (mips_state.pc) + 8;
	mips_state.pc = address_field;
}
