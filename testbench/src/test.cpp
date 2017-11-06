#include "test.hpp"

Test::Test(const std::string& id, const std::string& instruction, const std::string& author, const std::string& message)
	:m_id(id), m_instruction(instruction), m_author(author), m_message(message){}

//getter functions
std::string Test::getId() const {return m_id;}
std::string Test::getInstruction() const {return m_instruction;}
std::string Test::getResult() const {return m_result;}
std::string Test::getAuthor() const {return m_author;}
std::string Test::getMessage() const {return m_message;}
std::string Test::getBin() const {return m_bin;}
