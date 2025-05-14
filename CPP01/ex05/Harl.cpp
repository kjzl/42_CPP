#include "Harl.hpp"
#include <iostream>

// Initialize the static member
Harl::FunctionMap Harl::functionMap[4] = {
	{"DEBUG", &Harl::debug},
	{"INFO", &Harl::info},
	{"WARNING", &Harl::warning},
	{"ERROR", &Harl::error}
};

Harl::Harl() {
	std::cout << "Harl is ready to complain." << std::endl;
}

Harl::~Harl() {
	std::cout << "Harl is leaving (but still complaining)." << std::endl;
}

void Harl::debug(void) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
	std::cout << std::endl;
}

void Harl::info(void) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
	std::cout << std::endl;
}

void Harl::warning(void) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month." << std::endl;
	std::cout << std::endl;
}

void Harl::error(void) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
	std::cout << std::endl;
}

void Harl::complain(std::string level) {
	for (int i = 0; i < 4; i++) {
		if (level == functionMap[i].level) {
			(this->*(functionMap[i].function))();
			return;
		}
	}
	std::cout << "[ INVALID LEVEL ]" << std::endl;
	std::cout << "Harl doesn't know how to complain at level: " << level << std::endl;
	std::cout << std::endl;
}
