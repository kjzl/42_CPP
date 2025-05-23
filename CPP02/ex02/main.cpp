#include <iostream>
#include "Fixed.hpp"

int main(void) {
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;

	// Additional tests for all operators
	std::cout << "\n--- Additional Tests ---\n" << std::endl;

	// Arithmetic operators
	Fixed c(10);
	Fixed d(4);

	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "c + d = " << (c + d) << std::endl;
	std::cout << "c - d = " << (c - d) << std::endl;
	std::cout << "c * d = " << (c * d) << std::endl;
	std::cout << "c / d = " << (c / d) << std::endl;

	// Comparison operators
	std::cout << "\nComparison operations:" << std::endl;
	std::cout << "c > d: " << (c > d) << std::endl;
	std::cout << "c < d: " << (c < d) << std::endl;
	std::cout << "c >= d: " << (c >= d) << std::endl;
	std::cout << "c <= d: " << (c <= d) << std::endl;
	std::cout << "c == d: " << (c == d) << std::endl;
	std::cout << "c != d: " << (c != d) << std::endl;

	// Decrement operators
	Fixed e(1);
	std::cout << "\nDecrement operations with e = " << e << ":" << std::endl;
	std::cout << "--e: " << --e << std::endl;
	std::cout << "e: " << e << std::endl;
	std::cout << "e--: " << e-- << std::endl;
	std::cout << "e: " << e << std::endl;

	// Min/Max functions
	Fixed f(42.42f);
	Fixed g(42.0f);

	std::cout << "\nMin/Max functions:" << std::endl;
	std::cout << "f = " << f << ", g = " << g << std::endl;
	std::cout << "min(f, g): " << Fixed::min(f, g) << std::endl;
	std::cout << "max(f, g): " << Fixed::max(f, g) << std::endl;

	return 0;
}
