#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
public:
	// Constructors and destructor
	Cat();
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);
	virtual ~Cat();

	// Override the makeSound method
	virtual void makeSound() const;
};

#endif // CAT_HPP
