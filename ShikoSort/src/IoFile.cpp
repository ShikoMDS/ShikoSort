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

#include "IoFile.h"

#include <iostream>

IoFile::IoFile(const HWND Handle)
{
    // Clear and initialise memory for OFN
    ZeroMemory(&MOfn, sizeof(MOfn));
    MOfn.lStructSize = sizeof(MOfn);

    // Load the handle parameter and set to the member
    MHwnd = Handle;

    // Set the open filename owner
    MOfn.hwndOwner = MHwnd;

    // Initialise a string as empty, then null the first element
    MOfn.lpstrFile = reinterpret_cast<LPWSTR>(SzFile);
    MOfn.lpstrFile[0] = '\0';
    MOfn.nMaxFile = sizeof(SzFile);

    const std::string DefaultName("Untitled");

    for (int I = 0; I < DefaultName.size(); I++)
    {
        MOfn.lpstrFile[I] = DefaultName[I];
    }

    // Change file filters to change what image types we can see or save to
    MOfn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";

    // What do these do idk?
    MOfn.nFilterIndex = 1;

    MOfn.lpstrFileTitle = nullptr;
    MOfn.nMaxFileTitle = 0;
    MOfn.lpstrInitialDir = nullptr;

    MOfn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
}

IoFile::~IoFile() = default;

std::string IoFile::openFile()
{
    OPENFILENAME Ofn;
    ZeroMemory(&Ofn, sizeof(Ofn));
    Ofn.lStructSize = sizeof(Ofn);
    Ofn.hwndOwner = nullptr;
    Ofn.lpstrFile = reinterpret_cast<LPWSTR>(SzFile);
    Ofn.lpstrFile[0] = '\0';
    Ofn.nMaxFile = sizeof(SzFile);
    Ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    Ofn.nFilterIndex = 1;
    Ofn.lpstrTitle = L"Open File";
    Ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&Ofn) == true)
    {
        std::wstring Ws(Ofn.lpstrFile);
        return std::string(Ws.begin(), Ws.end());
    }
    else
    {
        return {};
    }
}

std::string IoFile::saveFile()
{
    if (GetSaveFileName(&MOfn) == true)
    {
        std::wstring Ws(MOfn.lpstrFile);
        return std::string(Ws.begin(), Ws.end());
    }
    else
    {
        return {};
    }
}

void IoFile::trimWhitespace(std::string& Str)
{
	if (const size_t First = Str.find_first_not_of(" \t"); std::string::npos != First)
    {
	    const size_t Last = Str.find_last_not_of(" \t");
        Str = Str.substr(First, (Last - First + 1));
    }
}

// Implement save/load, note " " and "//"