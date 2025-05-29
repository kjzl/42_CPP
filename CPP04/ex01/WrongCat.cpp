#include "WrongCat.hpp"

WrongCat::WrongCat() {
	std::cout << "[WrongAnimal] Default constructor called" << std::endl;
	std::cout << "WrongCat constructed" << std::endl;
	this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
	std::cout << "[WrongAnimal] Copy constructor called" << std::endl;
	std::cout << "WrongCat copy constructed" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
	std::cout << "[WrongAnimal] Copy assignment operator called" << std::endl;
	std::cout << "WrongCat assigned" << std::endl;
	WrongAnimal::operator=(other);
	return *this;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructed" << std::endl;
	std::cout << "[WrongAnimal] Destructor called" << std::endl;
}

void WrongCat::makeSound() const {
	std::cout << "Meow? (but it's wrong...)" << std::endl;
}
