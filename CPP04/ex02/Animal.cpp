#include "Animal.hpp"

Animal::Animal() : type("Abstract Animal") {
	std::cout << "[Animal] Default constructor called" << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type) {
	std::cout << "[Animal] Copy constructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
	std::cout << "[Animal] Assignment operator called" << std::endl;
	if (this != &other) {
		this->type = other.type;
	}
	return *this;
}

Animal::~Animal() {
	std::cout << "[Animal] Destructor called" << std::endl;
}

std::string Animal::getType() const {
	return this->type;
}
