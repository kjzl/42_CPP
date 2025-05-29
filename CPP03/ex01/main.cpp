#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

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

	std::cout << "----- Testing Inheritance -----" << std::endl;
	// Polymorphism: ClapTrap pointer to ScavTrap object
	ClapTrap* polyScav = new ScavTrap("P0LY");
	polyScav->attack("Enemy");  // Should call ScavTrap's attack
	polyScav->takeDamage(25);
	polyScav->beRepaired(10);
	// polyScav->guardGate();  // Won't work without casting
	delete polyScav;  // Should call ScavTrap's destructor first
	std::cout << std::endl;

	std::cout << "----- Testing Construction/Destruction Order -----" << std::endl;
	{
		std::cout << "Creating a ScavTrap:" << std::endl;
		ScavTrap orderTest("ORDER-TEST");
		std::cout << "ScavTrap created, now leaving scope..." << std::endl;
	}
	std::cout << "Scope ended, destructors should have been called in reverse order" << std::endl;
	std::cout << std::endl;

	std::cout << "----- Testing Energy Depletion -----" << std::endl;
	ScavTrap energyTest("ENERGY-TEST");
	std::cout << "Remaining Energy: " << energyTest.getEnergyPoints() << std::endl;
	// ScavTrap has 50 energy points
	for (int i = 0; i < 5; ++i) {
		std::cout << "Attack " << (i + 1) << ": ";
		energyTest.attack("Target");
	}
	std::cout << std::endl;

	std::cout << "Remaining Energy: " << energyTest.getEnergyPoints() << std::endl;

	return 0;
}
