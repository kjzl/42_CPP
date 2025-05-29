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

	// Pure virtual function makes this class abstract
	virtual void makeSound() const = 0;
};

#endif // ANIMAL_HPP
