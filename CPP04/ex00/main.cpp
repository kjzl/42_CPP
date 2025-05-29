#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void separator(const std::string& title) {
	std::cout << "\n==== " << title << " ====\n" << std::endl;
}

int main() {
	separator("Basic Animal Polymorphism");
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "j->getType(): " << j->getType() << std::endl;
	std::cout << "i->getType(): " << i->getType() << std::endl;
	i->makeSound(); // Will output the cat sound!
	j->makeSound(); // Will output the dog sound!
	meta->makeSound(); // Will output the animal sound!

	delete meta;
	delete j;
	delete i;

	separator("WrongAnimal Polymorphism");
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();

	std::cout << "wrongCat->getType(): " << wrongCat->getType() << std::endl;
	wrongCat->makeSound(); // Should output WrongAnimal sound (not WrongCat)
	wrongMeta->makeSound();

	delete wrongMeta;
	delete wrongCat;

	separator("Direct WrongCat pointer");
	WrongCat* wc = new WrongCat();
	wc->makeSound(); // Should output WrongCat sound
	delete wc;

	separator("Copy and Assignment Tests");
	Dog dog1;
	Dog dog2 = dog1; // Copy constructor
	Dog dog3;
	dog3 = dog1;	 // Assignment operator

	Cat cat1;
	Cat cat2 = cat1; // Copy constructor
	Cat cat3;
	cat3 = cat1;	 // Assignment operator

	separator("WrongCat Copy and Assignment");
	WrongCat wcat1;
	WrongCat wcat2 = wcat1;
	WrongCat wcat3;
	wcat3 = wcat1;

	separator("Array of Animals (polymorphic)");
	const int N = 4;
	Animal* animals[N];
	for (int idx = 0; idx < N; ++idx) {
		if (idx % 2 == 0)
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

	separator("End of tests");
	return 0;
}
