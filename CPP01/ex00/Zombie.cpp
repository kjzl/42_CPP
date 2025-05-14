#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : name(name) {
	std::cout << this->name << " has been created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << this->name << " has been destroyed" << std::endl;
}

void Zombie::announce(void) {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
