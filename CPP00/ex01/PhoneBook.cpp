#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <string>

// Constructor
PhoneBook::PhoneBook() {
	this->oldestIndex = 0;
	this->count = 0;
}

// Add a new contact to the phonebook
void PhoneBook::addContact(const Contact& contact) {
	// Add the contact at the current oldest index position
	this->contacts[this->oldestIndex] = contact;

	// Update the oldest index (circular buffer approach)
	this->oldestIndex = (this->oldestIndex + 1) % 8;

	// Update the total count of contacts (max 8)
	if (this->count < 8)
		this->count++;
}

// Format a string to fit in the display column (10 chars, right-aligned, truncated with .)
static std::string formatColumn(const std::string& str) {
	if (str.length() <= 10)
		return std::string(10 - str.length(), ' ') + str;
	return str.substr(0, 9) + ".";
}

// Display all contacts in a formatted list
void PhoneBook::displayContacts() const {
	std::cout << "|" << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	std::cout << "|----------+----------+----------+----------|" << std::endl;

	// Display each contact
	for (int i = 0; i < this->count; i++) {
		std::cout << "|" << std::setw(10) << i << "|";
		std::cout << formatColumn(this->contacts[i].getFirstName()) << "|";
		std::cout << formatColumn(this->contacts[i].getLastName()) << "|";
		std::cout << formatColumn(this->contacts[i].getNickname()) << "|" << std::endl;
	}
}

// Display a specific contact by index
bool PhoneBook::displayContact(int index) const {
	// Check if index is valid
	if (index < 0 || index >= this->count) {
		std::cout << "Error: Index out of range." << std::endl;
		return false;
	}

	// Display contact details
	std::cout << "First Name: " << this->contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << this->contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << this->contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << this->contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << this->contacts[index].getDarkestSecret() << std::endl;
	return true;
}

// Get the current number of contacts
int PhoneBook::getCount() const {
	return this->count;
}
