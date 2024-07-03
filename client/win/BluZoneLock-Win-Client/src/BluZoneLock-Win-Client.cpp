/*
* BluZoneLock-Win-Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
* This Bluetooth application runs in client mode only and operates within a console environment.
*/

#include <Windows.h>
#include <iostream>
#include "UI/ConsoleUI/PagingManager.h"

/**
* @file BluZoneLock-Win-Client.cpp
* @brief Bluetooth client application for BluZoneLock.
* @details This console application initiates a Bluetooth connection in client mode.
*
* @author Rakesh Kumar
* @date July 2, 2024
*/
int main() {

    // get the reference to cout, cerr, cin streams
    std::istream& input_stream = std::cin;
    std::ostream& output_stream = std::cout;
    std::ostream& error_stream = std::cerr;


    // Retrieve the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == NULL) {
        std::cout << "StdHandle retrieval failure" << std::endl;
    }
    else {
        // obtain PagingManager instance ( initializes pages and draws status page title)
        PagingManager& pagingManager = PagingManager::getInstance(output_stream, hConsole);
    }

    system("pause");

    return 0;
}