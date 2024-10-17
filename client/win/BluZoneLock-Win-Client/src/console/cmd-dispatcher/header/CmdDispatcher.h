/**
 * @file CmdDispatcher.h
 * @brief This file contains CmdDispatcher class whose functions
 * are used to dispatch commands to specific command class instance.
 *
 * @author Rakesh Kumar
 */

#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class CmdDispatcher {
	public:

		static CmdDispatcher& getInstance();

		CmdDispatcher(const CmdDispatcher&) = delete;
		CmdDispatcher& operator=(const CmdDispatcher&) = delete;

		void dispatch(std::string input);
	private:
		~CmdDispatcher();
		CmdDispatcher();

		std::list<std::string> allCmds;
		void initCoreCommands();
};