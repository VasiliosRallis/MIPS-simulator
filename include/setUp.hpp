#ifndef SETUP_HPP_
#define SETUP_HPP_

#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>

struct State{
	std::vector<std::bitset<32> > mem;
	std::vector<std::bitset<32> > rom;
<<<<<<< HEAD
	std::bitset<32> pc, epc;
=======
	std::bitset<32> pc;
>>>>>>> d2eeff1f4d5af1854ba360df3b9206292726a77f
	std::vector<std::bitset<32> > reg;
	std::bitset<32> Hi;
	std::bitset<32> Lo;
};

struct MBlock{
	std::streampos size;
	char* data;
};

void setUp(State& s, const std::string& fileName);
std::bitset<32> convTo32B(char* in);
void memToVector(const MBlock& m, std::vector<std::bitset<32> >& v);

#endif /* SETUP_HPP_ */
