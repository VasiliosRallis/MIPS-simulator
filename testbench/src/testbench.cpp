#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "test.hpp"
#include "io.hpp"


int main(int argc, char* argv[]){

	if(argc != 2){
		std::cerr << "Error: Expected the simulator as input." << std::endl;
		exit(1);
	}
	std::string simulator(argv[1]);
	std::string fileName = "testbench/tests.txt";

	//Vector in which we will store the tests
	std::vector<Test> v;

	std::ifstream input(fileName);

	if(!input.is_open()){
		std::cerr << "Error: Could not open file " << fileName << std::endl;
	}
	else{
		toVector(input, v);
	}



	input.close();


	//First test
	const char* command = (simulator + " " + v[0].getBin()).c_str();

	//This will run a command on the bash and return the exit-code of that command
	int s = std::system(command);
	if (s == 0){
		v[0].setResult("PASS");
	}
	else{
		v[0].setResult("FAIL");
	}

	std::cout << v[0] << std::endl;

	std::ofstream output("testbench/results.csv");

	if(!output.is_open()){
		std::cerr << "Error: Could not open file ../results.csv" << std::endl;
	}
	else{
		toCSV(output, v);
	}

	output.close();

	//std::string output = exec((simulator + " " + testBin).c_str());

	//std::cout << "The output of the command you ran was: " << std::endl;
	//std::cout << output;

	return 0;
}

