#include "J_functions.hpp"
using namespace std;


void j_type(bitset<32>& instr, State& mips_state){
	bitset<32> address_field = (instr & bitset<32>(0x03FFFFFF)); //address
	bitset<32> opcode_field = (instr & bitset<32>(0xFC000000)); //op

	if(opcode_field == bitset<32>(0x00000002))
		j(mips_state, address_field);
	else if(opcode_field == bitset<32>(0x00000002))
		jal(mips_state, address_field);
	else
		return;
}


void j(State& mips_state, bitset<32>& address_field){
	mips_state.pc = address_field.to_ulong();
}

void jal(State& mips_state, bitset<32>& address_field){
	mips_state.reg[31] = (mips_state.pc).to_ulong() + 8;
	mips_state.pc = address_field.to_ulong();
}
