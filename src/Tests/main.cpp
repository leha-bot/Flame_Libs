#include <iostream>
#include <algorithm>
#include <About/About.h>
#include <Tests/Test.h>

#include <Templates/ForAll.h>

int main(int argc, char** argv)
{
	
	std::cout << argc << ' ' << argv[0] << '\n';
	
	(flame_ide::templates::is_same_types<int, int>()) 
	    ? std::cout << "true\n"
	    : std::cout << "false\n";
    
    (flame_ide::templates::is_same_types<int, long>()) 
	    ? std::cout << "true\n"
	    : std::cout << "false\n";
    
    (flame_ide::templates::is_primitive_type<unsigned char>()) 
	    ? std::cout << "true\n"
	    : std::cout << "false\n";
    
    (flame_ide::templates::is_primitive_type<std::ostream>()) 
	    ? std::cout << "true\n"
	    : std::cout << "false\n";
    
	(flame_ide::templates::is_same_types<int, int&>()) 
	    ? std::cout << "true\n"
	    : std::cout << "false\n";
	
	flame_ide::Test test;
	test.all();
	
	flame_ide::About about;
	
	std::cout << about.date << ' '
			  << about.time << '\n'
			  << "Build Number = " << about.buid_number << '\n';
	
//	const int size = 10;
//	int *arr_int = new int[size], i  = 0;
//	std::for_each(
//		arr_int, arr_int+size,
//		[&](int &input)
//		{
//			input = i;
//			std::cout << "input = " << input << "; i = " << i << '\n';
//			++i;
//		});
	
	return 0;
}