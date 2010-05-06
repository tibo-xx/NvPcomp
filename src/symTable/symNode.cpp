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
/*!  Symbol Table Node
 *  \file symNode.cpp
 *  \class symNode
 *  \brief Class for the symbol table node
 *  \author CMT, DRJ & BFB
 */
#include <symNode.h>

using namespace std;

NvPcomp::symNode::symNode(NvPcomp::location loc, \
							string key, \
							string strType) {
	_loc = loc;
	_key = key;
	_strType = strType;
	_mangledName = "";
}

NvPcomp::symNode::~symNode() 
{
	
}

bool NvPcomp::symNode::hasType()
{
   bool ret = false;
   if(!_type.empty())
   {
     ret = true;
     // if this is an otherwise empty typedef
     if (_type.size() == 1 && _type.end() != find (_type.begin(), _type.end(), 298 /*TYPEDEF_NAME_TK*/))
	ret = false;
   }
   return ret;
}

bool NvPcomp::symNode::hasType(int token_type)
{  
   bool result = (_type.end() != find (_type.begin(), _type.end(), token_type));
   return result;
}

void NvPcomp::symNode::addType(int type) {
	_type.push_back(type);
}

int NvPcomp::symNode::getNumberOfTypes()
{
    return _type.size();
}

int NvPcomp::symNode::getTypeByIndex(int index)
{
    return _type[index];
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

void NvPcomp::symNode::setMangledName(string newName) {
	_mangledName = newName;
}
	
string NvPcomp::symNode::getMangledName() {
	return _mangledName;
}




int NvPcomp::symNode::getNumberOfPointerTypes() {
    return _pointerType.size();
}

void NvPcomp::symNode::addPointerType(int type) {
	_pointerType.push_back(type);
}

bool NvPcomp::symNode::hasPointerType(int token_type) {  
   bool result = (_pointerType.end() != find (_pointerType.begin(), _pointerType.end(), token_type));
   return result;
}

int NvPcomp::symNode::getPointerTypeByIndex(int index) {
    return _pointerType[index];
}
