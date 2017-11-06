#include "io.hpp"

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

void toVector(const std::string& fileName, std::vector<Test>& v){

	std::ifstream input(fileName);

	if(!input.is_open()){
		std::cerr << "Error: Could not open file " << fileName << std::endl;
	}
	else{

	}
}
