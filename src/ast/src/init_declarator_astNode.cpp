/***********************************************************************
* init_declarator_astNode - Syntax Tree Node
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

#include <init_declarator_astNode.h>

using namespace std;

init_declarator_astNode::init_declarator_astNode()
	:astNode() {
	nodeType = "init_declarator";
}

init_declarator_astNode::init_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "init_declarator";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void init_declarator_astNode::output3AC() {
	LOG(ASTLog, logLEVEL1) << nodeType << " is not supported at this time" << nodeString;
}

bool init_declarator_astNode::setSpecifiers(declaration_specifiers_astNode* declaration_specifiers, NvPcomp::symTable *table ) {

	string identifier;
	if (children[0]->nodeString == ":pointer direct_declarator")
	  identifier = children[0]->children[1]->nodeString;
	else
	  identifier = children[0]->children[0]->nodeString;

	NvPcomp::symNode* st_node = table->search_top(identifier);
        if (st_node->hasType())
	  return false;
	      
	for (unsigned int i = 0; i < declaration_specifiers->children.size(); i ++)
	{
	  st_node->addType( ((leaf_astNode*) declaration_specifiers->children[0])->getTokenType());
	}
	return true;
}
