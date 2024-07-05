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

/**
* @brief The entry point of the application.
* 
* @return An exit code sent to the operating system.
*/
int main() {

    // get the reference to cout, cerr, cin streams
    std::istream& input_stream = std::cin;
    std::ostream& output_stream = std::cout;
    std::ostream& error_stream = std::cerr;


    // Retrieve the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == NULL) {
        std::cout << "StdHandle retrieval failure" << std::endl;
    }
    else {
        // obtain PagingManager instance ( initializes pages and draws status page title )
        PagingManager& pagingManager = PagingManager::getInstance(output_stream, hConsole);
    }

    system("pause");

    return 0;
}