#include "test.hpp"

Test::Test(const std::string& id, const std::string& instruction, const std::string& author, const std::string& bin, const  std::string& message, int exitCode)
	:m_id(id), m_instruction(instruction), m_author(author), m_bin(bin), m_message(message), m_exitCode(exitCode){}

//getter functions
std::string Test::getId() const {return m_id;}
std::string Test::getInstruction() const {return m_instruction;}
std::string Test::getResult() const {return m_result;}
std::string Test::getAuthor() const {return m_author;}
std::string Test::getBin() const {return m_bin;}
std::string Test::getMessage() const {return m_message;}
int Test::getExitCode() const {return m_exitCode;}


//setter functions
void Test::setResult(const std::string& result){m_result = result;}

//Weird Error here so I had to use ghetto fix
std::ostream& operator<<(std::ostream& out, const Test& test){
	std::string temp(", ");
	out << test.m_id << temp << test.m_instruction << temp << test.m_result << temp << test.m_message;
	return out;
}
