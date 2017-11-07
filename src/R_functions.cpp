#include "R_functions.hpp"
#include <limits.h>
using namespace std;

<<<<<<< HEAD
bool r_type(bitset<32>& instr, State& mips_state, bool overflow) {
	bitset<32> funct_field = (instr & bitset<32>(0x0000003F));
	bitset<32> shamt_field = (instr & bitset<32>(0x000007C0));
	bitset<32> dest_field = (instr & bitset<32>(0x0000F800)); //rd
	unsigned long index = dest_field.to_ulong() >> 11;
	bitset<32> source2_field = (instr & bitset<32>(0x001F0000)); //rt
	bitset<32> source1_field = (instr & bitset<32>(0x03E00000)); //rs
	bitset<32> opcode_field = (instr & bitset<32>(0xFC000000)); //op
	overflow = false;
	
	if(funct_field == bitset<32>(0x00000020))
			mips_state.reg[index] = add(mips_state,source1_field,source2_field,overflow);
	else if(funct_field == bitset<32>(0x00000021))
			mips_state.reg[index] = addu(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000024))
			mips_state.reg[index] = And(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000008))
			jr(mips_state,source1_field);
	else if(funct_field == bitset<32>(0x00000027))
			mips_state.reg[index] = nor(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000025))
			mips_state.reg[index] = Or(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x0000002A))
			mips_state.reg[index] = slt(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x0000002B))
			mips_state.reg[index] = sltu(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000000))
			mips_state.reg[index] = sll(mips_state,source2_field,shamt_field);
	else if(funct_field == bitset<32>(0x00000002))
			mips_state.reg[index] = srl(mips_state,source2_field,shamt_field);
	else if(funct_field == bitset<32>(0x00000022))
			mips_state.reg[index] = sub(mips_state,source1_field,source2_field,overflow);
	else if(funct_field == bitset<32>(0x00000023))
			mips_state.reg[index] = subu(mips_state,source1_field,source2_field);
=======
void r_type(bitset<32>& instr, State& mips_state) {
	bitset<32> funct_field = (instr & bitset<32>(0x0000003F));
	bitset<32> shamt_field = (instr & bitset<32>(0x000007C0));
	bitset<32> dest_field = (instr & bitset<32>(0x0000F800)); //rd
	//I think the correct shift is 11 correct me if I'm wrong
	dest_field >>= 11;
	unsigned long dest_field2 = dest_field.to_ulong();
	bitset<32> source2_field = (instr & bitset<32>(0x001F0000)); //rt
	bitset<32> source1_field = (instr & bitset<32>(0x03E00000)); //rs
	
	if(funct_field == bitset<32>(0x00000020))
			mips_state.reg[dest_field2] = add(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000021))
			mips_state.reg[dest_field] = addu(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000024))
			mips_state.reg[dest_field] = And(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000008))
			jr(mips_state,source1_field);
	else if(funct_field == bitset<32>(0x00000027))
			mips_state.reg[dest_field] = nor(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000025))
			mips_state.reg[dest_field] = Or(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x0000002A))
			mips_state.reg[dest_field] = slt(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x0000002B))
			mips_state.reg[dest_field] = sltu(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000000))
			mips_state.reg[dest_field] = sll(mips_state,source2_field,shamt_field);
	else if(funct_field == bitset<32>(0x00000002))
			mips_state.reg[dest_field] = srl(mips_state,source2_field,shamt_field);
	else if(funct_field == bitset<32>(0x00000022))
			mips_state.reg[dest_field] = sub(mips_state,source1_field,source2_field);
	else if(funct_field == bitset<32>(0x00000023))
			mips_state.reg[dest_field] = subu(mips_state,source1_field,source2_field);
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	else if(funct_field == bitset<32>(0x0000001A))
			div(mips_state,source2_field,source1_field);
	else if(funct_field == bitset<32>(0x0000001B))
			divu(mips_state,source2_field,source1_field);
	else if(funct_field == bitset<32>(0x00000010))
			mfhi(mips_state,dest_field);
	else if(funct_field == bitset<32>(0x00000012))
			mflo(mips_state,dest_field);
	else if(funct_field == bitset<32>(0x00000018))
			mult(mips_state,source2_field,source1_field);
	else if(funct_field == bitset<32>(0x00000019))
			multu(mips_state,source2_field,source1_field);
	else if(funct_field == bitset<32>(0x00000003))
<<<<<<< HEAD
			mips_state.reg[index] = sra(mips_state,source2_field,shamt_field);
	else if(opcode_field == bitset<32>(0x00000010) && funct_field == bitset<32>(0x00000000)){
			mfc0(mips_state,source1_field);
	}
			return overflow;
	}

bitset<32> add(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field, bool overflow){
	 bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	 bitset<32> rt = mips_state.reg[source2_field.to_ulong()];	 
	 bitset<1> sign1 = (rs.to_ulong() >> 31);
	 bitset<1> sign2 = (rt.to_ulong() >> 31);
	 if(~(sign1.to_ulong() ^ sign2.to_ulong()) & (((rs.to_ulong() + rt.to_ulong()) >> 31) ^ sign1.to_ulong())){
		overflow = true;
	}
	else {
		overflow = false;
	}
	return  (int)rs.to_ulong() + (int)rt.to_ulong();
}

void mfc0(State& mips_state,bitset<32> source1_field) {
	mips_state.epc = mips_state.reg[source1_field.to_ulong()];
}

bitset<32> addu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	bitset<32>  rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32>  rt = mips_state.reg[source2_field.to_ulong()];
	return  rs.to_ulong()+rt.to_ulong() ;
}

bitset<32> And(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return mips_state.reg[source1_field.to_ulong()] & mips_state.reg[source2_field.to_ulong()];
}

void jr(State& mips_state,bitset<32>& source1_field){
	mips_state.pc = mips_state.reg[source1_field.to_ulong()];
}

bitset<32> nor(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return ~(mips_state.reg[source1_field.to_ulong()] | mips_state.reg[source2_field.to_ulong()]);
}

bitset<32> Or(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return (mips_state.reg[source1_field.to_ulong()] | mips_state.reg[source2_field.to_ulong()]);
}

bool slt(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	if((int)rs.to_ulong() - (int)rt.to_ulong() < 0) {
		return true;
=======
			mips_state.reg[dest_field] = sra(mips_state,source2_field,shamt_field);
		else
			return; //this should be changed to the appropriate error code
	}

bitset<32> add(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	 bitset<32> rs = mips_state.reg[source1_field];
	 bitset<32> rt = mips_state.reg[source2_field];
	return  rs+rt ;
}

bitset<32> addu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	ubitset<32>  rs = mips_state.reg[source1_field];
	ubitset<32>  rt = mips_state.reg[source2_field];
	return  rs+rt ;
}

bitset<32> And(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return mips_state.reg[source1_field] & mips_state.reg[source2_field];
}

void jr(State& mips_state,bitset<32>& source1_field){
	mips_state.pc = mips_state.reg[source1_field];
}

bitset<32> nor(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return ~(mips_state.reg[source1_field] | mips_state.reg[source2_field])
}

bitset<32> Or(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	return (mips_state.reg[source1_field] | mips_state.reg[source2_field]);
}

bool slt(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	signed bitset<32> rs = mips_state.reg[source1_field];
	signed bitset<32> rt = mips_state.reg[source2_field];
	if(rs - rt < 0) {
		return 1;
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	}
	else {
		return false;
	}
}

bool sltu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
<<<<<<< HEAD
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	if(rs.to_ulong() < rt.to_ulong()) {
		return true;
=======
	unsigned bitset<32> rs = mips_state.reg[source1_field];
	unsigned bitset<32> rt = mips_state.reg[source2_field];
	if(rs - rt < 0) {
		return 1;
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	}
	else {
		return false;
	}
}

bitset<32> sll(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field){
<<<<<<< HEAD
	return (mips_state.reg[source2_field.to_ulong()] << shamt_field.to_ulong());
}

bitset<32> srl(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field){
	bitset<32> result = mips_state.reg[source2_field.to_ulong()];
	return (result >> shamt_field.to_ulong());
}

bitset<32> sub(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field, bool overflow){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];	 
	bitset<1> sign1 = (rs.to_ulong() >> 31);
	bitset<1> sign2 = (rt.to_ulong() >> 31);
	if(~(sign1.to_ulong() ^ sign2.to_ulong()) & (((rs.to_ulong() - rt.to_ulong()) >> 31) ^ sign1.to_ulong())){
		overflow = true;
	}
	else {
		overflow = false;
	}
	return  (int)rs.to_ulong() - (int)rt.to_ulong();
}

bitset<32> subu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	return  rs.to_ulong()-rt.to_ulong() ;
}

void div(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	mips_state.Hi = (int)rs.to_ulong() % (int)rt.to_ulong();
	mips_state.Lo = rs.to_ulong() / rt.to_ulong();
}

void divu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	mips_state.Hi = rs.to_ulong() % rt.to_ulong();
	mips_state.Lo = rs.to_ulong() / rt.to_ulong();
}

void mfhi(State& mips_state,bitset<32>& dest_field){
	mips_state.reg[dest_field.to_ulong()] = mips_state.Hi;
}

void mflo(State& mips_state,bitset<32>& dest_field){
	mips_state.reg[dest_field.to_ulong()] = mips_state.Lo;
}

void mult(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	int64_t result  = (int)rs.to_ulong() * (int)rt.to_ulong();
=======
	return (mips_state.reg[source2_field] << shamt_field);
}

bitset<32> srl(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field){
	ubitset<32> result = mips_state.reg[source2_field];
	return (result >> shamt_field);
}

bitset<32> sub(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	signed bitset<32> rs = mips_state.reg[source1_field];
	signed bitset<32> rt = mips_state.reg[source2_field];
	return  rs-rt ;
}

bitset<32> subu(State& mips_state,bitset<32>& source1_field,bitset<32>& source2_field){
	ubitset<32> rs = mips_state.reg[source1_field];
	ubitset<32> rt = mips_state.reg[source2_field];
	return  rs-rt ;
}

void div(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	signed bitset<32> rs = mips_state.reg[source1_field];
	signed bitset<32> rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void divu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	unsigned bitset<32> rs = mips_state.reg[source1_field];
	unsigned bitset<32> rt = mips_state.reg[source2_field];
	mips_state.Hi = rs % rt;
	mips_state.Lo = rs / rt;
}

void mfhi(State& mips_state,bitset<32>& dest_field){
	mips_state.reg[dest_field] = mips_state.Hi;
}

void mflo(State& mips_state,bitset<32>& dest_field){
	mips_state.reg[dest_field] = mips_state.Lo;
}

void mult(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
	signed bitset<32> rs = mips_state.reg[source1_field];
	signed bitset<32>	rt = mips_state.reg[source2_field];
	signed int64_t result  = rs * rt;
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

void multu(State& mips_state,bitset<32>& source2_field,bitset<32>& source1_field){
<<<<<<< HEAD
	bitset<32> rs = mips_state.reg[source1_field.to_ulong()];
	bitset<32> rt = mips_state.reg[source2_field.to_ulong()];
	uint64_t result = rs.to_ulong() * rt.to_ulong();
=======
	ubitset<32> rs = mips_state.reg[source1_field];
	ubitset<32> rt = mips_state.reg[source2_field];
	uint64_t result = rs * rt;
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	mips_state.Hi = (result >> 32);
	mips_state.Lo = (result << 32) >> 32;
}

bitset<32> sra(State& mips_state,bitset<32>& source2_field,bitset<32> shamt_field){
<<<<<<< HEAD
	bitset<32> result = mips_state.reg[source2_field.to_ulong()];
	return ((int)result.to_ulong() >> shamt_field.to_ulong());
=======
	signed bitset<32> result = mips_state.reg[source2_field];
	return (result >> shamt_field);
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
}
