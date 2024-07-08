/**
 * @file incoming.cpp
 *
 * @author Rakesh Kumar
 */

#include "incoming.h"
#include "../PagesInfo.h"
#include <string>
#include "../../../Utils/Utils.h"
#include <Windows.h>
#include <stdint.h>

void initIncomingPage(struct Page* page) {
    page->fpHeaderF = [](std::ostream& rOutputStream, HANDLE hConsole, uint_fast8_t pageNumber) -> void {
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

        // page number with arrow symbols showing if navigation is available

        // Use this length to identify available padding
        int dateTimeStringLength = date.size() + separator.size() + time.size();
        std::string currentPageNumberAsString = std::to_string(pageNumber);

        std::string navigationString = "";

        if (pageNumber > 1) {
            navigationString = "<";
        }
        navigationString += " " + currentPageNumberAsString + " ";
        if (pageNumber < 5) {
            navigationString += ">";
        }

        // calculate left padding to navigation string
        // Get console screen buffer info
        CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

        // Calculate width based on console window dimensions
        int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

        int u = navigationString.size();
        int x = (consoleWidth - u) >> 1;
        x -= dateTimeStringLength; // adjust as per date-time string length

        printInRGB(navigationString, true, 90, 90, 255, false, true, true, x, hConsole, rOutputStream);

        // Name of the view/screen/page
        std::string pageName = "View: Incoming";
        u = dateTimeStringLength + x + u;
        x = consoleWidth - pageName.size();
        x = x - u;
        printInRGB(pageName, true, 0, 255, 0, true, true, true, x, hConsole, rOutputStream);
    };
}