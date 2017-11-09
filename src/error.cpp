#include "error.hpp"
#include <cstdlib> //for std::exit

void checkExec(int32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1))) && (addr != ADDR_NULL)){
		std::exit(-11);
	}
}

void checkRead(int32_t addr){
	if(((addr < ADDR_INSTR) || (addr > (ADDR_INSTR + ADDR_INSTR_L - 1)))
		&& ((addr < ADDR_DATA) || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))
		&& (addr != ADDR_GETC)){
			std::exit(-11);
		}
}

void checkWrite(int32_t addr){
	if(((addr < ADDR_DATA || (addr > (ADDR_DATA + ADDR_DATA_L - 1)))) && (addr != ADDR_PUTC)){
		std::exit(-11);
	}
}
