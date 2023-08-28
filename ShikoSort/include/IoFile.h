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

#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <ShObjIdl.h>
#include "Inventory.h" // Include the necessary header

class IoFile
{
public:
    explicit IoFile(HWND Handle);
    ~IoFile();

	std::string openFile();
    std::string saveFile();


    static void trimWhitespace(std::string& Str);

private:
    OPENFILENAME MOfn{}; // Variable holding information about loading or saving file
    HWND MHwnd; // Handle current window
    HANDLE MHf{}; // Handle to a file

    char SzFile[260]{}; // Array for filename + path
};

// Save/load functions .txt