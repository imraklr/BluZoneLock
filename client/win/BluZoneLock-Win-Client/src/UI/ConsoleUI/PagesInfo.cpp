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

#define APPLICATION_NAME_LENGTH 11

 /**
  * @brief Manages shared content across pages, allowing storage, retrieval, and manipulation.
  * Each content item is identified by a unique ID. Ensuring ID uniqueness is not explicitly enforced.
  */
std::shared_ptr<std::unordered_map<int, void*>> pageSharedContent;

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

/**
* @brief Prints given string (`piece`) to the console with given color in RGB
*
* This function takes a string, RGB values for foreground and background with other parameters to
* display the text in color.
*
* @param piece -> A std::string which is to be displayed in the console.
* @param fR -> An unsigned char which represents the value of red channel for foreground color.
* @param fG -> An unsigned char which represents the value of green channel for foreground color.
* @param fB -> An unsigned char which represents the value of blue channel for foreground color.
* @param bR -> An unsigned char which represents the value of red channel for background color.
* @param bG -> An unsigned char which represents the value of greenchannel for background color.
* @param bB -> An unsigned char which represents the value of blue channel for background color.
* @param terminateLine -> A bool to indicate whether after printing the desired colored text, the line
* should be terminated or not.
* @param flushOutputStream -> A bool to indicate whether to call `flush()` on the supplied
* std::ostream& (`rOutputStream`) to flush the output stream.
* @param resetColorAfterOutput -> A bool to indicate whether to reset the color after output.
* @param paddingLeft -> An int for padding to be given to the left of the text to be printed.
* @param hConsole -> A HANDLE to the console.
* @param rOutputStream -> A reference to the std::ostream output stream.
*
* @return void
*/
void printInRGB(
    std::string piece,
    unsigned char fR, unsigned char fG, unsigned char fB, // for foreground color
    unsigned char bR, unsigned char bG, unsigned char bB, // for background color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    std::string 
        foregroundColorSequence = "\x1B[38;2;" + std::to_string(fR) + ";" + std::to_string(fG) + ";" + std::to_string(fB) + "m";
    std::string 
        backgroundColorSequence = "\x1B[48;2;" + std::to_string(bR) + ";" + std::to_string(bG) + ";" + std::to_string(bB) + "m";

    rOutputStream << std::string(paddingLeft, ' ') << foregroundColorSequence << backgroundColorSequence << piece;

    if (terminateLine) {
        rOutputStream << std::endl;
    }

    if (resetColorAfterOutput) {
        // reset color
        rOutputStream << "\x1B[0m";
    }

    if (flushOutputStream) {
        rOutputStream.flush();
    }
}

/**
* @brief Prints given string (`piece`) to the console with given color in RGB
*
* This function takes a string, RGB values for either foreground or background with other parameters to
* display the text in color.
*
* @param piece -> A std::string which is to be displayed in the console.
* @param R -> An unsigned char which represents the value of red channel for either foreground color or
* background color.
* @param G -> An unsigned char which represents the value of greenchannel for either foreground color or
* background color.
* @param B -> An unsigned char which represents the value of blue channel for either foreground color or
* background color.
* @param terminateLine -> A bool to indicate whether after printing the desired colored text, the line
* should be terminated or not.
* @param flushOutputStream -> A bool to indicate whether to call `flush()` on the supplied
* std::ostream& (`rOutputStream`) to flush the output stream.
* @param resetColorAfterOutput -> A bool to indicate whether to reset the color after output.
* @param paddingLeft -> An int for padding to be given to the left of the text to be printed.
* @param hConsole -> A HANDLE to the console.
* @param rOutputStream -> A reference to the std::ostream output stream.
*
* @return void
*/
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

    rOutputStream << std::string(paddingLeft, ' ') << colorSequence << piece;

    if (terminateLine) {
        rOutputStream << std::endl;
    }

    if (resetColorAfterOutput) {
        // reset color
        rOutputStream << "\x1B[0m";
    }

    if (flushOutputStream) {
        rOutputStream.flush();
    }
}

/**
* @brief Prints a divider using a supplied character which spans across entire console width.
*
* This function takes a string, RGB values for either foreground or background with other parameters to
* display the divider in color.
*
* @param piece -> A std::string which is to be displayed in the console.
* @param R -> An unsigned char which represents the value of red channel for either foreground color or
* background color.
* @param G -> An unsigned char which represents the value of greenchannel for either foreground color or
* background color.
* @param B -> An unsigned char which represents the value of blue channel for either foreground color or
* background color.
* @param paddingLeft -> An int for padding to be given to the left of the text to be printed.
* @param hConsole -> A HANDLE to the console.
* @param rOutputStream -> A reference to the std::ostream output stream.
*
* @return void
*/
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
    rOutputStream << 
        std::string(paddingLeft, ' ') << 
        colorSequence << std::setfill(dividerSymbol) <<
        std::string(consoleWidth, dividerSymbol) << 
        std::endl;

    // Reset color
    rOutputStream << "\x1B[0m";
    // Flush output stream
    rOutputStream.flush();
}

/**
* @brief Prints a divider using a supplied character which spans across entire console width.
*
* This function takes a string, RGB values for both foreground and background with other parameters to
* display the divider in color.
*
* @param piece -> A std::string which is to be displayed in the console.
* @param fR -> An unsigned char which represents the value of red channel for foreground color.
* @param fG -> An unsigned char which represents the value of green channel for foreground color.
* @param fB -> An unsigned char which represents the value of blue channel for foreground color.
* @param bR -> An unsigned char which represents the value of red channel for background color.
* @param bG -> An unsigned char which represents the value of greenchannel for background color.
* @param bB -> An unsigned char which represents the value of blue channel for background color.
* @param paddingLeft -> An int for padding to be given to the left of the text to be printed.
* @param hConsole -> A HANDLE to the console.
* @param rOutputStream -> A reference to the std::ostream output stream.
*
* @return void
*/
void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB,    // For Background color
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
) {
    // Construct foreground and background color sequences
    std::string 
        foregroundColorSequence = "\x1B[38;2;" + std::to_string(fR) + ";" + std::to_string(fG) + ";" + std::to_string(fB) + "m";
    std::string 
        backgroundColorSequence = "\x1B[48;2;" + std::to_string(bR) + ";" + std::to_string(bG) + ";" + std::to_string(bB) + "m";

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo);

    // Calculate width based on console window dimensions
    int consoleWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;

    // Print the divider with specified padding, foreground and background colors
    rOutputStream << 
        std::string(paddingLeft, ' ') << 
        foregroundColorSequence << 
        backgroundColorSequence << 
        std::setfill(dividerSymbol) << 
        std::string(consoleWidth, dividerSymbol) << 
        std::endl;

    // Reset color
    rOutputStream << "\x1B[0m";
    // Flush output stream
    rOutputStream.flush();
}
