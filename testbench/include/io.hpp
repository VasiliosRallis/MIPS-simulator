#ifndef IO_HPP_
#define IO_HPP_

#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <fstream>
#include "test.hpp"
#include <iostream>

//Here will will place all the functions that handle the input and output to the testbench

//This function returns the output of a command on the command line.
//You pass as input the command you would like to run on the command line
//The output of that command is returned to you as a string.
std::string exec(const char* cmd);

//This function will take the list of test that we have in "tests.txt" and import them to a vector of out class test
void toVector(const std::string& fileName, std::vector<Test>& v);


#endif
