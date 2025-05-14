#include "Zombie.hpp"
#include <iostream>

int main() {
	int hordeSize = 5;
	std::string zombieName = "Walker";

	std::cout << "Creating a horde of " << hordeSize << " zombies named " << zombieName << std::endl;

	// Create the zombie horde
	Zombie* horde = zombieHorde(hordeSize, zombieName);

	// Make each zombie announce itself
	for (int i = 0; i < hordeSize; i++) {
		std::cout << "Zombie #" << i + 1 << " announces: ";
		horde[i].announce();
	}

	// Clean up by deleting the zombie horde
	delete[] horde;

	std::cout << "All zombies have been destroyed." << std::endl;

	return 0;
}
