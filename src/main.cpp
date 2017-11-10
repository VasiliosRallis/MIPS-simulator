#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <cstdint>
#include "error.hpp"
#include "R_functions.hpp"

using namespace std;

void i_type(int32_t& instr,State& mips_state); //not implemented yet


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
	std::cout << mips_state.ram.size() << std::endl;

	//Passes the instructions to the
	setUp(mips_state, fileName);

	mips_state.ram[ADDR_INSTR] = 0x20420005;
	mips_state.ram[ADDR_INSTR + 1] = 0x08000000;



	int32_t temp = 0xFFFFFFFF;
	bool overflow;
	

	for(int i = 0; i < (mips_state.ram).size(); i++) {
		switch(temp & 0xFC000000) {
			
			case 0x00000000:{
				int32_t instr = (temp & 0xFC000000);
				r_type(instr,mips_state, overflow);
			}
			case 0x20000000:{
				int32_t instr = (temp & 0xFC000000);
				//i_type(instr,mips_state, overflow);
			}
			case 0x30000000:{
				int32_t instr = (temp & 0xFC000000);
				//i_type(instr,mips_state, overflow);
			}
			default:{
				int32_t instr = (temp & 0xFC000000);
				//j_type(instr,mips_state);
			}
		}
	}


	return 0;
}
