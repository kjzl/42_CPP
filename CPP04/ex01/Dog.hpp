#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
private:
	Brain* brain;

public:
	// Constructors and destructor
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	virtual ~Dog();

	// Override the makeSound method
	virtual void makeSound() const;

	// Access to brain
	Brain* getBrain() const;
};

#endif // DOG_HPP
