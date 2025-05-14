#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {
	private:
	std::string name;
	Weapon* weapon;  // Pointer to Weapon since HumanB might not always have a weapon

	public:
	HumanB(std::string name);
	~HumanB();

	void setWeapon(Weapon& weapon);
	void attack() const;
};

#endif // HUMANB_HPP
