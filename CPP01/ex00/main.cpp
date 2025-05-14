#include "Zombie.hpp"
#include <iostream>

int main() {
	// Test creating a zombie on the stack
	std::cout << "Creating a Zombie on the stack:" << std::endl;
	Zombie stackZombie("StackZombie");
	stackZombie.announce();
	// Zombie on stack will be automatically destroyed at end of scope

	// Test creating a zombie on the heap using newZombie
	std::cout << "\nCreating a Zombie on the heap:" << std::endl;
	Zombie* heapZombie = newZombie("HeapZombie");
	heapZombie->announce();

	// Clean up the heap-allocated zombie
	delete heapZombie;

	// Test random chump function that creates a zombie locally
	std::cout << "\nTesting randomChump function:" << std::endl;
	randomChump("RandomZombie");

	return 0;
}
