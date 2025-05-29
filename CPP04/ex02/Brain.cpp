#include "Brain.hpp"

Brain::Brain() {
	std::cout << "[Brain] Default constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = "";
	}
}

Brain::Brain(const Brain& other) {
	std::cout << "[Brain] Copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = other.ideas[i];
	}
}

Brain& Brain::operator=(const Brain& other) {
	std::cout << "[Brain] Copy assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			this->ideas[i] = other.ideas[i];
		}
	}
	return *this;
}

Brain::~Brain() {
	std::cout << "[Brain] Destructor called" << std::endl;
}

std::string Brain::getIdea(int index) const {
	if (index >= 0 && index < 100) {
		return this->ideas[index];
	}
	return "Invalid idea index";
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < 100) {
		this->ideas[index] = idea;
	} else {
		std::cout << "Error: Idea index out of bounds" << std::endl;
	}
}
