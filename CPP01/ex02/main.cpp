#include <iostream>
#include <string>

int main() {
	// Initialize the string variable
	std::string str = "HI THIS IS BRAIN";

	// Create a pointer to the string
	std::string* stringPTR = &str;

	// Create a reference to the string
	std::string& stringREF = str;

	// Print memory addresses
	std::cout << "Memory address of the string variable: " << &str << std::endl;
	std::cout << "Memory address held by stringPTR: " << stringPTR << std::endl;
	std::cout << "Memory address held by stringREF: " << &stringREF << std::endl;

	// Print values
	std::cout << "Value of the string variable: " << str << std::endl;
	std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

	return 0;
}
