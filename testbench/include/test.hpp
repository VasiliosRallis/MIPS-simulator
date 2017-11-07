#ifndef TEST_HPP_
#define TEST_HPP_

#include <string>

class Test{
private:
	std::string m_id;
	std::string m_instruction;
	std::string m_result;
	std::string m_author;
	std::string m_bin;
	std::string m_message;
	int m_exitCode;
public:
	//Note we don't pass the result because we don't know it yet!
	Test(const std::string& id, const std::string& instruction, const std::string& author, const std::string& bin, const std::string& message = "No message", int exitCode = 0);

	//getter functions
	std::string getId() const;
	std::string getInstruction() const;
	std::string getResult() const;
	std::string getAuthor() const;
	std::string getMessage() const;
	std::string getBin() const;
	int getExitCode() const;

	//setter functions
	void setResult(const std::string& result);

	friend std::ostream& operator<<(std::ostream& out, const Test& test);
};

#endif
