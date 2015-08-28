#include "Test.h"
#include <vector>
#include <iostream>

#include "../About/About.h"

int main(int argc, char** argv)
{
	
	std::cout << argc << ' ' << argv[0] << '\n';
	
	flame_ide::Test test;
	test.all();
	
//	std::cout << "pos_type = "
//			  << sizeof(std::istream::pos_type)*8
//			  << '\n';
	
	flame_ide::About about;
	
	std::cout << about.date << ' '
			  << about.time << '\n'
			  << "Build Number = " << about.buid_number << '\n';
	
	return 0;
}