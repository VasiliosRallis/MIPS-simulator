#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <cstdint>
#include "error.hpp"
#include "J_functions.hpp"
#include "R_functions.hpp"
#include "I_functions.hpp"

using namespace std;

int main(int argc, char* argv[]){

	if(argc != 2){
		std::cerr << "Error: Expected a Binary file a input" << std::endl;
		exit(1);
	}

	string fileName = argv[1];

	State mips_state;

	//This will allocate memory for the whole RAM
	//I used hex so that it is easier to relate to the Specification on GitHub
	mips_state.ram.resize(MEM_SIZE);

	//Passes the instructions to the vector
	setUp(mips_state, fileName);

	do{
		checkExec(mips_state.reg, mips_state.pc);
		mips_state.reg[0] = 0;

		//Since the instruction that will be executed will change the npc we need to store it somewhere
		int32_t tempNPC = mips_state.npc;

		int32_t opcode = mips_state.ram[mips_state.pc] >> 26;
		opcode = opcode & 0x0000003F;

		if(opcode == 0x00000000){
			r_type(mips_state);
		}
		else if(opcode == 0x00000020 || opcode == 0x00000021 || opcode == 0x00000022 || opcode == 0x00000023 || opcode == 0x00000024 ||
				opcode == 0x00000025 || opcode == 0x00000026 || opcode == 0x00000028 || opcode == 0x00000029 || opcode == 0x0000002B ||
				opcode == 0x00000008 || opcode == 0x00000009 || opcode == 0x0000000A || opcode == 0x0000000B || opcode == 0x0000000C ||
				opcode == 0x0000000D || opcode == 0x0000000E || opcode == 0x0000000F || opcode == 0x00000001 || opcode == 0x00000004 ||
				opcode == 0x00000005 || opcode == 0x00000006 || opcode == 0x00000007){
			i_type(mips_state);
		}
		else if(opcode == 0x00000002 || opcode == 0x00000003){
			j_type(mips_state);
		}
		else{
			std::exit(static_cast<int>(Exception::INSTRUCTION));

		}

		//Set the value of pc(the address of the next instruction that we are going to execute) to the
		//original value of npc
		mips_state.pc = tempNPC;


	}while(1);

	return 0;
}

