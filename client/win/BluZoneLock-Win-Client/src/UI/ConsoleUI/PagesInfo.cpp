// PagesInfo.cpp

#include "PagesInfo.h"
#include <string>
#include <Windows.h>
#include <iomanip>

#define APPLICATION_NAME_LENGTH 11

// The writeTitle function which prints the application name
void writeTitle(std::ostream& rOutputStream, HANDLE hConsole) {

    // Clear Console
    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

    // calculate width
    int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

    // For title application name we only have 1 column
    // left padding (x) + logo max width (u) + right padding (x)
    // 2*x + u = consoleWidth
    // => x = (consoleWidth - u) / 2;
    // Here u = length of string "BluZoneLock"
    int u = APPLICATION_NAME_LENGTH;
    int x = (consoleWidth - u) >> 1;
    x += APPLICATION_NAME_LENGTH + 8; // Add extra 8 to center the name

    printInRGB("Blu", true, 173, 216, 230, false, false, true, x, hConsole, rOutputStream);
    printInRGB("ZoneLock", true, 128, 128, 128, true, true, true, 0, hConsole, rOutputStream);

    printDivider('-', true, 173, 216, 230, 0, hConsole, rOutputStream);
}

void printInRGB(
    std::string piece,
    unsigned char fR, unsigned char fG, unsigned char fB, // for foreground color
    unsigned char bR, unsigned char bG, unsigned char bB, // for background color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    std::string foregroundColorSequence = "\x1B[38;2;" + std::to_string(fR) + ";" + std::to_string(fG) + ";" + std::to_string(fB) + "m";
    std::string backgroundColorSequence = "\x1B[48;2;" + std::to_string(bR) + ";" + std::to_string(bG) + ";" + std::to_string(bB) + "m";

    if (terminateLine) {
        rOutputStream << std::left << std::setw(paddingLeft) << foregroundColorSequence << backgroundColorSequence << piece << std::endl;
    }
    else {
        rOutputStream << std::left << std::setw(paddingLeft) << foregroundColorSequence << backgroundColorSequence << piece;
    }

    if (resetColorAfterOutput) {
        // reset color
        rOutputStream << "\x1B[0m";
    }

    if (flushOutputStream) {
        rOutputStream.flush();
    }
}

void printInRGB(
    std::string piece,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B, // For foreground color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    std::string colorSequence;
    if (forForeground) {
        colorSequence = "\x1B[38;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
    }
    else {
        colorSequence = "\x1B[48;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
    }

    if (terminateLine) {
        rOutputStream << std::left << std::setw(paddingLeft) << colorSequence << piece << std::endl;
    }
    else {
        rOutputStream << std::left << std::setw(paddingLeft) << colorSequence << piece;
    }

    if (resetColorAfterOutput) {
        // reset color
        rOutputStream << "\x1B[0m";
    }

    if (flushOutputStream) {
        rOutputStream.flush();
    }
}

void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    // Construct color sequence based on whether it's for foreground or background
    std::string colorSequence;
    if (forForeground) {
        colorSequence = "\x1B[38;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
    }
    else {
        colorSequence = "\x1B[48;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
    }

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

    // Calculate width based on console window dimensions
    int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

    // Print the divider with specified padding and color
    rOutputStream << std::left << std::setw(paddingLeft) << colorSequence << std::setfill(dividerSymbol) << std::string(consoleWidth, dividerSymbol) << std::endl;

    // Reset color
    rOutputStream << "\x1B[0m";
    // Flush output stream
    rOutputStream.flush();
}

void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB,    // For Background color
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    // Construct foreground and background color sequences
    std::string foregroundColorSequence = "\x1B[38;2;" + std::to_string(fR) + ";" + std::to_string(fG) + ";" + std::to_string(fB) + "m";
    std::string backgroundColorSequence = "\x1B[48;2;" + std::to_string(bR) + ";" + std::to_string(bG) + ";" + std::to_string(bB) + "m";

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

    // Calculate width based on console window dimensions
    int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

    // Print the divider with specified padding, foreground and background colors
    rOutputStream << std::left << std::setw(paddingLeft) << foregroundColorSequence << backgroundColorSequence << std::setfill(dividerSymbol) << std::string(consoleWidth, dividerSymbol) << std::endl;

    // Reset color
    rOutputStream << "\x1B[0m";
    // Flush output stream
    rOutputStream.flush();
}
