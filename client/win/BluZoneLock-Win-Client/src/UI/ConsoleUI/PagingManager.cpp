// PagingManager.cpp

#include "PagingManager.h"
#include "PagesInfo.h"
#include <Windows.h>

// Static instance initialization
static PagingManager* instance = nullptr;
// struct PageList global instance
struct PageList pageList;

PagingManager& PagingManager::getInstance(std::ostream& rOutputStream, HANDLE hConsole) {
    // Lazy initialization of the singleton instance
    if (!instance) {
        instance = new PagingManager(rOutputStream, hConsole);
    }
    return *instance;
}

PagingManager::PagingManager(std::ostream& rOutputStream, HANDLE hConsole)
    : rOutputStream(rOutputStream), hConsole(hConsole) {
    // Constructor implementation
    PagingManager::init();
}

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

Page PagingManager::prevPage() {
    if (pageList.index == 0) {
        pageList.index = 2; // because we are going circular
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

Page PagingManager::mthPage(uint_fast8_t M) {
    if (!(
        M > MAXIMUM_ALLOWED_NUMBER_OF_PAGES && M < MINIMUM_ALLOWED_NUMBER_OF_PAGES
        )) {
        pageList.index = M - 1; // considering that the end-user does not know 0-indexing
        pageList.currentPage = pageList.pageArray[pageList.index];
    }

    // Clear console
    clearConsole();
    // show the title
    pageList.currentPage.fpTitleF(rOutputStream, hConsole);
    // show the header

    return pageList.currentPage; // return a reference to currentPage even in case of faulty M'th page request. Use the function
    // isTheSamePage to know if this currentPage obtained using this function matches the page that the user is on. This prevents
    // huge rewrites to the screen because by the observer pattern, a change is reflected immediately on the console window.
}

bool PagingManager::isTheSamePage(struct Page* thisPage) {
    return thisPage == &(pageList.currentPage);
}

// function to display the initial page ( one-time use function )
void PagingManager::init() {
    // Display the status page (the first page)
    pageList.currentPage.fpTitleF(PagingManager::rOutputStream, PagingManager::hConsole);
}

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