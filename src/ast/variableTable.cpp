/***********************************************************************
 *   variableTable - Variable table implementation for NvPcomp
 *   Copyright (C) 2010  CMT, DRJ & BFB
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 **********************************************************************/
#include <variableTable.h>

using namespace std;

variableTable::variableTable() {
	
}

variableTable::~variableTable() {}

string variableTable::insert(std::string key, int memLocation) {
	string retVal = "";
	
	return retVal;
}

void variableTable::setMemLocation(std::string key, int memLocation) {
	
}

bool variableTable::search(const std::string key, int &memLocation) {
	bool retVal = false;
	
	return retVal;
}


// Protected functions.
bool variableTable::search(const std::string key) {
	bool retVal = false;
	
	return retVal;
}
