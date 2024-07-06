/**
 * @file Utils.h
 * @brief Header file for all utility functions, variables, etc.
 *
 * @author Rakesh Kumar
 */
#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <ostream>
#include <string>
#include <Windows.h>
#include <iomanip>

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
extern void printInRGB(
    std::string piece,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB, // For Background color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);

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
extern void printInRGB(
    std::string piece,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B, // For foreground color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);

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
extern void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);

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
extern void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB,    // For Background color
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);

#endif