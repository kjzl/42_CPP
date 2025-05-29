#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

void separator(const std::string& title) {
	std::cout << "\n==== " << title << " ====\n" << std::endl;
}

int main() {
	separator("Abstract Animal Test");

	// Animal a; // This should not compile: Animal is abstract

	Dog dog1;
	Cat cat1;

	dog1.makeSound();
	cat1.makeSound();

	separator("Polymorphic Array Test");

	const int N = 4;
	Animal* animals[N];
	for (int i = 0; i < N; ++i) {
		if (i % 2 == 0)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < N; ++i) {
		std::cout << "Animal[" << i << "] type: " << animals[i]->getType() << " - ";
		animals[i]->makeSound();
	}
	for (int i = 0; i < N; ++i)
		delete animals[i];

	separator("Copy and Assignment Test");

	Dog d1;
	d1.makeSound();
	Dog d2 = d1; // Copy constructor
	d2.makeSound();
	Dog d3;
	d3 = d1; // Assignment operator
	d3.makeSound();

	Cat c1;
	c1.makeSound();
	Cat c2 = c1; // Copy constructor
	c2.makeSound();
	Cat c3;
	c3 = c1; // Assignment operator
	c3.makeSound();

	separator("Deep Copy Test");

	Dog originalDog;
	originalDog.getBrain()->setIdea(0, "I love bones");

	Dog copiedDog = originalDog;
	std::cout << "Original dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied dog idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

	copiedDog.getBrain()->setIdea(0, "I love sleeping");
	std::cout << "After changing copied dog's idea:" << std::endl;
	std::cout << "Original dog idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied dog idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

	separator("End of tests");
	return 0;
}
