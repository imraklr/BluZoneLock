// PagesInfo.cpp

#include "PagesInfo.h"
#include <string>

// The writeTitle function which prints the logo
void writeTitle(std::ostream& rOutputStream, HANDLE hConsole) {

    printInRGB("  ||\\", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("  || \\", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("\\ || /", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB(" \\||/", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("  ||", true, 0, 0, 255, false, false, false, hConsole, rOutputStream);
    
    printInRGB("luZoneLock", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    
    printInRGB(" /||\\", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("/ || \\", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("  || /", true, 0, 0, 255, true, false, false, hConsole, rOutputStream);
    printInRGB("  ||/", true, 0, 0, 255, true, false, true, hConsole, rOutputStream);
}

void printInRGB(
    std::string piece,
    unsigned char fR, unsigned char fG, unsigned char fB, // for foreground color
    unsigned char bR, unsigned char bG, unsigned char bB, // for background color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    std::string foregroundColorSequence = "\x1B[38;2;" + std::to_string(fR) + ";" + std::to_string(fG) + ";" + std::to_string(fB) + "m";
    std::string backgroundColorSequence = "\x1B[48;2;" + std::to_string(bR) + ";" + std::to_string(bG) + ";" + std::to_string(bB) + "m";

    if (terminateLine) {
        rOutputStream << foregroundColorSequence << backgroundColorSequence << piece << std::endl;
    }
    else {
        rOutputStream << foregroundColorSequence << backgroundColorSequence << piece;
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
        rOutputStream << colorSequence << piece << std::endl;
    }
    else {
        rOutputStream << colorSequence << piece;
    }

    if (resetColorAfterOutput) {
        // reset color
        rOutputStream << "\x1B[0m";
    }

    if (flushOutputStream) {
        rOutputStream.flush();
    }
}