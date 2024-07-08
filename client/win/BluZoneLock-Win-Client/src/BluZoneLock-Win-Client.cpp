/**
 * @file BluZoneLock-Win-Client.cpp
 * @brief Bluetooth client application for BluZoneLock.
 * 
 * This file contains the 'main' function. Program execution begins and ends there.
 * This Bluetooth application runs in client mode only and operates within a console environment.
 *
 * @author Rakesh Kumar
 */

#include <Windows.h>
#include <iostream>
#include "UI/ConsoleUI/PagingManager.h"

void performPreChecks(std::ostream&);
void postLaunchWarnings(std::ostream&, std::ostream&, HANDLE);
void hideConsoleCursor(HANDLE hConsole, std::ostream& rErrorStream);
void showConsoleCursor(HANDLE hConsole, std::ostream& rErrorStream);

/**
* @brief The entry point of the application.
* 
* @return An exit code sent to the operating system.
*/
int main() {

    // get the reference to cout, cerr, cin streams
    std::istream& rInputStream = std::cin;
    std::ostream& rOutputStream = std::cout;
    std::ostream& rErrorStream = std::cerr;


    // Retrieve the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        rOutputStream << "StdHandle retrieval failure" << std::endl;
        rOutputStream.flush();
    }
    else {
        performPreChecks(rOutputStream);
        // display warnings after console application launch
        postLaunchWarnings(rOutputStream, rErrorStream, hConsole);
        // obtain PagingManager instance ( initializes pages and draws status page title )
        PagingManager& pagingManager = PagingManager::getInstance(rOutputStream, hConsole);
        // Display status page when the application is launched after warning messages
        pagingManager.showPage(1);
    }

    system("pause");

    return 0;
}

/**
* @brief A function to perform some checks after moving on to showing status page.
* 
* @param rOutputStream A reference to `std::ostream`
*/
void performPreChecks(std::ostream& rOutputStream) {}

/**
* @brief Display warnings before moving to any page/view/screen.
*
* @param rOutputStream A reference to `std::ostream`
*/
void postLaunchWarnings(std::ostream& rOutputStream, std::ostream& rErrorStream, HANDLE hConsole) {
    // Display warning messages
    rOutputStream << "WARNING: THIS APPLICATION MUST NOT BE RUN IN ADMINISTRATOR MODE" 
        << std::endl;
    rOutputStream << "\tREASON(S):\n\t\t* MIGHT EXPRESS UNDEFINED BEHAVIOR RELATED TO DISPLAY OF TEXT"
        << std::endl;
    rOutputStream << "\t\t* THIS APPLICATION DOES NOT NEED ELEVATED PRIVILEGES" 
        << std::endl;

    // Introduce time delay before switching to status page
    std::string switchMessage = "Switching to status page in x seconds...";
    rOutputStream << switchMessage;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole, &info);
    COORD pos = 
        {static_cast<SHORT>(switchMessage.length() - 12), static_cast<SHORT>(info.dwCursorPosition.Y)};
    
    // Hide the cursor
    hideConsoleCursor(hConsole, rErrorStream);
    
    for (int i = 4;i >= 1;i--) {
        SetConsoleCursorPosition(hConsole, pos);
        rOutputStream << i;
        Sleep(1000);
    }

    // Restore cursor
    showConsoleCursor(hConsole, rErrorStream);

    // Change line
    rOutputStream << "" << std::endl;
    rOutputStream.flush();
    system("cls");
}

// Function to hide the console cursor
void hideConsoleCursor(HANDLE hConsole, std::ostream& rErrorStream) {
    if (hConsole == INVALID_HANDLE_VALUE) {
        rErrorStream << "Error getting console handle" << std::endl;
        rErrorStream.flush();
        return;
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Function to show the console cursor
void showConsoleCursor(HANDLE hConsole, std::ostream& rErrorStream) {
    if (hConsole == INVALID_HANDLE_VALUE) {
        rErrorStream << "Error getting console handle" << std::endl;
        rErrorStream.flush();
        return;
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true; // Show the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}