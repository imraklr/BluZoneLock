/**
 * @file PagingManager.h
 * @brief This header file contains the class definition, which includes the class 
 * declaration, member functions, and member variables.
 *
 * @author Rakesh Kumar
 */
#pragma once

#ifndef PAGING_MANAGER_H
#define PAGING_MANAGER_H

#include <stdint.h>
#include <ostream>
#include <Windows.h>
#include <stdint.h>
#include <sal.h>

#include "PagesInfo.h"

 /**
  * @class PagingManager
  * @brief Manages paging operations for an application.
  *
  * The PagingManager class is responsible for managing pages within an application.
  * It provides methods to navigate between pages, clear the console, and check if
  * a given page is the same as the current one. The class follows the singleton
  * design pattern to ensure that only one instance of PagingManager exists.
  */
class PagingManager {

	public:

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
		static PagingManager& getInstance(std::ostream& rOutputStream, HANDLE hConsole);
		
		// Prevent copying
		PagingManager(PagingManager const&) = delete;
		
		// Prevent assignment
		void operator=(PagingManager const&) = delete;

		/**
		 * @brief Get the pointer to next page.
		 *
		 * This function returns the pointer to the next page.
		 *
		 * @return Pointer to next page.
		 */
		Page* nextPage();

		/**
		 * @brief Get the pointer to previous page.
		 *
		 * This function returns the pointer to the previous page.
		 *
		 * @return Pointer to previous page.
		 */
		Page* prevPage();

		/**
		 * @brief Get the pointer to m-th page.
		 *
		 * This function returns the pointer to the m-th page based on the provided index.
		 *
		 * @param m Index of the page to be returned.
		 * @return The m-th page.
		 */
		Page* mthPage(uint_fast8_t);

		/**
		 * @brief Check if the given page is the same as the current page.
		 *
		 * This function compares the given page with the current page and
		 * returns true if they are the same.
		 *
		 * @param thisPage Pointer to the page to be compared.
		 * @return True if the pages are the same, false otherwise.
		 */
		bool isTheSamePage(struct Page* thisPage);

		/**
		 * @brief Clear the console.
		 *
		 * This function clears the console.
		 */
		void clearConsole();

		/**
		* @brief Get the page number of the current page.
		* 
		* @return A number whose minimum value will be 1 and maximum will be MAXIMUM_ALLOWED_NUMBER_OF_PAGES 
		* indicating the page number. Note that this function does not return the index of the array at which
		* this current page is located.
		*/
		uint_fast8_t getCurrentPageNumber();

		/**
		* @brief Get the current page as a pointer to `struct Page` type.
		* 
		* @return A poinnter to `struct Page` type which is the current page visible to the user through console.
		*/
		struct Page* getPointerToCurrentPage();

		/**
		* @brief Get the N'th as a pointer to `struct Page` type.
		* 
		* @param N Index of the page (not the page number)
		* 
		* @return A poinnter to `struct Page` type from the array.
		*/
		struct Page* getPointerToNthPage(uint_fast8_t N);

		/**
		* @brief Show entire page (title, header (if any), body (if any) and footer (if any) sections)
		* 
		* @param pageNumber The page number of the page whose each is to be displayed.
		*/
		void showPage(uint_fast8_t pageNumber);

		/**
		* @brief Show title section only of page specified by page number in the parameter.
		* 
		* Note that direct calls to printing any section like in this function does not 
		* guarantee nullptr checks
		* 
		* @param pageNumber The page number of the page whose title section is to be displayed.
		*/
		void showTitle(uint_fast8_t pageNumber);
		
		/**
		* @brief Show header section only of page specified by page number in the parameter.
		* 
		* Note that direct calls to printing any section like in this function does not 
		* guarantee nullptr checks
		*
		* @param pageNumber The page number of the page whose header section is to be displayed.
		*/
		void showHeader(uint_fast8_t pageNumber);

		/**
		* @brief Show body section only of page specified by page number in the parameter.
		* 
		* Note that direct calls to printing any section like in this function does not 
		* guarantee nullptr checks
		*
		* @param pageNumber The page number of the page whose body section is to be displayed.
		*/
		void showBody(uint_fast8_t pageNumber);

		/**
		* @brief Show footer section only of page specified by page number in the parameter.
		* 
		* Note that direct calls to printing any section like in this function does not 
		* guarantee nullptr checks
		*
		* @param pageNumber The page number of the page whose footer section is to be displayed.
		*/
		void showFooter(uint_fast8_t pageNumber);

	private:
		// page number
		_Field_range_(MINIMUM_ALLOWED_NUMBER_OF_PAGES, MAXIMUM_ALLOWED_NUMBER_OF_PAGES) uint_fast8_t pageNumber;

		// Array of struct Page
		struct Page pageArray[MAXIMUM_ALLOWED_NUMBER_OF_PAGES];

		// Pointer to current page which is visible to the user
		struct Page* currentPage;

		// Reference to the output stream.
		std::ostream& rOutputStream;

		//Handle to the console.
		HANDLE hConsole;

		/**
		* @brief Constructor.
		*
		* This constructor initializes the PagingManager with the provided
		* output stream and console handle. It is private to enforce the singleton pattern.
		*
		* @param rOutputStream Reference to an output stream.
		* @param hConsole Handle to the console.
		*/
		PagingManager(std::ostream& rOutputStream, HANDLE hConsole);

		/**
		* @brief Initialize the paging manager.
		*
		* This function initializes the pages and sets up initial view of status page on 
		* the console.
		*/
		void init();
};

#endif