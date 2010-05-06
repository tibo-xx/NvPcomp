/***********************************************************************
* direct_declarator_astNode - Syntax Tree Node
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

#include <direct_declarator_astNode.h>

using namespace std;

direct_declarator_astNode::direct_declarator_astNode()
	:astNode() {
	nodeType = "direct_declarator";
}

direct_declarator_astNode::direct_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "direct_declarator";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}
/*
direct_declarator_astNode::direct_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree, declaratorType type)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "direct_declarator";
	_type = type;
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}*/

void direct_declarator_astNode::output3AC() {
	LOG(ASTLog, logLEVEL1) << nodeType << " is not supported at this time" << nodeString;
}

/*
void direct_declarator_astNode::updateVariableTable(variableTable *v_table, NvPcomp::symTable *table) {
	astNode *asNode;
	NvPcomp::symNode *smNode;
	variableInfo* info;

	asNode = getChild(0);
	table->search(asNode->getString(), smNode, false);

	cout << "Starting to update variableTable..." << endl;

	if(smNode) {
		cout << "\tFound symNode..." << endl;
		if(v_table->search(smNode->getMangledName(), info)) {
			cout << "\tFound mangledName in variableTable..." << endl;
			info->isArray = true;
			asNode = getChild(2);
			info->elements = atoi(asNode->getString().c_str());
		}		
	}
}
*/
