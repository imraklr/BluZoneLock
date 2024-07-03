// PagesInfo.h
#pragma once

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <ostream>
#include <stdint.h>
#include <memory>
#include <sal.h>
#include <Windows.h>

/// only 6 pages are there: incoming, outgoing, status(or health), logging screen , transitioning screen, error screen
#define MAXIMUM_ALLOWED_NUMBER_OF_PAGES 6
#define MINIMUM_ALLOWED_NUMBER_OF_PAGES 1
/// If the screen is transitioning from one to another, display this message
#define SCREEN_TRANSITION_MESSAGE "Hang On\nWe are processing that!!";

// function to print RGB based color to a specific piece of text (optional line termination)
extern void printInRGB(
    std::string piece,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB, // For Background color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE, std::ostream&
);
extern void printInRGB(
    std::string piece,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B, // For foreground color
    bool terminateLine, bool flushOutputStream, bool resetColorAfterOutput,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);
extern void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char R, unsigned char G, unsigned char B,
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);
extern void printDivider(
    char dividerSymbol,
    bool forForeground,
    unsigned char fR, unsigned char fG, unsigned char fB,    // For Foreground color
    unsigned char bR, unsigned char bG, unsigned char bB,    // For Background color
    int paddingLeft,
    HANDLE hConsole, std::ostream& rOutputStream
);

extern void writeTitle(std::ostream&,HANDLE); // extern because it needs to be implemented only once ( it contains only a logo to print )
void writeHeader(std::ostream&);
void writeBody(std::ostream&);
void writeFooter(std::ostream&);
// Paging feature
struct Page {
    _Field_range_(
        MINIMUM_ALLOWED_NUMBER_OF_PAGES, MAXIMUM_ALLOWED_NUMBER_OF_PAGES
    ) uint_fast8_t page_number;

    /// <summary>
    /// The four parts of any page: Title (Compulsory), Header (Compulsory), Body (Compulsory), Footer (Close/Exit notices)
    /// </summary>
    void (*fpTitleF)(std::ostream&,HANDLE);  // Function Pointer to `title`  function
    void (*fpHeaderF)(std::ostream&); // Function Pointer to `header` function
    void (*fpBodyF)(std::ostream&);   // Function Pointer to `body`   function
    void (*fpFooterF)(std::ostream&); // Function Pointer to `footer` function

    // Title is constant (not changing) ==> Single function reuse
    // Division Line
    // Header has a changing nature --> page_number at the top is changing, commands & details as per page nature is also variable. Conclusion: Use lambda with shared stuff 
    // included at proper place:
    // lambda_begin {
    //     rOutputStream << pageSharedStuff.getStuff("unique ID / name");
    //     // other custom stuff
    //     use shared stuff OR write other custom stuff
    // }
    // Division Line
    // 

    Page() : page_number(0), fpTitleF(&writeTitle), fpHeaderF(nullptr), fpBodyF(nullptr), fpFooterF(nullptr) {}
};

struct Reusable {
    short id;
    void* content;
};

extern std::shared_ptr<struct Resuable[]> pageSharedStuff; // could be anything, repeated strings in console output, a thread, an object or whatever.

// contains no allocation functions. Allocation is totally explicit
struct PageList {
    uint_fast8_t index; // initially 0

    struct Page currentPage;

    /**
    * A circular array for storing pages.
    */
    struct Page pageArray[MAXIMUM_ALLOWED_NUMBER_OF_PAGES]; // an array of pages

    void addPage(struct Page page) {
        // copy page data to the index by page_number - 1
        // check range
        if ((page.page_number <= MAXIMUM_ALLOWED_NUMBER_OF_PAGES) && (page.page_number >= MINIMUM_ALLOWED_NUMBER_OF_PAGES)) {
            pageArray[page.page_number - 1] = page;
            if (page.page_number == 1) {
                currentPage = pageArray[page.page_number - 1];
            }
        }
        else {
            // write to the output
        }
    }

    void showHeader(std::ostream& output_stream) {
        // show current page number and then show all the commands, how to move among pages, etc. etc.
    }

    // constructor
    PageList() : index(0), currentPage{}, pageArray{} {}
    // Destructor to clean up allocated memory
    ~PageList() {}
};
extern struct PageList pagelist;

#endif