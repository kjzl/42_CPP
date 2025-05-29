#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain {
private:
	std::string ideas[100];

public:
	// Constructors and destructor
	Brain();
	Brain(const Brain& other);
	Brain& operator=(const Brain& other);
	~Brain();

	// Methods to get and set ideas
	std::string getIdea(int index) const;
	void setIdea(int index, const std::string& idea);
};

#endif // BRAIN_HPP
