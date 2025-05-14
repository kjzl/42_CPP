#include "Contact.hpp"

// Default constructor
Contact::Contact() {
	// Initialize with empty strings
	this->firstName = "";
	this->lastName = "";
	this->nickname = "";
	this->phoneNumber = "";
	this->darkestSecret = "";
}

// Set all fields of a contact
void Contact::setContact(const std::string& firstName, const std::string& lastName,
				const std::string& nickname, const std::string& phoneNumber,
				const std::string& darkestSecret) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->nickname = nickname;
	this->phoneNumber = phoneNumber;
	this->darkestSecret = darkestSecret;
}

std::string Contact::getFirstName() const {
	return this->firstName;
}

std::string Contact::getLastName() const {
	return this->lastName;
}

std::string Contact::getNickname() const {
	return this->nickname;
}

std::string Contact::getPhoneNumber() const {
	return this->phoneNumber;
}

std::string Contact::getDarkestSecret() const {
	return this->darkestSecret;
}
