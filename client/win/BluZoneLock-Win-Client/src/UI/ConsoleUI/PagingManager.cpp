/**
 * @file PagingManager.cpp
 * @brief Implementation of the PagingManager class.
 *
 * This file contains the implementation of the PagingManager class, including its
 * member functions and the singleton instance management.
 *
 * @author Rakesh Kumar
 */

#include "PagingManager.h"
#include "PagesInfo.h"
#include <Windows.h>

// Static instance initialization
static PagingManager* instance = nullptr;
// Global instance of struct PageList
struct PageList pageList;

/**
 * @brief Get the singleton instance of PagingManager.
 *
 * This function returns the singleton instance of PagingManager. It takes
 * a reference to an output stream and a handle to the console as parameters.
 *
 * @param rOutputStream Reference to an output stream.
 * @param hConsole Handle to the console.
 * @return The singleton instance of PagingManager.
 */
PagingManager& PagingManager::getInstance(std::ostream& rOutputStream, HANDLE hConsole) {
    if (!instance) {
        instance = new PagingManager(rOutputStream, hConsole);
    }
    return *instance;
}

/**
 * @brief Constructor.
 *
 * This constructor initializes the PagingManager with the provided
 * output stream and console handle. It is private to enforce the singleton pattern.
 *
 * @param rOutputStream Reference to an output stream.
 * @param hConsole Handle to the console.
 */
PagingManager::PagingManager(std::ostream& rOutputStream, HANDLE hConsole)
    : rOutputStream(rOutputStream), hConsole(hConsole) {
    // Constructor implementation
    PagingManager::init();
}

/**
 * @brief Move to the next page.
 *
 * This function changes the view to the next page and returns it.
 *
 * @return The next page (instance of `struct Page`).
 */
Page PagingManager::nextPage() {
    pageList.index = (++(pageList.index)) % MAXIMUM_ALLOWED_NUMBER_OF_PAGES; // 0-indexing
    pageList.currentPage = pageList.pageArray[pageList.index];

    // Clear Console
    clearConsole();
    // Show the title
    pageList.currentPage.fpTitleF(rOutputStream, hConsole);
    // Show the header

    return pageList.currentPage;
}

/**
 * @brief Move to the previous page.
 *
 * This function changes the view to the previous page and returns it.
 *
 * @return The previous page (instance of `struct Page`).
 */
Page PagingManager::prevPage() {
    if (pageList.index == 0) {
        pageList.index = MAXIMUM_ALLOWED_NUMBER_OF_PAGES - 1;
    }
    else {
        --(pageList.index);
    }
    pageList.currentPage = pageList.pageArray[pageList.index];

    // Clear console
    clearConsole();
    // show the title
    pageList.currentPage.fpTitleF(rOutputStream, hConsole);
    // show the header

    return pageList.currentPage;
}

/**
 * @brief Move to the Mth page where M is the page number.
 *
 * This function changes the view to the Mth page and returns it.
 *
 * @return The Mth page (instance of `struct Page`) OR if incorrect page number is supplied 
 * then the current page instance is returned. Use this function in conjunction with 
 * `isTheSamePage(struct Page* thisPage)` function to know if returned page instance matches 
 * the page that the user is on. This prevents huge rewrites to the screen.
 */
Page PagingManager::mthPage(uint_fast8_t M) {
    if (!(
        M > MAXIMUM_ALLOWED_NUMBER_OF_PAGES && M < MINIMUM_ALLOWED_NUMBER_OF_PAGES
        )) {
        // M cannot be zero, as the user is not aware of 0-based indexing in computer programs.
        pageList.index = M - 1;
        pageList.currentPage = pageList.pageArray[pageList.index];
    }

    // Clear console
    clearConsole();
    // show the title
    pageList.currentPage.fpTitleF(rOutputStream, hConsole);
    // show the header

    return pageList.currentPage;
}

/**
 * @brief Check if the given page is the same as the current page.
 *
 * This function compares the given page with the current page and
 * returns true if they are the same.
 *
 * @param thisPage Pointer to the page to be compared.
 * @return True if the pages are the same, false otherwise.
 */
bool PagingManager::isTheSamePage(struct Page* thisPage) {
    return thisPage == &(pageList.currentPage);
}

/**
 * @brief Initialize the paging manager.
 *
 * This function initializes the pages and sets up initial view of status page on
 * the console.
 */
void PagingManager::init() {
    // Prepare all pages
    
    // Finally display the status page (the first page)
    pageList.currentPage.fpTitleF(PagingManager::rOutputStream, PagingManager::hConsole);
}

/**
 * @brief Clear the console.
 *
 * This function clears the console.
 */
void PagingManager::clearConsole() {
    // TODO: Implement page clearing mechanism
    COORD topLeft = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    // Get the handle for the console buffer
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the current screen information
    GetConsoleScreenBufferInfo(console, &screen);

    // Fill the entire screen with spaces and reset the cursor position
    FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);

    // Reset cursor position to top-left corner
    SetConsoleCursorPosition(console, topLeft);
}