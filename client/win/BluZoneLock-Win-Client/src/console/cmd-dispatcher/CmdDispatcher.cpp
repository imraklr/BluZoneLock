/**
 * @file CmdDispatcher.cpp
 * @brief This file contains CmdDispatcher class implementation whose functions
 * are used to dispatch commands to specific command class instance.
 *
 * @author Rakesh Kumar
 */

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "header/CmdDispatcher.h"

CmdDispatcher::CmdDispatcher() {
	initCoreCommands();
}

CmdDispatcher::~CmdDispatcher() {
	std::cout << "Destructing command dispatcher..." << std::endl;
}

CmdDispatcher& CmdDispatcher::getInstance() {
	static CmdDispatcher instance;
	return instance;
}

void CmdDispatcher::dispatch(std::string input) {
	// check if the command exists
	auto it = std::find(allCmds.begin(), allCmds.end(), input);
	if (it != allCmds.end()) {
		if (input == "connect") {
			// connectCommand.act();
		}
		else if(input == "status") {
			// statusCommand.act();
		}
		else if(input == "disconnect") {
			// disconnectCommand.act();
		}
		else if (input == "exit") {
			// exitCommand.act();
		}
	}
}

void CmdDispatcher::initCoreCommands() {
	allCmds.push_back("connect");
	allCmds.push_back("status");
	allCmds.push_back("disconnect");
	allCmds.push_back("exit");
}