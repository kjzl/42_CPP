#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
public:
	// Constructors and destructor
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	virtual ~Dog();

	// Override the makeSound method
	virtual void makeSound() const;
};

#endif // DOG_HPP
