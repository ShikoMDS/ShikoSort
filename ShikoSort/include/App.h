/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : App.h
Description : Declarations for application handling
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include "Gui.h"
#include "Inventory.h"
#include "IoFile.h"

class App
{
public:
	App();
	~App();
	void run(); // Main app loop initiator

private:
	Inventory MInventory;
	IoFile MFileManager;
	Gui MGui;
};

// Program handles