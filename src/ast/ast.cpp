/***********************************************************************
 *   astNode - Syntax Tree Node
 *   Copyright (C) 2010  CMT & DRJ & BFB
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
 * 	\author CMT, DRJ & BFB
 **********************************************************************/
#include <ast.h>
#include <string.h>
#include <iostream>

using namespace std;

astNode::astNode() {
	nodeType = "empty";
}
astNode::astNode(string _nodeType) {
	nodeType = _nodeType;
}

void astNode::addChild(astNode* child)
{
	children.push_back(child);
}

void astNode::setType(string _nodeType)
{
	nodeType = _nodeType;
}

string astNode::getType()
{
	return nodeType;
}

void astNode::printNode(int level) {
	for (int i=0; i < level; i++)
	{
		cout << " ";	
	}	
	cout << nodeType << ":" << this << endl;
	for (int i=0; i < children.size(); i++)
	{
		children[i]->printNode(level+1);
	}
}