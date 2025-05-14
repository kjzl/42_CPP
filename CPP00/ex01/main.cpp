#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

// get a non-empty input string from user
std::string getInput(const std::string& prompt) {
	std::string input;

	while (true) {
		std::cout << prompt;
		std::getline(std::cin, input);

		// Check for EOF or input error
		if (!std::cin.good()) {
			std::cout << "\nInput error. Exiting program." << std::endl;
			exit(1);
		}

		// Check if input is empty
		if (input.empty()) {
			std::cout << "Error: field cannot be empty. Please try again." << std::endl;
		} else {
			return input;  // Return valid input
		}
	}
}

void addNewContact(PhoneBook& phoneBook) {
	Contact newContact;
	std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

	// Get contact information from user
	firstName = getInput("Enter first name: ");
	lastName = getInput("Enter last name: ");
	nickname = getInput("Enter nickname: ");
	phoneNumber = getInput("Enter phone number: ");
	darkestSecret = getInput("Enter darkest secret: ");

	newContact.setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
	phoneBook.addContact(newContact);
	std::cout << "Contact added successfully!" << std::endl;
}

// Function to search and display a contact
void searchContact(const PhoneBook& phoneBook) {
	int index;

	if (phoneBook.getCount() == 0) {
		std::cout << "Phonebook is empty. Add some contacts first." << std::endl;
		return;
	}

	phoneBook.displayContacts();

	// Get index from user
	while (true) {
		std::cout << "Enter the index of the contact to display: ";
		if (!(std::cin >> index)) {
			// Input is not a number
			std::cout << "Error: Invalid input. Please enter a number." << std::endl;
			std::cin.clear(); // Clear error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip bad input
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

		// Try to display the contact at given index
		if (phoneBook.displayContact(index)) {
			break;  // Success, exit loop
		}
		// If displayContact returns false, it will have already printed an error message
	}
}

int main() {
	PhoneBook phoneBook;
	std::string command;

	std::cout << "===== My Awesome PhoneBook =====" << std::endl;

	while (true) {
		std::cout << "\nEnter a command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, command);

		// Check for EOF or input error
		if (!std::cin.good()) {
			std::cout << "\nInput error. Exiting program." << std::endl;
			break;
		}

		// Process command
		if (command == "ADD") {
			addNewContact(phoneBook);
		} else if (command == "SEARCH") {
			searchContact(phoneBook);
		} else if (command == "EXIT") {
			std::cout << "Goodbye!" << std::endl;
			break;
		} else {
			std::cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << std::endl;
		}
	}

	return 0;
}
