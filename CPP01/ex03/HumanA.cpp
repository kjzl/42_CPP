#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon& weapon) : name(name), weapon(weapon) {
	std::cout << "HumanA " << this->name << " is created with a " << this->weapon.getType() << std::endl;
}

HumanA::~HumanA() {
	std::cout << "HumanA " << this->name << " is destroyed" << std::endl;
}

void HumanA::attack() const {
	std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}
