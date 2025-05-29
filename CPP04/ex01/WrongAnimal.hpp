#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
protected:
	std::string type;

public:
	// Constructors and destructor
	WrongAnimal();
	WrongAnimal(const WrongAnimal& other);
	WrongAnimal& operator=(const WrongAnimal& other);
	~WrongAnimal();

	// Getter for type
	std::string getType() const;

	// Make sound method - NOT virtual, so no polymorphism
	void makeSound() const;
};

#endif // WRONGANIMAL_HPP
