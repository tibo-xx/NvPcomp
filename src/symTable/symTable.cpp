/***********************************************************************
 *   symTable - Symbol table implementation for NvPcomp
 *   Copyright (C) 2010  CMT & DRJ
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
#include <symTable.h>
#include <NvPcomp_logger.h>

using namespace std;

/**********************************************************************/
// symTable logging declarations
LOG2FILE(SymbolDump_2File);
class SymbolDump : public NvPcomp_logger<SymbolDump_2File> {};
/**********************************************************************/

symTable::symTable() {
	// Push on the first level.
	_level = -1;
	this->push();
}

symTable::symTable(FILE* out) {
	// Push on the first level.
	_level = -1;
	this->push();
	SET_OUTPUT(SymbolDump, out);
}

symTable::~symTable() {
	vector<map<string, symNode *> *>::iterator iter;
	map<string, symNode *>::iterator map_iter;
		
	for(iter = _table.begin(); iter < _table.end(); iter++) {
		// loop through and delete all of the map symNodes.
		for(map_iter = (*iter)->begin(); map_iter != (*iter)->end(); map_iter++) {
			if((*map_iter).second != NULL) {
				delete (*map_iter).second;
			}
		}
		// Clear out the map.
		(*iter)->clear();
		// Delete the Map object.
		delete (*iter);	
	}
	// Clear the vector
	_table.clear();		
}

bool symTable::insert(string key, symNode *node) {
	pair<map<string, symNode *>::iterator, bool> ret;
	ret = (_table.back())->insert(make_pair(key, node));
	return ret.second;
}

symNode *symTable::search(string key) {
	symNode *retVal = NULL;
	map<string, symNode *>::iterator iter;
	
	iter = (_table.back())->find(key);
	
	if(iter != (_table.back())->end()) {
		retVal = (*iter).second;
	}
	
	return retVal;
}

void symTable::dump() {
	
	int level = 0;
    vector<map<string, symNode *> *>::iterator iter;
	map<string, symNode *>::iterator map_iter;

	LOG(SymbolDump, logLEVEL1) << "Dumping current Symbol Table:";		
	
	for(iter = _table.begin(); iter < _table.end(); iter++) {
		LOG(SymbolDump, logLEVEL1) << string(level, '\t') << "Level: " << level;

		// loop through and print out node information:
		for(map_iter = (*iter)->begin(); map_iter != (*iter)->end(); map_iter++) {
			if((*map_iter).second != NULL) {
				LOG(SymbolDump, logLEVEL1) << string(level, '\t') << (*map_iter).first << ": " << "Node Information.";				
			}
		}
		
		level++;
		
	}		
}

bool symTable::push() {
	bool retVal = true;
	_table.push_back(new map<string, symNode *>);
	_level++;
	return retVal;
}

bool symTable::pop() {
	bool retVal = true;
	
	if(_level > 0) {
		map<string, symNode *>::iterator map_iter;
		map<string, symNode *> *mapPtr = _table.back();
		
		// Loop through and clear the allocated memory.	
		for(map_iter = (mapPtr)->begin(); map_iter != (mapPtr)->end(); map_iter++) {
			if((*map_iter).second != NULL) {
				delete (*map_iter).second;
			}
		}
		// Clear out the map.
		mapPtr->clear();	
		// Delete the Map object.
		delete mapPtr;	
		// pop the map pointer
		_table.pop_back();		
		// Decrement the Level Counter.
		_level--;
	} else {
		retVal = false;
	}
	
	return retVal;
	
}
