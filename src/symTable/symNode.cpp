/***********************************************************************
 *   symNode - Symbol Table Node.
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
#include <symNode.h>

using namespace std;

NvPcomp::symNode::symNode(NvPcomp::location loc, \
							string key, \
							string strType) {
	_loc = loc;
	_key = key;
	_strType = strType;	
}

NvPcomp::symNode::~symNode() 
{
	
}

void NvPcomp::symNode::addType(int type) {
	_type.push_back(type);
}

int NvPcomp::symNode::getTopType() {
	
	int retVal = -1;
	if(!_type.empty()) {
		retVal = _type.front();
	}
	
	return  retVal;
}

int NvPcomp::symNode::popType() {
	int retVal;
	
	if(_type.empty()) {
		retVal = 0;
	} else {
		_type.pop_back();
		retVal = _type.size();		
	}
	
	return retVal;
	
}





