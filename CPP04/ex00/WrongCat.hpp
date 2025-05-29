#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
	// Constructors and destructor
	WrongCat();
	WrongCat(const WrongCat& other);
	WrongCat& operator=(const WrongCat& other);
	~WrongCat();

	// This method is NOT virtual in the base class
	// so even if we override it here, it won't be called polymorphically
	void makeSound() const;
};

#endif // WRONGCAT_HPP
