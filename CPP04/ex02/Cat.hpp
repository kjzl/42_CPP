#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
private:
	Brain* brain;

public:
	// Constructors and destructor
	Cat();
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);
	virtual ~Cat();

	// Override the makeSound method
	virtual void makeSound() const;

	// Access to brain
	Brain* getBrain() const;
};

#endif // CAT_HPP
