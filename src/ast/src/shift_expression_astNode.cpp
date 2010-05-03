/***********************************************************************
* shift_expression_astNode - Syntax Tree Node
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

#include <shift_expression_astNode.h>
#include <ast.h>

using namespace std;

shift_expression_astNode::shift_expression_astNode()
	:expression_astNode() {
	nodeType = "shift_expression";
}

shift_expression_astNode::shift_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:expression_astNode(_nodeString, _loc, tree) {
	nodeType = "shift_expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void shift_expression_astNode::output3AC() {
	  std::string op1 = "op1", op2 = "op2", dst = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  getChild(0)->output3AC();
	  op1 = getChild(0)->ret3ac;
	  getChild(2)->output3AC();
	  op2 = getChild(2)->ret3ac;
	 
	  dst = gettacTree()->asTree->genReg();
	  
	  switch(((leaf_astNode*) getChild(1))->getTokenType())
	  {
	    case LEFT_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_LSHIFT, op1, op2, dst, loc);
	      break;
	    case RIGHT_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_RSHIFT, op1, op2, dst, loc);
	      break;	      
	    default:
	      break;
	  }
	  ret3ac = dst;
	  acTree->addNode(ac_node);
}

