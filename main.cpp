#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>
#include <bitset>
#include <stdint.h>
#include "R_functions.hpp"
using namespace std;

void i_type(bitset<26>& instr,State& mips_state); //not implemented yet
void j_type(bitset<26>& instr,State& mips_state); //not implemented yetd

//mfc0 not implemented; weird function field


int main(int argc, char* argv[]){

	if(argc != 2){
		std::cerr << "Error: Expected a Binary file a input" << std::endl;
		exit(1);
	}

	string fileName = argv[1];
	State mips_state;

	//Passes the instructions to the
	setUp(mips_state, fileName);

	std::cout << mips_state.rom.size() << " instructions were loaded into ROM" << std::endl;
	/*

	bitset<32> temp = 0xFFFFFFFF;
	
	for(int i=0;i<(mips_state.mem[i]).size();i++) {
		switch(temp & 0xFC000000) {
			
			case '0x0':
				bitset<26> instr = (temp & 0xFC000000);
				r_type(instr,mips_state);
			
			case '0x2':
				bitset<26> instr = (temp & 0xFC000000);
				i_type(instr,mips_state);

			case '0x3':
				bitset<26> instr = (temp & 0xFC000000);
				i_type(instr,mips_state);
			
			default:
				bitset<26> instr = (temp & 0xFC000000);
				j_type(instr,mips_state);
		}
	}

	*/

	return 0;
}
