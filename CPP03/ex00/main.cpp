#include <iostream>
#include "ClapTrap.hpp"

int main() {
	// Test default constructor
	ClapTrap defaultTrap;
	std::cout << "Default ClapTrap stats: " << defaultTrap.getName()
			  << " HP: " << defaultTrap.getHitPoints()
			  << " Energy: " << defaultTrap.getEnergyPoints()
			  << " Attack: " << defaultTrap.getAttackDamage() << std::endl;
	std::cout << std::endl;

	// Test named constructor
	ClapTrap ct1("CT-137");
	ClapTrap ct2("CT-249");
	std::cout << std::endl;

	// Test copy constructor and assignment operator
	ClapTrap ct3(ct1);  // Copy constructor
	ClapTrap ct4 = ct2; // Copy assignment operator
	std::cout << std::endl;

	// Test attack functionality
	ct1.attack("Enemy Bot");
	ct1.attack("Enemy Bot");
	std::cout << std::endl;

	// Test damage functionality
	ct1.takeDamage(3);
	ct1.takeDamage(4);
	ct1.takeDamage(5); // Should be knocked out (0 HP)
	ct1.takeDamage(1); // Already at 0 HP
	std::cout << std::endl;

	// Test repair functionality
	ct2.beRepaired(2);
	ct2.attack("Enemy Bot");
	std::cout << std::endl;

	// Test energy depletion
	for (int i = 0; i < 9; ++i) {
		ct2.attack("Enemy Bot");
	}
	ct2.attack("Enemy Bot"); // No energy left
	ct2.beRepaired(5);	   // No energy left
	std::cout << std::endl;

	// Destructors will be called automatically when main exits
	return 0;
}
