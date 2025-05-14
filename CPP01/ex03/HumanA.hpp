#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
	private:
	std::string name;
	Weapon& weapon;  // Reference to Weapon since HumanA will always have a weapon

	public:
	HumanA(std::string name, Weapon& weapon);
	~HumanA();

	void attack() const;
};

#endif // HUMANA_HPP
