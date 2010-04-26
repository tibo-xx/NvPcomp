/***********************************************************************
* function_definition_astNode - Syntax Tree Node
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

#include <function_definition_astNode.h>

using namespace std;

function_definition_astNode::function_definition_astNode()
	:astNode() {
	nodeType = "function_definition";
}

function_definition_astNode::function_definition_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree, NvPcomp::symTable *_table)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "function_definition";
	table = _table;
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void function_definition_astNode::output3AC() {
	if (nodeString == "declarator declaration_list compound_statement")
	{
	  // get the declarator
	  declarator_astNode* node = (declarator_astNode*) getChild(2)->getChild(0);
	  // get our name for use as label
	  std::string label = table->search_top(node->getName())->getMangledName();
	  cout << label << endl;
	}
}

