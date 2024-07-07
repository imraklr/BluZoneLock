/**
 * @file PagesInfo.cpp
 * @brief Implements all the functions defined in PagesInfo.h header file.
 *
 * A page is defined as a single view on the console. The user can switch between pages using
 * commands to visit next page or previous page or any M page.
 *
 * A page consists of following parts:
 * 1. Title (logo or application name)
 * 2. Header (page number, commands specific to that page)
 * 3. Body (inputs, current ongoing actions)
 * 4. Footer (Footer is not necessary, it is just a placeholder for future use)
 *
 * @author Rakesh Kumar
 * @date July 5, 2024
 */

#include "PagesInfo.h"
#include <string>
#include <Windows.h>
#include <iomanip>
#include "../../Utils/Utils.h"

#define APPLICATION_NAME_LENGTH 11

 /**
 * @brief Writes title content to the console.
 *
 * A function to print the title to the console. This function is same for all pages.
 *
 * @param rOutputStream A reference to the std::ostream.
 * @param hConsole A HANDLE to the console.
 *
 * @return void
 */
void writeTitle(std::ostream& rOutputStream, HANDLE hConsole) {

    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

    // calculate width of the console
    int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

    // For title application name we only have 1 column
    // left padding (x) + application name width (u) + right padding (x)
    // 2*x + u = consoleWidth
    // => x = (consoleWidth - u) / 2;
    // Here u = length of string "BluZoneLock"
    int u = APPLICATION_NAME_LENGTH;
    int x = (consoleWidth - u) >> 1;

    printInRGB("Blu", true, 173, 216, 230, false, false, true, x, hConsole, rOutputStream);
    printInRGB("ZoneLock", true, 128, 128, 128, true, true, true, 0, hConsole, rOutputStream);

    printDivider('-', true, 173, 216, 230, 0, hConsole, rOutputStream);
}
