#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

	// Function pointer type definition
	typedef void (Harl::*MemberFuncPtr)(void);

	// Array of function pointers to member functions
	struct FunctionMap {
		std::string level;
		MemberFuncPtr function;
	};

	// Array to map levels to member functions
	static FunctionMap functionMap[4];

public:
	Harl();
	~Harl();

	void complain(std::string level);
};

#endif // HARL_HPP
