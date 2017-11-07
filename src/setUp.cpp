#include "setUp.hpp"

void setUp(State& s, const std::string& fileName){

	std::ifstream fileIn(fileName, std::ios::binary | std::ios::ate);

	if(!fileIn.is_open()){
		std::cout << "E: Could not open file" << std::endl;
	}
	else{
		MBlock m;

	    m.size = fileIn.tellg();
	    m.data = new char [m.size];
	    fileIn.seekg (0, std::ios::beg);
	    fileIn.read (m.data, m.size);
	    fileIn.close();


	    std::cout << "Bit read: " << std::endl;
	    for(int i = 0; i < m.size; i++){
	    	std::bitset<8> temp(m.data[i]);
	    	std::cout << temp << " ";
	    	if(((i + 1) % 4) == 0){
	    		std::cout << std::endl;
	    	}
	    }

	    memToVector(m, s.rom);

	}
}



void memToVector(const MBlock& m, std::vector<std::bitset<32> >& v){
	for(int i = 0; i < m.size; i+=4){
		v.push_back(convTo32B(&m.data[i]));
	}
}

std::bitset<32> convTo32B(char* in){
		std::bitset<32> out, temp;

		for(int i = 0; i < 4; i++){
			out <<= 8;
			temp = in[i];
			temp<<= 24;
			temp>>= 24;
			out|= temp;
		}

		return out;
}
