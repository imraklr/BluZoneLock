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
#include <unordered_map>

// only 5 pages are there: incoming, outgoing, status(or health), logging screen, error screen
#define MAXIMUM_ALLOWED_NUMBER_OF_PAGES 5
#define MINIMUM_ALLOWED_NUMBER_OF_PAGES 1
// If the screen is transitioning from one to another, display this message in a new view and then 
// change to the desired page
#define SCREEN_TRANSITION_MESSAGE "Hang On\nWe are processing that!!";

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
    }

    PageList() : index(0), currentPage{}, pageArray{} {}
    ~PageList() {}
};

/**
* @brief A single definition of `struct PageList` that can be used across entire 
* application.
*/
extern struct PageList pageList;

#endif