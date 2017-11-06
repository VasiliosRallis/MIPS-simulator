#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "test.hpp"
#include "io.hpp"


int main(){


	std::string simulator = "./bin/mips_simulator";
	std::string testBin = "testbench/test.mips.bin";
	const char* command = (simulator + " " + testBin).c_str();

	//This will run a command on the bash and return the exit-code of that command
	int s = std::system(command);

	std::string output = exec((simulator + " " + testBin).c_str());

	std::cout << "The output of the command you ran was: " << std::endl;
	std::cout << output;

	return 0;
}

