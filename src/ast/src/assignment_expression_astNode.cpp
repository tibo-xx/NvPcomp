/***********************************************************************
* assignment_expression_astNode - Syntax Tree Node
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

#include <assignment_expression_astNode.h>

using namespace std;

assignment_expression_astNode::assignment_expression_astNode()
	:expression_astNode() {
	nodeType = "assignment_expression";
}

assignment_expression_astNode::assignment_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:expression_astNode(_nodeString, _loc, tree) {
	nodeType = "assignment_expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void assignment_expression_astNode::output3AC() {
	if (nodeString == "unary_expression assignment_operator assignment_expression")
	{
	  std::string lhs = "lhs",rhs = "rhs";
	  getChild(0)->output3AC();
	  getChild(2)->output3AC();
	  NvPcomp::tacNode * ac_node;
	  
	  rhs = getChild(2)->ret3ac;
	  lhs = getChild(0)->ret3ac;
	  
	  switch(((leaf_astNode*) getChild(1))->getTokenType())
	  {
	    case EQUAL_TK:
	      ac_node = new NvPcomp::tacNode("", OP_ASSIGN, rhs, "", lhs, loc);
	      acTree->addNode(ac_node);	  
	      break;
	    default:
	      break;
	  }
	  ret3ac = lhs;
	}
	else if (nodeString == "declarator EQUAL_TK initializer")
	{
	  std::string lhs = "lhs",rhs = "rhs";
	  getChild(2)->output3AC();
	  NvPcomp::tacNode * ac_node;
	  
	  rhs = getChild(2)->ret3ac;
	  lhs = getChild(0)->ret3ac;
	  
	  switch(((leaf_astNode*) getChild(1))->getTokenType())
	  {
	    case EQUAL_TK:
	      ac_node = new NvPcomp::tacNode("", OP_ASSIGN, rhs, "", lhs, loc);
	      break;
	    default:
	      break;
	  }
	  acTree->addNode(ac_node);	  
	}
}

