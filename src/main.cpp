#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <cstdint>
#include "error.hpp"
//#include "I_functions.hpp"
#include "J_functions.hpp"
#include "R_functions.hpp"

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

	//Passes the instructions to the
	setUp(mips_state, fileName);

	mips_state.ram[ADDR_INSTR] = 0x08000000;

	bool overflow;
	do{
		checkExec(mips_state.reg, mips_state.pc);
		mips_state.reg[0] = 0;

		int32_t s = mips_state.ram[mips_state.pc] >> 26;
		s = s & 0x0000003F;

		if(s == 0x00000000){
			overflow = r_type(mips_state);
		}
		else if(s == 0x00000020 || s == 0x00000021 || s == 0x00000022 || s == 0x00000023 || s == 0x00000024 ||
				s == 0x00000025 || s == 0x00000026 || s == 0x00000028 || s == 0x00000029 || s == 0x0000002B ||
				s == 0x00000008 || s == 0x00000009 || s == 0x0000000A || s == 0x0000000B || s == 0x0000000C ||
				s == 0x0000000D || s == 0x0000000E || s == 0x0000000F || s == 0x00000001 || s == 0x00000004 ||
				s == 0x00000005 || s == 0x00000006 || s == 0x00000007){
			//overflow = i_type(mips_state);
		}
		else if(s == 0x00000002 || s == 0x00000003){
			j_type(mips_state);
		}
		else{
			//Invalid Instruction
			std::exit(-12);

		}
	}while(1);

	return 0;
}
