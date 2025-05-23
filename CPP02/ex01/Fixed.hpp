#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
	int _fixedPointValue;
	static const int _fractionalBits = 8;

public:
	// Default constructor
	Fixed();

	// Int constructor
	Fixed(const int intValue);

	// Float constructor
	Fixed(const float floatValue);

	// Copy constructor
	Fixed(const Fixed& other);

	// Copy assignment operator
	Fixed& operator=(const Fixed& other);

	// Destructor
	~Fixed();

	// Member functions
	int getRawBits(void) const;
	void setRawBits(int const raw);

	// Conversion functions
	float toFloat(void) const;
	int toInt(void) const;
};

// Stream insertion operator overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif // FIXED_HPP
