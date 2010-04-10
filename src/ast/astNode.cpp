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
#include <astNode.h>
#include <string.h>
#include <iostream>

using namespace std;

astNode::astNode() {
	nodeString = "empty";
}

astNode::astNode(string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree) {
	loc = _loc;
	nodeString = _nodeString;
	acTree = tree;
}

void astNode::setString(string _nodeString)
{
	nodeString = _nodeString;
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

NvPcomp::location astNode::getLocation() {
	return loc;
}

NvPcomp::tacTree *astNode::gettacTree() {
	return acTree;
}

void astNode::printNode(bool printProductions, int level) {
		
	if (!(nodeString == "" && printProductions == false))
	{
		if (printProductions)
			LOG(ASTLog, logLEVEL1) << string(level, ' ') << nodeType << ":" << nodeString;
		else
			LOG(ASTLog, logLEVEL1) << string(level, ' ') << nodeString;
	}
	else
		LOG(ASTLog, logLEVEL1) << " ";
		
	for (unsigned int i=0; i < children.size(); i++)
	{
		if(children[i])
			children[i]->printNode(printProductions, level+1);
		else
			LOG(ERRORLog, logLEVEL1) << "!!!!!!!!!!!nil node found in AST!!!!!!!!!!!!";
	}
}
