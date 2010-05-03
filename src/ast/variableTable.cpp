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
	
string variableTable::insert(std::string key, variableInfo *info) {
	string retVal = "";
	bool unsuccessful = true;
	string newKey;
	int suffix = 1;

	while(unsuccessful) {
		newKey = mangleName(key, suffix);		
		
		pair<map<string, variableInfo *>::iterator, bool> ret;
		ret = _table.insert(make_pair(newKey, info));
		
		// The node was inserted correctly.
		if(ret.second) {
			unsuccessful = false;
			retVal = newKey;
		} else {
			suffix++;
		}
		
	}
	
	return retVal;

}

void variableTable::print() {

	map<string, variableInfo *>::iterator map_iter;
	
	cout << "Table:" << endl;
	
	for(map_iter = _table.begin(); map_iter != _table.end(); map_iter++) {
		cout << "\t" << (*map_iter).first << endl;
	}
	
}

bool variableTable::setMemLocation(std::string key, int memLocation) {
	variableInfo *info;
	bool retVal = false;
	if(search(key, info)) {
		info->memLocation = memLocation;
		retVal = true;
	}
	
	return retVal;	
}

bool variableTable::setVariableSize(std::string key, int size) {
	variableInfo *info;
	bool retVal = false;
	
	if(search(key, info)) {
		info->size = size;
		retVal = true;
	}
	
	return retVal;		
}

bool variableTable::setVariableInfo(std::string key, variableInfo *info_in) {
	variableInfo *info;
	bool retVal = false;
	
	if(search(key, info)) {
		info->memLocation = info_in->memLocation;
		info->size = info_in->size;
		retVal = true;
	}
	
	return retVal;		
}

bool variableTable::search(const std::string key, variableInfo* &info) {
	
	bool retVal = false;	
	map<string, variableInfo *>::iterator iter;
 
	iter = _table.find(key);
 
	if(iter != _table.end()) {
		info = (*iter).second;
		retVal = true;
	}
	
	return retVal;

}

////////////////////////////////////////////////////////////////////////
// Protected functions.
////////////////////////////////////////////////////////////////////////
bool variableTable::search(const std::string key) {
	bool retVal = false;
		
	map<string, variableInfo *>::iterator iter;
 
	iter = _table.find(key);
 
	if(iter != _table.end()) {
		retVal = true;
	}
	
	return retVal;
}

string variableTable::mangleName(std::string key, int suffix) {
	string newKey = key;
	stringstream suffixStr;
	stringstream retVal;
	int suffixSize;
	suffixStr << suffix;	
	suffixSize = suffixStr.str().size();
	
	retVal << key.substr(0, MAXNAMELENGTH - suffixSize -1 ) << suffixStr.str();
	
	return retVal.str();
}
