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
		 * @brief Get the next page.
		 *
		 * This function returns the next page.
		 *
		 * @return The next page.
		 */
		Page nextPage();

		/**
		 * @brief Get the previous page.
		 *
		 * This function returns the previous page.
		 *
		 * @return The previous page.
		 */
		Page prevPage();

		/**
		 * @brief Get the m-th page.
		 *
		 * This function returns the m-th page based on the provided index.
		 *
		 * @param m Index of the page to be returned.
		 * @return The m-th page.
		 */
		Page mthPage(uint_fast8_t);

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

	private:
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