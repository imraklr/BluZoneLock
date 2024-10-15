/**
 * @file status.h
 *
 * @author Rakesh Kumar
 */

#pragma once

#include <string>
#include <windows.h>
#include <iostream>
#include <stdint.h>
#include "../../Utils/Utils.h"

#ifndef APPLICATION_NAME_LENGTH
#define APPLICATION_NAME_LENGTH 11
#endif

void writeTitle(std::ostream& rOutputStream, HANDLE hConsole);

void initPage(std::ostream& rOutputStream, HANDLE hConsole);