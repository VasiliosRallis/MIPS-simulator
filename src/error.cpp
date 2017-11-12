#include "error.hpp"
#include <cstdlib> //for std::exit

void checkExec(const std::vector<int32_t>& reg, uint32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1))) && (addr != ADDR_NULL)){
		std::exit(-11);
	}
	if(addr == ADDR_NULL){
		int32_t out = reg[3] & 0x000000FF;
		std::exit(out);
	}
}

void checkRead(uint32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1)))
		&& ((addr < ADDR_DATA) || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))
		&& (addr != ADDR_GETC)){
			std::exit(-11);
		}
}

void checkWrite(uint32_t addr){
	if(((addr < ADDR_DATA || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))) && (addr != ADDR_PUTC)){
		std::exit(-11);
	}
}

void checkDiv4(uint32_t addr){
	if(addr % 4 != 0){
		std::exit(-11);
	}
}

char readChar(){
	char c;
	std::cin.get(c);
	if(!std::cin.good()){
		std::exit(-21);
	}
}

void writeChar(char c){
	std::cout.put(c);
	if(!std::cout.good()){
		std::exit(-21);
	}
}
