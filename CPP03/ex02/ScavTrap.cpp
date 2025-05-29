#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	std::cout << "ScavTrap constructor called: " << this->_name << " is ready for action!" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap& other) {
	std::cout << "ScavTrap copy assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called: " << this->_name << " is shutting down!" << std::endl;
}

// Override attack method
void ScavTrap::attack(const std::string& target) {
	if (this->_energyPoints == 0) {
		std::cout << "ScavTrap " << this->_name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->_hitPoints == 0) {
		std::cout << "ScavTrap " << this->_name << " is out of hit points and cannot attack!" << std::endl;
		return;
	}

	std::cout << "ScavTrap " << this->_name << " aggressively attacks " << target << ", causing "
			  << this->_attackDamage << " points of damage!" << std::endl;
	this->_energyPoints--;
}

// Special ability
void ScavTrap::guardGate() {
	std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode!" << std::endl;
}
