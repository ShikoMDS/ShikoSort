# ShikoSort

Rushed Inventory Sorting System project created for GD1P02 Algorithms and Data Structures Assessment 1.


## Table of Contents

- [Description]
- [Features]
- [Requirements]
- [Installation]
- [Controls]
- [Disclaimer]
- [Credits]


## Description

ShikoSort is a small program that allows the user to edit or create custom inventory lists.
This program is designed with C++ and to be operated with mouse and keyboard controls. 


## Features
### Loading and Saving
ShikoSort has a loading and saving function for the use of .txt files.
.txt files may be imported from the local system with the format where:

- NAME = Item name (std::string)
- TYPE = Item type (Enum - Weapon, Armor, Consumable, Utility)
- PRICE = Item price (double)
- QUANTITY = Item Quantity (int)

.TXT (REMOVE THE DOTS)
- NAME // TYPE // PRICE // QUANTITY
- Shiko Sword // Weapon // 10.69 // 1
- Bad Item // Rod // 21.69 // 1                   <- invalid type name (Rod), line will not be used
- Another Bad Item // Utility // 16.45 // 0       <- if item does not exist (0 quantity), why should it be in the list?
- Health Potion // Consumable // 2.99 // 5
                                                <- line will be skipped
Luminescence Cloak // Armor // 15.20 // 1
  d                                             <- invalid item format, line will not be used
Appearance Dust // Utility // 1.98 // 7

Inventories can be saved at their current state to a .txt file too!

### QuickSort
ShikoSort has QuickSort, allowing you to sort the inventory in ascending or descending order by item parameter NAME, TYPE, PRICE, or QUANTITY!


## Requirements

- Visual Studio 2022 (v143)
- Windows SDK 10.0
- C++ Language Standard: ISO C++20 Standard (/std:c++20)
- C Language Standard: ISO C17 (2018) Standard (/std:c17)
- Windows x64


## Installation

This program can be downloaded and built in x64 with Visual Studio 2022 by opening the solution file.


## Controls

Standard keyboard controls can be used.


## Disclaimer

This program is somewhat rushed and incomplete, it is "almost" finished for submission.
As this project is incomplete, the current issues are:
    - No input check handling: If you are stupid enough to test for input bugs, yes you will break the program as of now.
    - There is no GUI implemented or included to draw onto, the program currently only uses the Windows console.
    - I have not added a check for the 0 QUANTITY check as stated in features.
Bugs should be minimal but may be present. 
All code was written by me from my own knowledge from classes and self driven research of the C++ coding language.


## Credits

Shikomisen (Ayoub) 2023
Media Design School
GD1P02 - Algorithms and Data Structures
Written for Assignment 1
