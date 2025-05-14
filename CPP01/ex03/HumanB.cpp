#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) : name(name), weapon(NULL) {
	std::cout << "HumanB " << this->name << " is created without a weapon" << std::endl;
}

HumanB::~HumanB() {
	std::cout << "HumanB " << this->name << " is destroyed" << std::endl;
}

void HumanB::setWeapon(Weapon& weapon) {
	this->weapon = &weapon;
	std::cout << this->name << " is now armed with a " << this->weapon->getType() << std::endl;
}

void HumanB::attack() const {
	if (this->weapon) {
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	} else {
		std::cout << this->name << " tries to attack but has no weapon!" << std::endl;
	}
}
