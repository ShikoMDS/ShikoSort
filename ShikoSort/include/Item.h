/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : Item.h
Description : Declarations for item object related functions
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include <string>

enum class ItemType
{
	Weapon,
	Armor,
	Consumable,
	Utility
};

class Item final
{
public:
	explicit Item(std::string Name, ItemType Type, double Price, int Quantity);

	Item();
	~Item();

	// Mutators
	void setName(const std::string& Name);
	void setType(ItemType Type);
	void setPrice(double Price);
	void setQuantity(int Quantity);

	// Accessors
	[[nodiscard]] std::string getName() const;
	[[nodiscard]] ItemType getType() const;
	[[nodiscard]] double getPrice() const;
	[[nodiscard]] int getQuantity() const;
	

private:
	std::string MName;
	ItemType MType;
	double MPrice{};
	int MQuantity{};
};


// Item value handling