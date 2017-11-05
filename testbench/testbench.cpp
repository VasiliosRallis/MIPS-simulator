#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>


//Doesn't do anything yet still implementing

std::string exec(const char* cmd);

int main(){


	std::string simulator = "./bin/mips_simulator";
	std::string testBin = "testbench/test.mips.bin";
	char* command = (simulator + " " + testBin).c_str();

	int s = std::system(command);

	std::string output = exec((simulator + " " + testBin).c_str());

	std::cout << "The output of the command you ran was: " << std::endl;
	std::cout << output;

	return 0;
}


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
