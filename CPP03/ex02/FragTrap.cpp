#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "FragTrap default constructor called" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "FragTrap constructor called: " << this->_name << " is ready for fragmentation!" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor called: " << this->_name << " is shutting down!" << std::endl;
}

// Override attack method
void FragTrap::attack(const std::string& target) {
	if (this->_energyPoints == 0) {
		std::cout << "FragTrap " << this->_name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->_hitPoints == 0) {
		std::cout << "FragTrap " << this->_name << " is out of hit points and cannot attack!" << std::endl;
		return;
	}

	std::cout << "FragTrap " << this->_name << " unleashes devastation on " << target << ", causing "
			  << this->_attackDamage << " points of damage!" << std::endl;
	this->_energyPoints--;
}

// Special ability
void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << this->_name << " requests high fives from everyone!" << std::endl;
}
