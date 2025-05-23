#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _fixedPointValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int intValue) {
	std::cout << "Int constructor called" << std::endl;
	this->_fixedPointValue = intValue << this->_fractionalBits;
}

Fixed::Fixed(const float floatValue) {
	std::cout << "Float constructor called" << std::endl;
	// Float to fixed-point: multiply by 2^_fractionalBits and round
	this->_fixedPointValue = static_cast<int>(roundf(floatValue * (1 << this->_fractionalBits)));
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		this->_fixedPointValue = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
	return this->_fixedPointValue;
}

void Fixed::setRawBits(int const raw) {
	this->_fixedPointValue = static_cast<int>(raw);
}

float Fixed::toFloat(void) const {
	// divide by 2^_fractionalBits
	return static_cast<float>(this->_fixedPointValue) / static_cast<float>(1 << this->_fractionalBits);
}

int Fixed::toInt(void) const {
	// shift right by _fractionalBits (truncates fractional part)
	return this->_fixedPointValue >> this->_fractionalBits;
}

// Stream insertion operator overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}
