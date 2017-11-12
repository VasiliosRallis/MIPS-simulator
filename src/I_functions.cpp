#include "I_functions.hpp"
using namespace std;

void i_type(State& mips_state){
	int32_t instr = mips_state.ram[mips_state.pc];

	int32_t opcode = (instr & 0xFC000000) >> 26;
	int32_t rs = (instr & 0x03E00000) >> 21;
	int32_t rt= (instr & 0x001F0000) >> 16;
	int32_t immediate = instr & 0x0000FFFF;

	//In our case BranchAddr = SignExtImm;

	int32_t SignExtImm;

	if(immediate >> 15){
		SignExtImm = immediate | 0xFFFF0000;
	}
	else{
		SignExtImm = immediate;
	}


	switch(opcode){
	case 0x00000008:
		addi(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000009:
		addiu(mips_state, rs, rt, SignExtImm);
		break;
	case 0x0000000C:
		andi(mips_state, rs, rt, immediate);
		break;
	case 0x00000004:
		beq(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000005:
		bne(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000024:
		lbu(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000020:
		lb(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000025:
		lhu(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000021:
		lh(mips_state, rs, rt, SignExtImm);
		break;
	case 0x0000000F:
		lui(mips_state, rs, rt, immediate);
		break;
	case 0x00000023:
		lw(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000022:
		lwl(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000026:
		lwr(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000028:
		sb(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000029:
		sh(mips_state, rs, rt, SignExtImm);
		break;
	case 0x0000002B:
		sw(mips_state, rs, rt, SignExtImm);
		break;
	case 0x0000000A:
		slti(mips_state, rs, rt, SignExtImm);
		break;
	case 0x0000000B:
		sltiu(mips_state, rs, rt, immediate);
		break;
	case 0x0000000E:
		xori(mips_state, rs, rt, immediate);
		break;
	case 0x0000000D:
		ori(mips_state, rs, rt, immediate);
		break;
	case 0x00000007:
		bgtz(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000006:
		blez(mips_state, rs, rt, SignExtImm);
		break;
	case 0x00000001:
		bdecoder(mips_state, rs, rt, immediate);
		break;
	default:
		std::exit(static_cast<int>(Exception::INSTRUCTION));
		break;
	}
}


void addi(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	rs = mips_state.reg[rs];

	if (((rs < 0) && (SignExtImm < 0) && (rs + SignExtImm > 0)) || ((rs > 0) && (SignExtImm > 0) && (rs + SignExtImm <0))){
		std::exit(static_cast<int>(Exception::ARITHMETIC));
	}
	else {
		mips_state.reg[rt] = rs + SignExtImm;
	}

	++mips_state.pc;
}

void addiu(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	rs = mips_state.reg[rs];
	mips_state.reg[rt] = rs + SignExtImm;

	++mips_state.pc;
}
	
void andi(State& mips_state, int32_t rs, int32_t rt, int32_t immediate){
	rs = mips_state.reg[rs];
	mips_state.reg[rt] = rs & immediate;

	++mips_state.pc;
}

void beq(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	if(mips_state.reg[rt] == mips_state.reg[rs]){
		mips_state.pc += 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}

void bne(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	if(mips_state.reg[rt] != mips_state.reg[rs]){
		mips_state.pc += 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}

void lbu(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkRead(static_cast<int>(addr / 4));
	int32_t temp;

	if(addr % 4 != 0){
		int32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
		temp = temp << (8 * (addr % 4));
		temp = temp >> (32 - (8 * (addr % 4)));
	}
	else{
		temp = mips_state.ram[addr / 4];
		temp = temp >> 24;
	}

	mips_state.reg[rt] = temp;
	++mips_state.pc;

}

void lb(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkRead(static_cast<int>(addr / 4));
	int32_t temp;

	if(addr % 4 != 0){
		int32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
		temp = temp << (8 * (addr % 4));
		temp = temp >> (32 - (8 * (addr % 4)));
	}
	else{
		temp = mips_state.ram[addr / 4];
		temp = temp >> 24;
	}

	if(temp >> 7){
		temp = temp | 0xFFFFFF00;
	}

	mips_state.reg[rt] = temp;
	++mips_state.pc;

}

void lhu(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkRead(static_cast<int>(addr / 4));
	int32_t temp;

	if(addr % 2 != 0){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
	else{
		if(addr % 4 != 0){
			int32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
			temp = temp << (8 * (addr % 4));
			temp = temp >> (24 - (8 * (addr % 4)));
		}
		else{
			temp = mips_state.ram[addr / 4];
			temp = temp >> 16;
		}
		mips_state.reg[rt] = temp;
	}

	++mips_state.pc;
}
	
void lh(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkRead(static_cast<int>(addr / 4));
	int32_t temp;

	if(addr % 2 != 0){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
	else{
		if(addr % 4 != 0){
			int32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
			temp = temp << (8 * (addr % 4));
			temp = temp >> (24 - (8 * (addr % 4)));
		}
		else{
			temp = mips_state.ram[addr / 4];
			temp = temp >> 16;
		}

		if(temp >> 15){
			temp = temp | 0xFFFF0000;
		}

		mips_state.reg[rt] = temp;
	}

	++mips_state.pc;
}


void lui(State& mips_state, int32_t rs, int32_t rt, int32_t immediate){
	if(rs != 0x00000000){
		std::exit(static_cast<int>(Exception::INSTRUCTION));
	}
	else{
		immediate = immediate << 16;
		mips_state.reg[rt] = immediate;
	}

	++mips_state.pc;
}

void lw(State& mips_state , int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERFLOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	if(addr % 4 != 0){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
	else {
		mips_state.reg[rt] = mips_state.ram[addr / 4];
	}

	++mips_state.pc;
}

void lwl(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){

	uint32_t word;
	uint32_t addr = SignExtImm + mips_state.reg[rs];

	if(addr % 4 != 0){
		uint32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
		temp = temp << 8 * (addr % 4);
		word = temp | (mips_state.ram[static_cast<int>(addr / 4) + 1] >> (8 * (addr % 4)));
	}
	else{
		word = mips_state.ram[static_cast<int>(addr / 4)];
	}

	mips_state.reg[rt] = mips_state.reg[rt] & 0x0000FFFF;
	mips_state.reg[rt] = mips_state.reg[rt] | (word & 0xFFFF0000);

	++mips_state.pc;

}

void lwr(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){

	uint32_t word;
	uint32_t addr = SignExtImm + mips_state.reg[rs];

	if(addr % 4 != 0){
		uint32_t temp = mips_state.ram[static_cast<int>(addr / 4)];
		temp = temp << 8 * (addr % 4);
		word = temp | (mips_state.ram[static_cast<int>(addr / 4) + 1] >> (8 * (addr % 4)));
	}
	else{
		word = mips_state.ram[static_cast<int>(addr / 4)];
	}

	mips_state.reg[rt] = mips_state.reg[rt] & 0xFFFF0000;
	mips_state.reg[rt] = mips_state.reg[rt] | (word & 0x0000FFFF);

	++mips_state.pc;

}

void ori(State& mips_state, int32_t rs, int32_t rt, int32_t immediate){
	mips_state.reg[rt] = mips_state.reg[rs] | immediate;

	++mips_state.pc;
}

void xori(State& mips_state, int32_t rs, int32_t rt, int32_t immediate){
	mips_state.reg[rt] = mips_state.reg[rs] ^ immediate;

	++mips_state.pc;
}

void slti(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	if(mips_state.reg[rs] < SignExtImm){
		mips_state.reg[rt] = 1;
	}
	else{
		mips_state.reg[rt] = 0;
	}

	++mips_state.pc;
}

void sltiu(State& mips_state, int32_t rs, int32_t rt, int32_t immediate){
	if(mips_state.reg[rs] < immediate){
		mips_state.reg[rt] = 1;
	}
	else{
		mips_state.reg[rt] = 0;
	}

	++mips_state.pc;
}

void sb(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkWrite(static_cast<uint32_t>(addr / 4));

	int32_t temp = mips_state.reg[rt] & 0x000000FF;
	temp = temp << 24;

	mips_state.ram[static_cast<int>(addr / 4)] = mips_state.ram[static_cast<int>(addr / 4)] & (0x00FFFFFF >> (8 * (addr % 4)));
	mips_state.ram[static_cast<int>(addr / 4)] = mips_state.ram[static_cast<int>(addr / 4)] | (temp >> (8 * (addr % 4)));

	++mips_state.pc;
}

void sh(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERLFOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkWrite(static_cast<uint32_t>(addr / 4));

	if(addr % 2){
		std::exit(static_cast<int>(Exception::MEMORY));
	}

	else{
		int32_t temp = mips_state.reg[rt] & 0x0000FFFF;
		temp = temp << 16;

		mips_state.ram[static_cast<int>(addr / 4)] = mips_state.ram[static_cast<int>(addr / 4)] & (0x0000FFFF >> (8 * (addr % 4)));
		mips_state.ram[static_cast<int>(addr / 4)] = mips_state.ram[static_cast<int>(addr / 4)] | (temp >> (8 * (addr % 4)));

	}

	++mips_state.pc;
}

void sw(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	//THINK ABOUT OVERFLOW HERE
	uint32_t addr = SignExtImm + mips_state.reg[rs];
	checkWrite(static_cast<int32_t>(addr / 4));

	if(addr % 4 != 0){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
	else{
		mips_state.ram[addr] = mips_state.reg[rt];
	}

	++mips_state.pc;
}

void bgez(State& mips_state, int32_t rs, int32_t SignExtImm){
	if(rs >= 0){
		mips_state.pc =+ 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}

void bgezal(State& mips_state, int32_t rs, int32_t SignExtImm){
	if(rs >= 0){
		mips_state.reg[31] = mips_state.pc + 1;
		mips_state.pc =+ 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}

void bgtz(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	if(rt != 0x00000000){
		std::exit(static_cast<int>(Exception::INSTRUCTION));
	}
	else{
		if(rs > 0){
			mips_state.pc =+ 1 + SignExtImm;
		}
		else{
			++mips_state.pc;
		}
	}
}

void blez(State& mips_state, int32_t rs, int32_t rt, int32_t SignExtImm){
	if(rt != 0){
		std::exit(static_cast<int>(Exception::INSTRUCTION));
	}

	else{
		if(rs <= 0x00000000){
			mips_state.pc =+ 1 + SignExtImm;
		}
		else{
			++mips_state.pc;
		}
	}
}

void bltz(State& mips_state, int32_t rs, int32_t SignExtImm){
	if(rs < 0){
		mips_state.pc =+ 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}

void bltzal(State& mips_state, int32_t rs, int32_t SignExtImm){

	if(rs < 0){
		mips_state.reg[31] = mips_state.pc + 1;
		mips_state.pc =+ 1 + SignExtImm;
	}
	else{
		++mips_state.pc;
	}
}
	
void bdecoder(State& mips_state, int32_t rt, int32_t rs, int32_t SignExtImm){
	switch(rt){
	case 0x00000001:
		bgez(mips_state, rs, SignExtImm);
		break;
	case 0x00000011:
		bgezal(mips_state, rs, SignExtImm);
		break;
	case 0x00000000:
		bltz(mips_state, rs, SignExtImm);
		break;
	case 0x00000010:
		bltzal(mips_state, rs, SignExtImm);
		break;
	default:
		std::exit(static_cast<int>(Exception::INSTRUCTION));
		break;
	}
}
			
