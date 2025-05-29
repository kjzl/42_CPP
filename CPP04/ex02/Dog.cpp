#include "Dog.hpp"

Dog::Dog() {
	std::cout << "[Dog] Default constructor called" << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "[Dog] Copy constructor called" << std::endl;
	this->brain = new Brain(*other.brain); // Deep copy
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "[Dog] Copy assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain); // Deep copy
	}
	return *this;
}

Dog::~Dog() {
	std::cout << "[Dog] Destructor called" << std::endl;
	delete this->brain;
}

void Dog::makeSound() const {
	std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain() const {
	return this->brain;
}
