#include "ClapTrap.hpp"
#include <iostream>

// Default constructor
ClapTrap::ClapTrap() : _name("Unnamed"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

// Name constructor
ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap constructor called: " << this->_name << " is ready!" << std::endl;
}

// Copy constructor
ClapTrap::ClapTrap(const ClapTrap& other) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = other;
}

// Copy assignment operator
ClapTrap &ClapTrap::operator=(const ClapTrap& other) {
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &other) {
		this->_name = other._name;
		this->_hitPoints = other._hitPoints;
		this->_energyPoints = other._energyPoints;
		this->_attackDamage = other._attackDamage;
	}
	return *this;
}

// Destructor
ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called: " << this->_name << " is no more!" << std::endl;
}

// Member function: attack
void ClapTrap::attack(const std::string& target) {
	if (this->_energyPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " has no energy points left to attack!" << std::endl;
		return;
	}
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " is out of hit points and cannot attack!" << std::endl;
		return;
	}

	std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing "
			  << this->_attackDamage << " points of damage!" << std::endl;
	this->_energyPoints--;
}

// Member function: takeDamage
void ClapTrap::takeDamage(unsigned int amount) {
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " is already out of hit points!" << std::endl;
		return;
	}

	if (amount >= this->_hitPoints) {
		this->_hitPoints = 0;
		std::cout << "ClapTrap " << this->_name << " takes " << amount << " damage and is knocked out!" << std::endl;
	} else {
		this->_hitPoints -= amount;
		std::cout << "ClapTrap " << this->_name << " takes " << amount << " damage, reducing hit points to "
				  << this->_hitPoints << "!" << std::endl;
	}
}

// Member function: beRepaired
void ClapTrap::beRepaired(unsigned int amount) {
	if (this->_energyPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " has no energy points left to repair itself!" << std::endl;
		return;
	}
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " is out of hit points and cannot repair itself!" << std::endl;
		return;
	}

	this->_hitPoints += amount;
	std::cout << "ClapTrap " << this->_name << " repairs itself, gaining " << amount << " hit points. Now has "
			  << this->_hitPoints << " hit points!" << std::endl;
	this->_energyPoints--;
}

// Getters
std::string ClapTrap::getName() const {
	return this->_name;
}

unsigned int ClapTrap::getHitPoints() const {
	return this->_hitPoints;
}

unsigned int ClapTrap::getEnergyPoints() const {
	return this->_energyPoints;
}

unsigned int ClapTrap::getAttackDamage() const {
	return this->_attackDamage;
}
