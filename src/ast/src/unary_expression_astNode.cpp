/***********************************************************************
* unary_expression_astNode - Syntax Tree Node
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

#include <unary_expression_astNode.h>
#include <ast.h>


using namespace std;

unary_expression_astNode::unary_expression_astNode()
	:expression_astNode() {
	nodeType = "unary_expression";
}

unary_expression_astNode::unary_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:expression_astNode(_nodeString, _loc, tree) {
	nodeType = "unary_expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void unary_expression_astNode::output3AC() {
	if (nodeString == "++ unary_expression" || nodeString == "-- unary_expression")
	{
	  std::string op1 = "op1", dst = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  getChild(1)->output3AC();
	  op1 = getChild(1)->ret3ac;
	  dst = op1;
	  
	  switch(((leaf_astNode*) getChild(0))->getTokenType())
	  {
	    case INC_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_ADD, op1, "1", dst, loc);
	      break;
	    case DEC_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_SUB, op1, "1", dst, loc);
	      break;	      
	    default:
	      break;
	  }
	  ret3ac = op1;
	  acTree->addNode(ac_node);
	}
}

