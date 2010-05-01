/***********************************************************************
* relational_expression_astNode - Syntax Tree Node
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

#include <relational_expression_astNode.h>
#include <ast.h>

using namespace std;

relational_expression_astNode::relational_expression_astNode()
	:expression_astNode() {
	nodeType = "relational_expression";
}

relational_expression_astNode::relational_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:expression_astNode(_nodeString, _loc, tree) {
	nodeType = "relational_expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void relational_expression_astNode::output3AC() {
	  std::string op1 = "op1", op2 = "op2", dst = "dst";
	  getChild(0)->output3AC();
	  getChild(2)->output3AC();
	  NvPcomp::tacNode * ac_node;
	  
	  op1 = getChild(0)->ret3ac;
	  op2 = getChild(2)->ret3ac;
	  dst = gettacTree()->asTree->genReg();
  
	  switch(((leaf_astNode*) getChild(1))->getTokenType())
	  {
	    case LT_TK:
	      ac_node = new NvPcomp::tacNode("", OP_LT, op1, op2, dst, loc);
	      break;
	    case LE_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_LE, op1, op2, dst, loc);
	      break;	      
	    case GT_TK:
	      ac_node = new NvPcomp::tacNode("", OP_GT, op1, op2, dst, loc);
	      break;
	    case GE_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_GE, op1, op2, dst, loc);
	      break;	      
	    default:
	      break;
	  }
	  ret3ac = dst;
	  acTree->addNode(ac_node);
}

