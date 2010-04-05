/***********************************************************************
* leaf_astNode - Syntax Tree Node
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

#include <leaf_astNode.h>

using namespace std;

leaf_astNode::leaf_astNode()
	:astNode() {
	nodeType = "leaf";
}

leaf_astNode::leaf_astNode(std::string _nodeString, NvPcomp::location _loc)
	:astNode(_nodeString, _loc) {
	nodeType = "leaf";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void leaf_astNode::output3AC() {}

