#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
private:
	// Array of 8 contacts (maximum capacity)
	Contact contacts[8];
	// Index to keep track of the oldest contact for replacement
	int oldestIndex;
	// Current number of contacts stored
	int count;

public:
	// Constructor
	PhoneBook();

	// Add a new contact to the phonebook
	void addContact(const Contact& contact);

	// Display all contacts in a formatted list
	void displayContacts() const;

	// Display a specific contact by index
	bool displayContact(int index) const;

	// Get the current number of contacts
	int getCount() const;
};

#endif // PHONEBOOK_HPP
