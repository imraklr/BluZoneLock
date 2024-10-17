/**
 * @file page.cpp
 *
 * @author Rakesh Kumar
 */

#include "header/page.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <stdint.h>
#include "../utils/header/Utils.h"

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


void initPage(std::ostream& rOutputStream, HANDLE hConsole) {
	// Get date and time
	SYSTEMTIME st;
	GetSystemTime(&st);

	// Prepare date and time strings
	std::string date = std::to_string(st.wYear) + "." +
		std::to_string(st.wMonth) + "." +
		std::to_string(st.wDay);
	std::string separator = " -- ";
	std::string time = std::to_string(st.wHour) + ":" +
		std::to_string(st.wMinute) + ":" +
		std::to_string(st.wSecond) + ":" +
		std::to_string(st.wMilliseconds);

	// Print date and time with appropriate formatting and colors
	printInRGB(date, true, 233, 116, 81, false, true, true, 0, hConsole, rOutputStream);
	printInRGB(separator, true, 128, 128, 128, false, false, true, 0, hConsole, rOutputStream);
	printInRGB(time, true, 0, 255, 255, false, false, true, 0, hConsole, rOutputStream);

	rOutputStream << "" << std::endl << std::flush;
}
