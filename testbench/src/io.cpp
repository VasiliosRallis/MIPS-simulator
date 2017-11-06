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

void toVector(std::ifstream& input, std::vector<Test>& v){

	std::string line;
	getline(input, line);

	while(getline(input, line)){
		v.push_back(toTest(line));
	}

}


Test toTest(const std::string& line){
    std::size_t p(line.find(','));
    std::size_t initialP(0);

    std::vector<std::string> temp;
    // Breaking the line into individual strings
    while(p != std::string::npos){
        temp.push_back(line.substr(initialP,(p - initialP)));
        initialP = p + 1;
        p = line.find(',', initialP);
    }

    //Add the last string which is the message
    temp.push_back(line.substr(initialP, (line.size() - initialP)));
    														//Convert the last par to an int
    Test tempt(temp[0], temp[1], temp[2], temp[3], temp[4], std::stoi(temp[5]));
    return tempt;
}

void toCSV(std::ofstream& output, const std::vector<Test>& v){
	for(int i(0); i < v.size(); i++){
		output << v[i].getId() << "," << v[i].getInstruction() << "," << v[i].getResult() << "," << v[i].getAuthor() << "," << v[i].getMessage() << std::endl;
	}
}
