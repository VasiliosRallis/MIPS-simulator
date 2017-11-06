#ifndef SETUP_HPP_
#define SETUP_HPP_

#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>

struct State{
	std::vector<std::bitset<32> > mem;
	std::vector<std::bitset<32> > rom;
	std::bitset<32> pc;
	std::vector<std::bitset<32> >reg = std::vector<std::bitset<32> >(32);
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
