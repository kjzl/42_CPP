#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

void separator(const std::string& title) {
	std::cout << "\n==== " << title << " ====\n" << std::endl;
}

int main() {
	separator("Basic Deep Copy and Memory Leak Test");

	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j; // should not leak
	delete i;

	separator("Array of Animals (polymorphic, half Dog, half Cat)");

	const int N = 10;
	Animal* animals[N];
	for (int idx = 0; idx < N; ++idx) {
		if (idx < N / 2)
			animals[idx] = new Dog();
		else
			animals[idx] = new Cat();
	}
	for (int idx = 0; idx < N; ++idx) {
		std::cout << "Animal[" << idx << "] type: " << animals[idx]->getType() << " - ";
		animals[idx]->makeSound();
	}
	for (int idx = 0; idx < N; ++idx)
		delete animals[idx];

	separator("Deep Copy Test for Dog");

	Dog basicDog;
	basicDog.getBrain()->setIdea(0, "Chase the cat!");
	basicDog.getBrain()->setIdea(1, "Eat food!");
	Dog copyDog = basicDog; // Copy constructor
	std::cout << "basicDog idea[0]: " << basicDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "copyDog idea[0]: " << copyDog.getBrain()->getIdea(0) << std::endl;
	copyDog.getBrain()->setIdea(0, "Sleep all day.");
	std::cout << "After modifying copyDog's brain:" << std::endl;
	std::cout << "basicDog idea[0]: " << basicDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "copyDog idea[0]: " << copyDog.getBrain()->getIdea(0) << std::endl;

	separator("Deep Copy Test for Cat");

	Cat basicCat;
	basicCat.getBrain()->setIdea(0, "Ignore humans.");
	Cat assignCat;
	assignCat = basicCat; // Assignment operator
	std::cout << "basicCat idea[0]: " << basicCat.getBrain()->getIdea(0) << std::endl;
	std::cout << "assignCat idea[0]: " << assignCat.getBrain()->getIdea(0) << std::endl;
	assignCat.getBrain()->setIdea(0, "Knock things off table.");
	std::cout << "After modifying assignCat's brain:" << std::endl;
	std::cout << "basicCat idea[0]: " << basicCat.getBrain()->getIdea(0) << std::endl;
	std::cout << "assignCat idea[0]: " << assignCat.getBrain()->getIdea(0) << std::endl;

	separator("End of tests");
	return 0;
}
