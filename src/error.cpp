#include "error.hpp"
#include <cstdlib> //for std::exit

void checkExec(const std::vector<int32_t>& reg, uint32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1))) && (addr != ADDR_NULL)){
		std::exit(-11);
	}
	if(addr == ADDR_NULL){
		int32_t out = reg[2] & 0x000000FF;
		std::exit(out);
	}
}

void checkRead(uint32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1)))
		&& ((addr < ADDR_DATA) || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))
		&& (addr != ADDR_GETC)){
			std::exit(static_cast<int>(Exception::MEMORY));
		}
}

void checkWrite(uint32_t addr){
	if(((addr < ADDR_DATA || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))) && (addr != ADDR_PUTC)){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
}


char readChar(){
	char c;
	c = std::getchar();
	if(!std::cin.good()){
		std::exit(static_cast<int>(Exception::IO));
	}
	return c;
}

void writeChar(char c){
	std::putchar(c);
	if(!std::cout.good()){
		std::exit(static_cast<int>(Exception::IO));
	}
}
