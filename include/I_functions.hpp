#ifndef I_TYPEHPP
#define I_TYPEHPP
#include <stdint.h>

bool i_type(State& mips_state);

int32_t addi(State& mips_state,uint32_t source1_field,int32_t SignExtImm,bool& overflow);
uint32_t addiu(State& mips_state,uint32_t source1_field,int32_t SignExtImm);
int32_t Andi(State& mips_state,uint32_t source1_field, uint32_t ZeroExtImm);
void beq(State& mips_state,uint32_t source1_field,uint32_t index,uint32_t offset);
void bne(State& mips_state,uint32_t source1_field,uint32_t index,uint32_t offset);
void lbu(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lb(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lhu(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lh(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lui(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lw(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm); 
void lwl(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void lwr(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
int32_t ori(State& mips_state,uint32_t source1_field, uint32_t ZeroExtImm);
int32_t xori(State& mips_state,uint32_t source1_field, uint32_t ZeroExtImm);
bool slti(State& mips_state,uint32_t source1_field,int32_t SignExtImm);
bool sltiu(State& mips_state,uint32_t source1_field,int32_t SignExtImm);
void sb(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void sh(State& mips_state,uint32_t source1_field,uint32_t index, int32_t SignExtImm);
void sw(State& mips_state,uint32_t source1_field,int32_t SignExtImm);
void bgez(State& mips_state, uint32_t source1_field, uint32_t offset);
void bgezal(State& mips_state, uint32_t source1_field, int32_t SignExtImm);
void bgtz(State& mips_state, uint32_t source1_field, int32_t SignExtImm);

#endif
