/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : Item.cpp
Description : Implementations for item declarations
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Item.h"

#include <sstream>
#include <utility>

Item::Item(std::string Name, const ItemType Type, const double Price, const int Quantity)
{
	MName = std::move(Name);
	MType = Type;
	MPrice = Price;
	MQuantity = Quantity;
}

Item::Item() : MType(ItemType::Weapon), MPrice(0.0) {}


Item::~Item() = default;


// Mutators
void Item::setName(const std::string& Name)
{
	MName = Name;
}

void Item::setType(const ItemType Type)
{
	MType = Type;
}

void Item::setPrice(const double Price)
{
	MPrice = Price;
}

void Item::setQuantity(const int Quantity)
{
	MQuantity = Quantity;
}


// Accessors
std::string Item::getName() const
{
	return MName;
}

ItemType Item::getType() const
{
	return MType;
}

double Item::getPrice() const
{
	return MPrice;
}

int Item::getQuantity() const
{
	return MQuantity;
}


// Item values are handled here
