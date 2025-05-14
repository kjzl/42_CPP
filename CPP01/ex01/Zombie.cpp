#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("") {
	std::cout << "A nameless zombie has been created" << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
	std::cout << this->name << " has been created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << this->name << " has been destroyed" << std::endl;
}

void Zombie::announce(void) {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
	this->name = name;
}
