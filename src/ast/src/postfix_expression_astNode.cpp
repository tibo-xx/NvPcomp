/***********************************************************************
* postfix_expression_astNode - Syntax Tree Node
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

#include <postfix_expression_astNode.h>
#include <ast.h>

using namespace std;

postfix_expression_astNode::postfix_expression_astNode()
	:expression_astNode() {
	nodeType = "postfix_expression";
}

postfix_expression_astNode::postfix_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:expression_astNode(_nodeString, _loc, tree) {
	nodeType = "postfix_expression";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void postfix_expression_astNode::output3AC() {

	// function call
	if (nodeString == "postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK")
	{
	  std::string lhs = "",rhs = "";
	  getChild(0)->output3AC();
	  getChild(2)->output3AC();
	  NvPcomp::tacNode * ac_node;
	  
	  lhs = getChild(0)->getString();	 
	  
	  ac_node = new NvPcomp::tacNode("", OP_CALL, lhs, "", "", loc);

	  acTree->addNode(ac_node);	  
	  ret3ac = lhs;
	}
	if (nodeString == "postfix_expression ++" || nodeString == "postfix_expression --")
	{
	  std::string op1 = "op1", dst = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  getChild(0)->output3AC();
	  op1 = getChild(0)->ret3ac;
	  
	  // we need a register because this is a post inc/dec, so our value for the rest 
	  // of the expression is our value pre-inc or pre-dec
	  dst = gettacTree()->asTree->genReg();
	  
	  switch(((leaf_astNode*) getChild(1))->getTokenType())
	  {
	    case INC_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_ADD, op1, "1", dst, loc);
	      acTree->addNode(ac_node);
	      ac_node = new NvPcomp::tacNode("", OP_ASSIGN, dst, "", op1, loc);
	      acTree->addNode(ac_node);
	      break;
	    case DEC_OP_TK:
	      ac_node = new NvPcomp::tacNode("", OP_SUB, op1, "1", dst, loc);
	      acTree->addNode(ac_node);
	      ac_node = new NvPcomp::tacNode("", OP_ASSIGN, dst, "", op1, loc);
	      acTree->addNode(ac_node);
	      break;	      
	    default:
	      break;
	  }
	  ret3ac = dst;
	}
}

