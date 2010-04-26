/***********************************************************************
* expression_astNode - Syntax Tree Node
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

#include <expression_astNode.h>

using namespace std;

expression_astNode::expression_astNode()
	:astNode() {
	nodeType = "expression";
}

expression_astNode::expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

expression_astNode::~expression_astNode() {}

void expression_astNode::output3AC() {
	LOG(ASTLog, logLEVEL1) << nodeType << " is not supported at this time" << nodeString;
}

bool expression_astNode::checkType(NvPcomp::symTable *table) {
	
	leaf_astNode *lhs;
	leaf_astNode *rhs;
	NvPcomp::symNode* stNode_lhs;
	NvPcomp::symNode* stNode_rhs;
	bool retVal = true;

	// We're assuming that we have three nodes right now, left-hand-side, operator, right-hand-side.
	lhs = (leaf_astNode*) children.at(0);
	rhs = (leaf_astNode*) children.at(2);

	// Is the lhs in the symbol table?
	if(table->search(lhs->getString(), stNode_lhs, false) < 0) {
		retVal = false;
	} else {		
		// Check the right hand side to see if this is a constant or another variable.
		if(IDENTIFIER_TK == rhs->getTokenType()) {
			// The right-hand-side is an identifier, grab its symbol table node.
			if(table->search(rhs->getString(), stNode_rhs, false) < 0) {
				retVal = false;
			} else {
				// Compare the types of the two identifiers.
				retVal = checkTypes(stNode_lhs, stNode_rhs);
			}
		} else {
			// Compare the type of the left-hand-side with the constant.
			retVal = checkTypes(stNode_lhs, rhs);
		}
	}
	return retVal;
}

bool expression_astNode::checkTypes(NvPcomp::symNode* lhs, NvPcomp::symNode* rhs) {
	return true;
}

bool expression_astNode::checkTypes(NvPcomp::symNode* lhs, leaf_astNode* rhs) {
	
	yytokentype tempToken = (yytokentype)rhs->getTokenType();
	bool retVal = false;
	
	switch(tempToken) {
		case INTEGER_CONSTANT_TK:
			retVal = lhs->hasType(INT_TK) || lhs->hasType(LONG_TK) || lhs->hasType(SHORT_TK);
			break;		
		case FLOATING_CONSTANT_TK:
			retVal = lhs->hasType(FLOAT_TK) || lhs->hasType(DOUBLE_TK);
			break;
		case CHARACTER_CONSTANT_TK:
			retVal = lhs->hasType(CHAR_TK);
			break;
		default:
			retVal = false;
			break;
	}
		
	return retVal;
	
}

