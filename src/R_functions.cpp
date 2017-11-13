#include "R_functions.hpp"
using namespace std;

void r_type(State& mips_state){
	int32_t instr = mips_state.ram[mips_state.pc];
	uint32_t funct_field = instr & 0x0000003F;
	uint32_t shamt_field = (instr & 0x000007C0) >> 6;
	uint32_t rd = (instr & 0x0000F800) >> 11;
	uint32_t rt = (instr & 0x001F0000) >> 16; 
	uint32_t rs = (instr & 0x03E00000) >> 21; 
	

	switch(funct_field){
	case 0x00000020:
			add(mips_state, rs, rt, rd); 
			break;			
	case 0x00000021:
			addu(mips_state, rs, rt, rd);
			break;
	case 0x00000024:
			And(mips_state, rs, rt, rd);
			break;
	case 0x00000008:
			jr(mips_state,rs);
			break;
	case 0x00000027:
			nor(mips_state, rs, rt, rd);
			break;
	case 0x00000025:
			Or(mips_state, rs, rt, rd);
			break;
	case 0x0000002A:
			slt(mips_state, rs, rt, rd);
			break;
	case 0x0000002B:
			sltu(mips_state, rs, rt, rd);
			break;
	case 0x00000000:
			sll(mips_state, rt, shamt_field, rd);
			break;
	case 0x00000002:
			srl(mips_state, rt, shamt_field, rd);
			break;
	case 0x00000022:
			sub(mips_state, rs, rt, rd); 
			break;
	case 0x00000023:
			subu(mips_state, rs, rt, rd);
			break;
	case 0x0000001A:
			div(mips_state, rt, rs);
			break;
	case 0x0000001B:
			divu(mips_state, rt, rs);
			break;
	case 0x00000010:
			mfhi(mips_state, rd);
			break;
	case 0x00000012:
			mflo(mips_state, rd);
			break;
	case 0x00000018:
			mult(mips_state, rt, rs);
			break;
	case 0x00000019:
			multu(mips_state, rt, rs);
			break;
	case 0x00000003:
			sra(mips_state, rt, shamt_field, rd);
			break;
	case 0x00000011:
			mthi(mips_state,rs);
			break;
	case 0x00000013:
			mtlo(mips_state,rs);
			break;
	case 0x00000004:
			sllv(mips_state,rt,rs,rd);
			break;
	case 0x00000007:
			srav(mips_state,rt,rs,rd);
			break;
	case 0x00000006:
			srlv(mips_state,rt,rs,rd);
			break;
	default:
			std::exit(static_cast<int>(Exception::INSTRUCTION));
			break;
	}
}

void add(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	 int32_t temp1 = mips_state.reg[rs];
	 int32_t temp2 = mips_state.reg[rt];
	 if (((temp1 < 0 ) && (temp2 < 0) && (temp1 + temp2 > 0)) || ((temp1 > 0) && (temp2 > 0) && (temp1 + temp2 < 0))){
		std::exit(static_cast<int>(Exception::ARITHMETIC));
	}
	else {
		mips_state.reg[rd] = temp1 + temp2;
	}
	 ++mips_state.pc;
}


void addu(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	uint32_t  temp1 = mips_state.reg[rs];
	uint32_t  temp2 = mips_state.reg[rt];
	mips_state.reg[rd] = temp1+temp2 ;
}

void And(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	mips_state.reg[rd] = mips_state.reg[rs] & mips_state.reg[rt];
}

void jr(State& mips_state, uint32_t rs){
	if(mips_state.reg[rs] % 4 != 0){
		std::exit(static_cast<int>(Exception::MEMORY));
	}
	else{
		mips_state.pc = mips_state.reg[rs] / 4;
	}
}

void nor(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	mips_state.reg[rd] = ~(mips_state.reg[rs] | mips_state.reg[rt]);
}

void Or(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	mips_state.reg[rd] = (mips_state.reg[rs] | mips_state.reg[rt]);
}

void slt(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	int32_t temp1 = mips_state.reg[rs];
	int32_t temp2 = mips_state.reg[rt];
	if( (temp1 - temp2) < 0) {
		mips_state.reg[rd] = 1;
	}
	else {
		mips_state.reg[rd] = 0;
	}
}

void sltu(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	uint32_t temp1 = mips_state.reg[rs];
	uint32_t temp2 = mips_state.reg[rt];
	if(temp1 < temp2) {
		mips_state.reg[rd] = 1;
	}
	else {
		mips_state.reg[rd] = 0;
	}
}

void sll(State& mips_state, uint32_t rt, uint32_t shamt_field, uint32_t rd){
	mips_state.reg[rd] = (mips_state.reg[rt] << shamt_field);
}

void srl(State& mips_state, uint32_t rt, uint32_t shamt_field, uint32_t rd){
	uint32_t result = mips_state.reg[rt];
	mips_state.reg[rd] = (result >> shamt_field);
}

void sub(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	int32_t temp1 = mips_state.reg[rs];
	int32_t temp2 = mips_state.reg[rt];
	if(((temp1 - temp2) < temp1) != (temp2 > 0)){
		std::exit(static_cast<int>(Exception::ARITHMETIC));
	}
	else {
		mips_state.reg[rd] =  temp1-temp2;
	}
}

void subu(State& mips_state, uint32_t rs, uint32_t rt, uint32_t rd){
	uint32_t temp1 = mips_state.reg[rs];
	uint32_t temp2 = mips_state.reg[rt];
	mips_state.reg[rd] =  temp1 - temp2 ;
}

void div(State& mips_state, uint32_t rt, uint32_t rs){
	int32_t temp1 = mips_state.reg[rs];
	int32_t temp2 = mips_state.reg[rt];
	mips_state.Hi = temp1 % temp2;
	mips_state.Lo = temp1 / temp2;
}

void divu(State& mips_state, uint32_t rt, uint32_t rs){
	uint32_t temp1 = mips_state.reg[rs];
	uint32_t temp2 = mips_state.reg[rt];
	mips_state.Hi = temp1 % temp2;
	mips_state.Lo = temp1 / temp2;
}

void mfhi(State& mips_state, uint32_t rd){
	mips_state.reg[rd] = mips_state.Hi;
}

void mflo(State& mips_state, uint32_t rd){
	mips_state.reg[rd] = mips_state.Lo;
}

void mult(State& mips_state, uint32_t rt, uint32_t rs){
	int32_t temp1 = mips_state.reg[rs];
	int32_t temp2 = mips_state.reg[rt];
	int64_t result  = temp1 * temp2;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void multu(State& mips_state, uint32_t rt, uint32_t rs){
	uint32_t temp1 = mips_state.reg[rs];
	uint32_t temp2 = mips_state.reg[rt];
	uint64_t result = temp1 * temp2;
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void sra(State& mips_state, uint32_t rt, uint32_t shamt_field, uint32_t rd){
	int32_t result = mips_state.reg[rt];
	mips_state.reg[rd] = (result >> shamt_field);
}

void mthi(State& mips_state,uint32_t rs){
	mips_state.Hi = mips_state.reg[rs];
}

void mtlo(State& mips_state,uint32_t rs){
	mips_state.Lo = mips_state.reg[rs];
}

void sllv(State& mips_state,uint32_t rt,uint32_t rs, uint32_t rd){
	mips_state.reg[rd] = (mips_state.reg[rt] << mips_state.reg[rs]);
}

void srav(State& mips_state,uint32_t rt,uint32_t rs, uint32_t rd){
	mips_state.reg[rd] = ((int32_t)mips_state.reg[rt] >> mips_state.reg[rs]);
}

void srlv(State& mips_state,uint32_t rt,uint32_t rs, uint32_t rd){
	uint32_t temp = mips_state.reg[rt];
	mips_state.reg[rd]  = temp >> mips_state.reg[rs];
}
