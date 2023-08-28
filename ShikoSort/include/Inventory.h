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

#pragma once

#include "Item.h"

class Inventory
{
public:
	// Doubly-Linked list
	// Item/Node class doubly linked list data structure
	class Node
	{
	public:
		// Node holds 2 ends and a body for DLL
		explicit Node(const Item& NewItem, Node* NextItem, Node* PrevItem);
		Item Data; // Core
		Node* Previous; // Head
		Node* Next; // Tail
	};

	Inventory(); // Constructor
	~Inventory(); // Destructor


	static std::string itemTypeToString(ItemType Type);
	// Load/Save functions
	void loadFile(const std::string& Filename);
	void saveFile(const std::string& FileName) const;

	void displayInventory() const;

	[[nodiscard]] Node* findItem(const std::string& Name) const; // Find a selected item from index
	[[nodiscard]] bool itemExists(const std::string& Name) const; // Check if name exists - cannot duplicate
	void addFileItem(const Item& NewItem); // Add a new item to index
	void addItem(const Item& NewItem);
	void removeItem(size_t Index); // Remove a selected item from index
	void accessItem(size_t Index, Item& NewItem) const; // Access and edit a selected item from index
	void clearInventory(); // Deletes all items from current inventory

	// Quick sort
	// Ascending
	// Descending
	// Name, Type, Price, Quantity etc.
	// Quick sort by item name
	void quickSortByName(bool Ascending);
	void quickSortByType(bool Ascending);
	void quickSortByPrice(bool Ascending);
	void quickSortByQuantity(bool Ascending);

	[[nodiscard]] Node* getHead() const;
	[[nodiscard]] Node* getTail() const;
	[[nodiscard]] size_t getSize() const;

private:
	// Front and back end list
	Node* MHead;
	Node* MTail;
	// Index size 
	size_t MSize; // size_t array indexing/loop counting https://en.cppreference.com/w/c/types/size_t

	void quickSortByNameRecursive(Node* Left, Node* Right, bool Ascending);
	void quickSortByTypeRecursive(Node* Left, Node* Right, bool Ascending);
	void quickSortByPriceRecursive(Node* Left, Node* Right, bool Ascending);
	void quickSortByQuantityRecursive(Node* Left, Node* Right, bool Ascending);

	Node* partitionByName(Node* Left, Node* Right, bool Ascending) const;
	Node* partitionByType(Node* Left, Node* Right, bool Ascending) const;
	Node* partitionByPrice(Node* Left, Node* Right, bool Ascending) const;
	Node* partitionByQuantity(Node* Left, Node* Right, bool Ascending) const;
};

