/**
 * @file PagesInfo.h
 * @brief Header file for all page related functionalities and data structures.
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
 * This header file defines a data structure for a page to store the info related to a page,
 * the page list which is again, a data structure to maintain an array of pages. This array
 * contains `struct Page` type items.
 *
 * @author Rakesh Kumar
 */
#pragma once

#ifndef PAGESINFO_H
#define PAGESINFO_H

#include <ostream>
#include <stdint.h>
#include <memory>
#include <sal.h>
#include <Windows.h>

// only 6 pages are there: incoming, outgoing, status(or health), logging screen , transitioning 
// screen, error screen
#define MAXIMUM_ALLOWED_NUMBER_OF_PAGES 6
#define MINIMUM_ALLOWED_NUMBER_OF_PAGES 1
// If the screen is transitioning from one to another, display this message in a new view and then 
// change to the desired page
#define SCREEN_TRANSITION_MESSAGE "Hang On\nWe are processing that!!";

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

/**
* @brief Writes title content to the console.
* 
* A function to print the title to the console. It is declared as extern because title is same for 
* every page.
* 
* @param rOutputStream A reference to the std::ostream.
* @param hConsole A HANDLE to the console.
* 
* @return void
*/
extern void writeTitle(std::ostream& rOutputStream,HANDLE hConsole);

/**
* @brief Writes header to the console.
* 
* A function to print the header contents to the console. This function has different variants 
* because every page has its own content.
* NOTE: There might be some shared contents to be displayed which is stored in a shared data 
* structure `struct Reusable` using `std::shared_ptr<struct Reusable[]>`.
* 
* @param A reference to `std::ostream`.
* 
* @return void
*/
void writeHeader(std::ostream&);

/**
* @brief Writes body to the console.
*
* A function to print the body contents to the console. This function has different variants
* because every page has its own content.
* NOTE: There might be some shared contents to be displayed which is stored in a shared data
* structure `struct Reusable` using `std::shared_ptr<struct Reusable[]>`.
*
* @param A reference to `std::ostream`.
*
* @return void
*/
void writeBody(std::ostream&);

/**
* @brief Writes footer to the console.
*
* A function to print the footer contents to the console. This function has different variants
* because every page has its own content.
* NOTE: No shared content has to be kept with respect to the footer section.
*
* @param A reference to `std::ostream`.
*
* @return void
*/
void writeFooter(std::ostream&);

/**
* @brief A struct that refers to a page to be printed on the console.
* 
* This struct contains the pointers to the functions for printing the title, header, body and 
* footer sections of a page.
* A constructor is utilized to initialize the struct instances.
* The page_number member stores the page number of the page. Each page has a specific page 
* number associated with it, the order of which cannot and must not be changed.
*/
struct Page {
    /**
    * The page number associated with a page. It is not changeable and must not be changed. 
    * The order must not be different than originally assigned through the `init()` function
    * call from PagingManager class.
    */ 
    _Field_range_(
        MINIMUM_ALLOWED_NUMBER_OF_PAGES, MAXIMUM_ALLOWED_NUMBER_OF_PAGES
    ) uint_fast8_t page_number;

    // The four parts of any page: Title (Compulsory), Header (Compulsory), Body (Compulsory), 
    // Footer (Close/Exit notices, Optional)
    void (*fpTitleF)(std::ostream&,HANDLE);  // Function Pointer to `title`  function
    void (*fpHeaderF)(std::ostream&); // Function Pointer to `header` function
    void (*fpBodyF)(std::ostream&);   // Function Pointer to `body`   function
    void (*fpFooterF)(std::ostream&); // Function Pointer to `footer` function

    /**
     * A constructor to initialize an instance of `struct Page`.
     * The header, body, and footer function pointers are set to `nullptr`
     * because these functions will be different for different pages.
     * The `page_number` is initialized to `0` and it will be
     * changed later by the `init()` function call from the PagingManager
     * class instance.
     */
    Page() : page_number(0), fpTitleF(&writeTitle), fpHeaderF(nullptr), fpBodyF(nullptr), fpFooterF(nullptr) {}
};

/**
* @brief A structure for storing shared contents of header and body sections.
*/
struct Reusable {
    // The unique id of the content.
    short id;
    // The content.
    void* content;
};

/**
* @brief An instance of `std::shared_ptr<struct Reusable[]>` to store the shared contents 
* of header & body sections in a `struct Reusable` struct. It needs to be defined only 
* once. It could store anything from repeated strings in console output to a thread or an 
* object.
*/
extern std::shared_ptr<struct Resuable[]> pageSharedStuff;

/**
* @brief A struct that holds an array/list of pages with a function that can 
* add a page to the list, a constructor to initialize instance of `struct PageList`, and, 
* a destructor to destruct the instance.
*/
struct PageList {
    /**
    * @brief The index of the array and not the page number.
    */
    uint_fast8_t index;

    /**
    * @brief The current page being viewed.
    */
    struct Page currentPage;

    /**
    * @brief A circular array to store instance of `struct Page`.
    */
    struct Page pageArray[MAXIMUM_ALLOWED_NUMBER_OF_PAGES];

    /**
    * @brief A function to add a page to the `pageArray` array/list. Only upto 
    * `MAXIMUM_ALLOWED_NUMBER_OF_WORDS` instance are allowed in the list.
    * 
    * @param page An instance of a `struct Page` type.
    */
    void addPage(struct Page page) {
        if (
            (page.page_number <= MAXIMUM_ALLOWED_NUMBER_OF_PAGES) && 
            (page.page_number >= MINIMUM_ALLOWED_NUMBER_OF_PAGES)
        ) {
            pageArray[page.page_number - 1] = page;
            if (page.page_number == 1) {
                currentPage = pageArray[page.page_number - 1];
            }
        }
        /// @deprecated REDUNDANT else block, marked for removal
        else {
            // write to the output
        }
    }

    // @deprecated REDUNDANT function, marked for removal
    void showHeader(std::ostream& output_stream) {}

    PageList() : index(0), currentPage{}, pageArray{} {}
    ~PageList() {}
};

/**
* @brief A single definition of `struct PageList` that can be used across entire 
* application.
*/
extern struct PageList pageList;

#endif