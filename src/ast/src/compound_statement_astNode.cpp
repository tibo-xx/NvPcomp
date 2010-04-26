/***********************************************************************
* compound_statement_astNode - Syntax Tree Node
* Copyright (C) 2010 CMT & DRJ & BFB
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* \author CMT, DRJ & BFB
**********************************************************************/

#include <compound_statement_astNode.h>

using namespace std;

compound_statement_astNode::compound_statement_astNode()
	:astNode() {
	nodeType = "compound_statement";
}

compound_statement_astNode::compound_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "compound_statement";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void compound_statement_astNode::output3AC() {
	for (int i = 0; i < getNumberOfChildren(); i ++)
	  getChild(i)->output3AC();
}

