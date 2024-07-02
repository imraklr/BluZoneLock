// PagingManager.h
#pragma once

#ifndef PAGING_MANAGER_H
#define PAGING_MANAGER_H

#include <stdint.h>
#include <ostream>
#include <Windows.h>

#include "PagesInfo.h"

class PagingManager {

	public:

		static PagingManager& getInstance(std::ostream& rOutputStream, HANDLE hConsole);
		// prevent copying
		PagingManager(PagingManager const&) = delete;
		// prevent assignment
		void operator=(PagingManager const&) = delete;

		Page nextPage();
		Page prevPage();
		Page mthPage(uint_fast8_t);

		bool isTheSamePage(struct Page* thisPage);

		void clearConsole();

	private:
		std::ostream& rOutputStream;
		HANDLE hConsole;

		PagingManager(std::ostream& rOutputStream, HANDLE hConsole);

		void init();
};

#endif