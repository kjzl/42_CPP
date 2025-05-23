#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
	int _fixedPointValue;
	static const int _fractionalBits = 8;

public:
	// Default constructor
	Fixed();

	// Copy constructor
	Fixed(const Fixed& other);

	// Copy assignment operator
	Fixed& operator=(const Fixed& other);

	// Destructor
	~Fixed();

	// Member functions
	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif // FIXED_HPP
