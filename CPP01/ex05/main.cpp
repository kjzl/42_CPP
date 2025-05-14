#include "Harl.hpp"
#include <iostream>

int main() {
	Harl harl;

	std::cout << "Testing Harl's complaints at different levels:" << std::endl << std::endl;

	std::cout << "==== DEBUG LEVEL ====" << std::endl;
	harl.complain("DEBUG");

	std::cout << "==== INFO LEVEL ====" << std::endl;
	harl.complain("INFO");

	std::cout << "==== WARNING LEVEL ====" << std::endl;
	harl.complain("WARNING");

	std::cout << "==== ERROR LEVEL ====" << std::endl;
	harl.complain("ERROR");

	std::cout << "==== INVALID LEVEL ====" << std::endl;
	harl.complain("CRITICAL");

	return 0;
}
