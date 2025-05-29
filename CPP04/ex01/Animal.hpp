#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
protected:
	std::string type;

public:
	// Constructors and destructor
	Animal();
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);
	virtual ~Animal();

	// Getter for type
	std::string getType() const;

	// Make sound method - virtual to enable polymorphism
	virtual void makeSound() const;
};

#endif // ANIMAL_HPP
