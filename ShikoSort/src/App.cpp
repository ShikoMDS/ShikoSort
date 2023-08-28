/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : App.cpp
Description : Implementations for App.h app handling declarations
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include <iostream>

#include "App.h"
#include "IoFile.h"

App::App() : MFileManager(GetConsoleWindow()) // Pass the console window handle to IoFile constructor
{
    // Load items from a file
    //MInventory.loadFile("resources/Inventory.txt");
}

App::~App() = default;

void App::run()
{
    std::cout << "Welcome to ShikoSort - a custom inventory management system using custom doubly linked list!" << std::endl;
    std::cout << "To get started, enter (4) to load preset or custom lists in the resources folder!" << std::endl;
    std::cout << "Suggested file - Inventory.txt (Initial inventory list file)" << std::endl;
    std::cout << "Otherwise you may start to create your own inventory to export immediately!" << std::endl;

    while (true)
    {
        MInventory.displayInventory();

        int Input;
        std::cout << "\nEnter 0 to clear inventory, 1 to add an item, 2 to remove an item, 3 to access/edit an item, 4 to load from file, 5 to save to file, 6 to quick sort, or -1 to exit: ";
        std::cin >> Input;

        if (Input == -1)
        {
            std::cout << "Exiting the program." << std::endl;
            break;
        }

        if (Input == 0) // Clear inventory
        {
            char ConfirmClear;
            std::cout << "Are you sure you want to clear the inventory? (y/n): ";
            std::cin >> ConfirmClear;

            if (ConfirmClear == 'y' || ConfirmClear == 'Y')
            {
                MInventory.clearInventory();
                std::cout << "Inventory cleared." << std::endl;
            }
            else
            {
                std::cout << "Inventory not cleared." << std::endl;
            }
        }
        else if (Input == 1) // Add an item
        {
            std::string Name;
            int Type;
            double Price;
            int Quantity;

            std::cout << "Enter the name of the new item: ";
            std::cin.ignore(); // Clear the newline character from previous input
            std::getline(std::cin, Name);

            do
            {
                std::cout << "Enter the type of the new item (0: Weapon, 1: Armor, 2: Consumable, 3: Utility): ";
                std::cin >> Type;

                if (Type < 0 || Type > 3)
                {
                    std::cout << "Invalid type. Please enter a valid type (0, 1, 2, or 3)." << std::endl;
                }
            }
        	while (Type < 0 || Type > 3);

            std::cout << "Enter the price of the new item: ";
            std::cin >> Price;

            std::cout << "Enter the quantity of the new item: ";
            std::cin >> Quantity;

            Item NewItem(Name, static_cast<ItemType>(Type), Price, Quantity);
            MInventory.addItem(NewItem);
        }
        else if (Input == 2) // Remove an item
        {
            std::cout << "Enter the item number to remove: ";
            std::cin >> Input;

            if (const int Choice = Input - 1; Choice >= 0 && Choice < MInventory.getSize())
            {
                MInventory.removeItem(Choice);
                std::cout << "Item " << Choice + 1 << " has been removed from the inventory." << std::endl;
            }
            else
            {
                std::cout << "Invalid index." << std::endl;
            }
        }
        else if (Input == 3) // Access and edit an item
        {
            std::cout << "Enter item number to edit: ";
            std::cin >> Input;

            if (const int Choice = Input - 1; Choice >= 0 && Choice < MInventory.getSize())
            {
                Item NewItem("New Name", ItemType::Weapon, 10.19, 2);
                MInventory.accessItem(Choice, NewItem);
                std::cout << "Item " << Choice + 1 << " edited successfully." << std::endl;
            }
            else
            {
                std::cout << "No item at index." << std::endl;
            }
        }
        else if (Input == 4) // Load from file
        {
	        if (std::string Filename = MFileManager.openFile(); !Filename.empty()) {
                MInventory.loadFile(Filename);
                std::cout << "Items loaded from " << Filename << std::endl;
            }
            else {
                std::cout << "Operation canceled or no file name entered." << std::endl;
            }
        }
        else if (Input == 5) // Save to file
        {
            std::string Filename = MFileManager.saveFile();
            MInventory.saveFile(Filename);
        }
        else if (Input == 6) // Quick sort
        {
            int SortOption;
            int SortOrder;
            std::cout << "Enter the sorting option (1: Name, 2: Type, 3: Price, 4: Quantity): ";
            std::cin >> SortOption;

            std::cout << "Enter the sorting order (1: Ascending, 2: Descending): ";
            std::cin >> SortOrder;

            const bool Ascending = (SortOrder == 1);
            switch (SortOption)
            {
            case 1:
                MInventory.quickSortByName(Ascending);
                break;
            case 2:
                MInventory.quickSortByType(Ascending);
                break;
            case 3:
                MInventory.quickSortByPrice(Ascending);
                break;
            case 4:
                MInventory.quickSortByQuantity(Ascending);
                break;
            default:
                std::cout << "Invalid sorting option." << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1 to add, 2 to remove, 3 to access, or -1 to exit." << std::endl;
        }
    }
}



// Code to handle the program to be ran