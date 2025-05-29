#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	std::cout << "----- Testing ClapTrap -----" << std::endl;
	ClapTrap clap("C1-4P");
	clap.attack("Enemy");
	clap.takeDamage(5);
	clap.beRepaired(3);
	std::cout << std::endl;

	std::cout << "----- Testing ScavTrap -----" << std::endl;
	ScavTrap scav("SC4V");
	scav.attack("Enemy");
	scav.takeDamage(30);
	scav.beRepaired(20);
	scav.guardGate();
	std::cout << std::endl;

	std::cout << "----- Testing FragTrap -----" << std::endl;
	FragTrap frag("FR4G");
	frag.attack("Enemy");
	frag.takeDamage(40);
	frag.beRepaired(25);
	frag.highFivesGuys();
	std::cout << std::endl;

	std::cout << "----- Testing Inheritance -----" << std::endl;
	// Polymorphism: ClapTrap pointer to derived objects
	ClapTrap* polyScav = new ScavTrap("POLY-SC4V");
	ClapTrap* polyFrag = new FragTrap("POLY-FR4G");

	polyScav->attack("Enemy");  // Should call ScavTrap's attack
	polyFrag->attack("Enemy");  // Should call FragTrap's attack

	delete polyScav;  // Should call ScavTrap's destructor first
	delete polyFrag;  // Should call FragTrap's destructor first
	std::cout << std::endl;

	std::cout << "----- Testing Construction/Destruction Order -----" << std::endl;
	{
		std::cout << "Creating a FragTrap:" << std::endl;
		FragTrap orderTest("ORDER-TEST");
		std::cout << "FragTrap created, now leaving scope..." << std::endl;
	}
	std::cout << "Scope ended, destructors should have been called in reverse order" << std::endl;
	std::cout << std::endl;

	std::cout << "----- Testing Energy and Damage -----" << std::endl;
	FragTrap energyTest("ENERGY-TEST");
	std::cout << "FragTrap attacking with " << energyTest.getAttackDamage() << " damage!" << std::endl;
	std::cout << "Remaining Energy: " << energyTest.getEnergyPoints() << std::endl;
	// Test a few attacks to show energy consumption
	for (int i = 0; i < 3; ++i) {
		std::cout << "Attack " << (i + 1) << ": ";
		energyTest.attack("Target");
	}
	std::cout << std::endl;
	std::cout << "Remaining Energy: " << energyTest.getEnergyPoints() << std::endl;

	return 0;
}
