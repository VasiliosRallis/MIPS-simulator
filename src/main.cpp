#include <iostream>
#include "mips.hpp"
#include <fstream>
#include <string>

int main(int argc, char* argv[]){

	std::string fileName = static_cast<std::string>(argv [1]);

	State state;
	setUp(state, fileName);

	return 0;
}

