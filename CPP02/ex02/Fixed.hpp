#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
	int _fixedPointValue;
	static const int _fractionalBits = 8;

public:
	// Constructors and destructor
	Fixed();
	Fixed(const int intValue);
	Fixed(const float floatValue);
	Fixed(const Fixed& other);
	~Fixed();

	// Copy assignment operator
	Fixed& operator=(const Fixed& other);

	// Comparison operators
	bool operator>(const Fixed& rhs) const;
	bool operator<(const Fixed& rhs) const;
	bool operator>=(const Fixed& rhs) const;
	bool operator<=(const Fixed& rhs) const;
	bool operator==(const Fixed& rhs) const;
	bool operator!=(const Fixed& rhs) const;

	// Arithmetic operators
	Fixed operator+(const Fixed& rhs) const;
	Fixed operator-(const Fixed& rhs) const;
	Fixed operator*(const Fixed& rhs) const;
	Fixed operator/(const Fixed& rhs) const;

	// Increment/decrement operators
	Fixed& operator++();	// Pre-increment
	Fixed operator++(int);  // Post-increment
	Fixed& operator--();	// Pre-decrement
	Fixed operator--(int);  // Post-decrement

	// Member functions
	int getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;

	// Static member functions
	static Fixed& min(Fixed& a, Fixed& b);
	static const Fixed& min(const Fixed& a, const Fixed& b);
	static Fixed& max(Fixed& a, Fixed& b);
	static const Fixed& max(const Fixed& a, const Fixed& b);
};

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif // FIXED_HPP
