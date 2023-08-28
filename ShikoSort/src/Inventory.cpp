/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name :
Description :
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Inventory.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "IoFile.h"

Inventory::Node::Node(const Item& NewItem, Node* NextItem, Node* PrevItem)
{
	Data = NewItem;
	Previous = PrevItem;
	Next = NextItem;
}

Inventory::Inventory()
{
	MHead = nullptr;
	MTail = nullptr;
	MSize = 0;
}

Inventory::~Inventory()
{
	// Destructor deletes all nodes to prevent memory leaks
	// Delete from the front and pass through to next front
	const Node* Select = MHead; // Sets the deletion to head of list
	while (Select != nullptr) // Runs through the list until all are deleted and head points to null
	{
		const Node* ToDelete = Select; // Stores current head to ToDelete variable
		Select = Select->Next; // Passes next item as the next head before deleting 
		delete ToDelete; // Deletes stored variable to remove the head and allows the passed item to be the next head
	}
}

std::string Inventory::itemTypeToString(const ItemType Type)
{
	switch (Type)
	{
	case ItemType::Weapon:
		return "Weapon";
	case ItemType::Armor:
		return "Armor";
	case ItemType::Consumable:
		return "Consumable";
	case ItemType::Utility:
		return "Utility";
	}
	return {};
}

void Inventory::loadFile(const std::string& Filename)
{
	auto StringToEnum = [](const std::string& TypeStr) -> ItemType
	{
		if (TypeStr == "Weapon")
			return ItemType::Weapon;
		if (TypeStr == "Armor")
			return ItemType::Armor;
		if (TypeStr == "Consumable")
			return ItemType::Consumable;
		if (TypeStr == "Utility")
			return ItemType::Utility;

		throw std::runtime_error("Invalid item type " + TypeStr + ". Item not loaded.");
	};

	if (!Filename.empty())
	{
		if (std::ifstream File(Filename); File.is_open())
		{
			std::string Line;
			std::getline(File, Line); // Skip the header line
			while (std::getline(File, Line))
			{
				// Check if the line is blank
				bool isBlank = true;
				for (const char Character : Line)
				{
					if (Character != ' ')
					{
						isBlank = false;
						break;
					}
				}

				if (!isBlank) // If line has values
				{
					// "//" delimiters are parsed to find line segments
					const size_t Pos0 = Line.find("//", 0); // Finds first "//" - (Name) > First position (1) < (2)
					const size_t Pos1 = Line.find("//", Pos0 + 1);
					// Finds second "//" - (Type) > Second position (2) < (3)
					const size_t Pos2 = Line.find("//", Pos1 + 1);
					// Finds third "//" - (Price) > Third Position (3) < (Quantity)

					// Check if all delimiter positions are true, sets to npos (not found) if not found
					if (Pos0 != std::string::npos && Pos1 != std::string::npos && Pos2 != std::string::npos)
					{
						std::string Name = Line.substr(0, Pos0 - 1); // Takes substring before first delimiter
						std::string Type = Line.substr(Pos0 + 3, Pos1 - Pos0 - 4);
						// Takes substring between first and second delimiter 
						const double Price = std::stod(Line.substr(Pos1 + 3, Pos2 - Pos1 - 4));
						// Takes substring between second and third delimiter 
						const int Quantity = std::stoi(Line.substr(Pos2 + 3)); // Takes substring after third delimiter

						try
						{
							StringToEnum(Type);
							// Duplicate item name check - can't have duplicate items by name   
							if (!itemExists(Name))
							{
								Item NewItem(Name, StringToEnum(Type), Price, Quantity);
								addFileItem(NewItem);
							}
							else
							{
								std::cerr << "Item duplicate found, already exists! Item not loaded.\n";
							}
						}
						catch (const std::exception& E)
						{
							std::cerr << E.what() << std::endl;
						}
					}
					// Line values invalid
					else
					{
						std::cerr << "Error parsing line: " << Line << " - Item not loaded." << std::endl;
					}
				}
			}
			File.close();
		}
		else
		{
			std::cerr << "Error: Unable to open file." << std::endl;
		}
	}
}

void Inventory::saveFile(const std::string& FileName) const
{
	if (std::ofstream File(FileName); File.is_open()) // Fixed variable name
	{
		File << "NAME // TYPE // PRICE // QUANTITY\n";

		const Node* CurrentNode = getHead(); // Assuming Node is a nested class within Inventory
		while (CurrentNode)
		{
			const Item& CurrentItem = CurrentNode->Data;
			File << CurrentItem.getName() << " // "
				<< itemTypeToString(CurrentItem.getType()) << " // "
				<< CurrentItem.getPrice() << " // "
				<< CurrentItem.getQuantity() << "\n";

			CurrentNode = CurrentNode->Next;
		}

		File.close();
		std::cout << "Items saved to " << FileName << std::endl; // Fixed variable name
	}
	else
	{
		std::cerr << "Error: Unable to open file for writing." << std::endl;
	}
}

void Inventory::displayInventory() const
{
	if (MSize == 0)
	{
		std::cout << "\nInventory is empty." << std::endl;
		return;
	}

	const Node* CurrentNode = MHead;
	size_t Index = 0;
	while (CurrentNode)
	{
		const Item& CurrentItem = CurrentNode->Data;
		std::cout << "Item " << Index + 1 << ":\n";
		std::cout << "Name: " << CurrentItem.getName() << "\n";
		std::cout << "Type: " << itemTypeToString(CurrentItem.getType()) << "\n";
		std::cout << "Price: $" << CurrentItem.getPrice() << "\n";
		std::cout << "Quantity: " << CurrentItem.getQuantity() << "\n\n";

		CurrentNode = CurrentNode->Next;
		Index++;
	}
}

Inventory::Node* Inventory::findItem(const std::string& Name) const
{
	Node* Select = MHead; // Start at the head to run through the list

	while (Select)
	{
		if (Select->Data.getName() == Name)
		{
			return Select; // Return the memory address of the found node
		}
		Select = Select->Next; // Pass through next item
	}

	return nullptr; // End of list - item by name not found
}

bool Inventory::itemExists(const std::string& Name) const
{
	return findItem(Name) != nullptr; // If name exists, return true
}

void Inventory::addFileItem(const Item& NewItem)
{
	// Check if an item with the same name already exists
	if (itemExists(NewItem.getName()))
	{
		std::cout << "An item with the same name already exists. Item not loaded." << std::endl;
		return;
	}

	// Create a new Node to hold the Item and set its pointers
	const auto NewNode = new Node(NewItem, nullptr, MTail);

	if (MTail) // Sends the new node to end of list
	{
		MTail->Next = NewNode;
	}
	else
	{
		MHead = NewNode; // If the list was empty, set the head to the new node
	}

	MTail = NewNode; // Update the tail to the new node

	MSize++; // Increment the size of the inventory

	std::cout << "Item added to inventory." << std::endl;
}

void Inventory::addItem(const Item& NewItem)
{
	// Check if an item with the same name already exists
	if (itemExists(NewItem.getName()))
	{
		std::cout << "An item with the same name already exists. Item not loaded." << std::endl;
		return;
	}

	// Create a new Node to hold the Item and set its pointers
	const auto NewNode = new Node(NewItem, nullptr, nullptr);

	int Choice; // Declare index here
	std::cout << "Where would you like to add this item into the list? (Enter -1 to add to the end): ";
	std::cin >> Choice;

	// Adjust index to zero-based for internal list representation
	Choice--;

	if (!MHead && Choice + 1 == -1 || Choice + 1 == 1) // If the list is empty, set both head and tail to the new node
	{
		MHead = NewNode;
		MTail = NewNode;
		MSize++;
		if (Choice + 1 == 1)
		{
			std::cout << "Item has been added at index 1." << std::endl;
		}
		else
		{
			std::cout << "Inventory was empty. New item has been at index 1." << std::endl;
		}
	}
	else if (Choice >= 1 && Choice <= MSize)
	{
		Node* CurrentNode = MHead;
		for (int I = 0; CurrentNode && I < Choice; ++I)
		{
			CurrentNode = CurrentNode->Next;
		}

		if (CurrentNode)
		{
			NewNode->Previous = CurrentNode->Previous;
			NewNode->Next = CurrentNode;
			if (CurrentNode->Previous)
			{
				CurrentNode->Previous->Next = NewNode;
			}
			else
			{
				MHead = NewNode;
			}
			CurrentNode->Previous = NewNode;

			MSize++; // Increment the size of the inventory
			std::cout << "Item added to inventory at item No. " << (Choice == -1 ? MSize : Choice + 1) << "." << std::endl;
		}
		else
		{
			std::cout << "Invalid index. Item was not added." << std::endl;
			delete NewNode;
		}
	}
	else if (Choice + 1 == -1)
	{
		// Check if an item with the same name already exists
		if (itemExists(NewItem.getName()))
		{
			std::cout << "An item with the same name already exists." << std::endl;
			return;
		}

		// Create a new Node to hold the Item and set its pointers
		const auto NewNode = new Node(NewItem, nullptr, MTail);

		if (MTail) // Sends the new node to end of list
			{
			MTail->Next = NewNode;
			}
		else
		{
			MHead = NewNode; // If the list was empty, set the head to the new node
		}

		MTail = NewNode; // Update the tail to the new node

		MSize++; // Increment the size of the inventory
		std::cout << "Item added to back of inventory." << std::endl;
	}
	else // Invalid index
	{
		std::cout << "Invalid index. Item was not added." << std::endl;
		delete NewNode;
	}
}

void Inventory::removeItem(const size_t Index)
{
	if (Index >= MSize)
	{
		std::cout << "Invalid index. Item does not exist." << std::endl;
		return;
	}

	// Traverse the list to find the node at the specified index
	const Node* CurrentItem = MHead;
	for (size_t I = 0; I < Index && CurrentItem; ++I)
	{
		CurrentItem = CurrentItem->Next;
	}

	if (!CurrentItem)
	{
		std::cout << "Item not found in the inventory." << std::endl;
		return;
	}

	// Update Next and Previous pointers of neighboring nodes
	if (CurrentItem->Previous)
	{
		CurrentItem->Previous->Next = CurrentItem->Next;
	}
	else
	{
		MHead = CurrentItem->Next; // Update head if removing the first node
	}

	if (CurrentItem->Next)
	{
		CurrentItem->Next->Previous = CurrentItem->Previous;
	}
	else
	{
		MTail = CurrentItem->Previous; // Update tail if removing the last node
	}

	delete CurrentItem; // Free memory

	MSize--; // Decrement the size of the inventory

	// Check if the last item was removed
	if (MSize == 0)
	{
		MHead = nullptr;
		MTail = nullptr;
	}

	std::cout << "Item removed from inventory." << std::endl;
}

void Inventory::accessItem(const size_t Index, Item& NewItem) const
{
	if (Index >= MSize)
	{
		std::cout << "Invalid index. Item does not exist." << std::endl;
		return;
	}

	// Traverse the list to find the node at the specified index
	Node* CurrentItem = MHead;
	for (size_t I = 0; I < Index && CurrentItem; ++I)
	{
		CurrentItem = CurrentItem->Next;
	}

	if (!CurrentItem)
	{
		std::cout << "Item not found in the inventory." << std::endl;
		return;
	}

	// Prompt user for updated item properties
	std::string NewName;
	int TypeInput;
	double NewPrice;
	int NewQuantity;

	std::cout << "Enter the new name for the item: ";
	std::cin >> NewName;

	// Similar prompts for other properties (type, price, quantity)
	// For example:
	std::cout << "Enter the new type for the item (0-Weapon, 1-Armor, 2-Consumable, 3-Utility): ";
	std::cin >> TypeInput;
	const auto NewType = static_cast<ItemType>(TypeInput);

	std::cout << "Enter the new price for the item: ";
	std::cin >> NewPrice;

	std::cout << "Enter the new quantity for the item: ";
	std::cin >> NewQuantity;

	// Update the item's properties
	NewItem.setName(NewName);
	NewItem.setType(NewType);
	NewItem.setPrice(NewPrice);
	NewItem.setQuantity(NewQuantity);

	// Update the properties of the item in the linked list node
	CurrentItem->Data = NewItem;

	std::cout << "Item updated successfully." << std::endl;
}

void Inventory::clearInventory()
{
	const Node* Current = MHead;
	while (Current)
	{
		const Node* Temp = Current;
		Current = Current->Next;
		delete Temp;
	}
	MHead = nullptr;
	MTail = nullptr;
	MSize = 0;
}

void Inventory::quickSortByName(const bool Ascending)
{
	quickSortByNameRecursive(MHead, MTail, Ascending);
}

void Inventory::quickSortByType(const bool Ascending)
{
	quickSortByTypeRecursive(MHead, MTail, Ascending);
}

void Inventory::quickSortByPrice(const bool Ascending)
{
	quickSortByPriceRecursive(MHead, MTail, Ascending);
}

void Inventory::quickSortByQuantity(const bool Ascending)
{
	quickSortByQuantityRecursive(MHead, MTail, Ascending);
}

Inventory::Node* Inventory::getHead() const
{
	return MHead;
}

Inventory::Node* Inventory::getTail() const
{
	return MTail;
}

size_t Inventory::getSize() const
{
	return MSize;
}

// Whole sorting system should be done here

void Inventory::quickSortByNameRecursive(Node* Left, Node* Right, const bool Ascending)
{
	if (Left && Right && Left != Right && Left != Right->Next)
	{
		const Node* Pivot = partitionByName(Left, Right, Ascending);
		quickSortByNameRecursive(Left, Pivot->Previous, Ascending);
		quickSortByNameRecursive(Pivot->Next, Right, Ascending);
	}
}

void Inventory::quickSortByTypeRecursive(Node* Left, Node* Right, const bool Ascending)
{
	if (Left && Right && Left != Right && Left != Right->Next)
	{
		const Node* Pivot = partitionByType(Left, Right, Ascending);
		quickSortByTypeRecursive(Left, Pivot->Previous, Ascending);
		quickSortByTypeRecursive(Pivot->Next, Right, Ascending);
	}
}

void Inventory::quickSortByPriceRecursive(Node* Left, Node* Right, const bool Ascending)
{
	if (Left && Right && Left != Right && Left != Right->Next)
	{
		const Node* Pivot = partitionByPrice(Left, Right, Ascending);
		quickSortByPriceRecursive(Left, Pivot->Previous, Ascending);
		quickSortByPriceRecursive(Pivot->Next, Right, Ascending);
	}
}

void Inventory::quickSortByQuantityRecursive(Node* Left, Node* Right, const bool Ascending)
{
	if (Left && Right && Left != Right && Left != Right->Next)
	{
		const Node* Pivot = partitionByQuantity(Left, Right, Ascending);
		quickSortByQuantityRecursive(Left, Pivot->Previous, Ascending);
		quickSortByQuantityRecursive(Pivot->Next, Right, Ascending);
	}
}

Inventory::Node* Inventory::partitionByName(Node* Left, Node* Right, const bool Ascending) const
{
	const std::string& PivotName = Right->Data.getName();
	Node* I = Left->Previous;

	for (Node* J = Left; J != Right && J != nullptr; J = J->Next)
	{
		if ((Ascending && J->Data.getName() <= PivotName) || (!Ascending && J->Data.getName() >= PivotName))
		{
			I = (I == nullptr) ? Left : I->Next;
			if (I != nullptr)
			{
				std::swap(I->Data, J->Data);
			}
		}
	}

	if (I != nullptr)
	{
		I = I->Next;
		if (I != nullptr)
		{
			std::swap(I->Data, Right->Data);
		}
	}
	return I;
}

static std::unordered_map<ItemType, std::string> ItemTypeToString =
{
	{ItemType::Weapon, "Weapon"},
	{ItemType::Armor, "Armor"},
	{ItemType::Consumable, "Consumable"},
	{ItemType::Utility, "Utility"}
};

Inventory::Node* Inventory::partitionByType(Node* Left, Node* Right, const bool Ascending) const
{
	const std::string& PivotTypeStr = ItemTypeToString[Right->Data.getType()];
	Node* I = Left->Previous;

	for (Node* J = Left; J != Right && J != nullptr; J = J->Next)
	{
		if (const std::string& JTypeStr = ItemTypeToString[J->Data.getType()]; (Ascending && JTypeStr <= PivotTypeStr)
			|| (!Ascending && JTypeStr >= PivotTypeStr))
		{
			I = (I == nullptr) ? Left : I->Next;
			if (I != nullptr)
			{
				std::swap(I->Data, J->Data);
			}
		}
	}

	if (I != nullptr)
	{
		I = I->Next;
		if (I != nullptr)
		{
			std::swap(I->Data, Right->Data);
		}
	}
	return I;
}

Inventory::Node* Inventory::partitionByPrice(Node* Left, Node* Right, const bool Ascending) const
{
	const double PivotPrice = Right->Data.getPrice();
	Node* I = Left->Previous;

	for (Node* J = Left; J != Right && J != nullptr; J = J->Next)
	{
		if ((Ascending && J->Data.getPrice() <= PivotPrice) || (!Ascending && J->Data.getPrice() >= PivotPrice))
		{
			I = (I == nullptr) ? Left : I->Next;
			if (I != nullptr)
			{
				std::swap(I->Data, J->Data);
			}
		}
	}

	if (I != nullptr)
	{
		I = I->Next;
		if (I != nullptr)
		{
			std::swap(I->Data, Right->Data);
		}
	}
	return I;
}

Inventory::Node* Inventory::partitionByQuantity(Node* Left, Node* Right, const bool Ascending) const
{
	const int PivotQuantity = Right->Data.getQuantity();
	Node* I = Left->Previous;

	for (Node* J = Left; J != Right && J != nullptr; J = J->Next)
	{
		if ((Ascending && J->Data.getQuantity() <= PivotQuantity) || (!Ascending && J->Data.getQuantity() >=
			PivotQuantity))
		{
			I = (I == nullptr) ? Left : I->Next;
			if (I != nullptr)
			{
				std::swap(I->Data, J->Data);
			}
		}
	}

	if (I != nullptr)
	{
		I = I->Next;
		if (I != nullptr)
		{
			std::swap(I->Data, Right->Data);
		}
	}
	return I;
}
