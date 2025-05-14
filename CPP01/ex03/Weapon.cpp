#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon(std::string type) : type(type) {
	std::cout << "Weapon of type '" << this->type << "' created" << std::endl;
}

Weapon::~Weapon() {
	std::cout << "Weapon of type '" << this->type << "' destroyed" << std::endl;
}

const std::string& Weapon::getType() const {
	return this->type;
}

void Weapon::setType(std::string type) {
	this->type = type;
}
