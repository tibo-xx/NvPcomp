/***********************************************************************
* selection_statement_astNode - Syntax Tree Node
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

#include <selection_statement_astNode.h>
#include <ast.h>

using namespace std;

selection_statement_astNode::selection_statement_astNode()
	:astNode() {
	nodeType = "selection_statement";
}

selection_statement_astNode::selection_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "selection_statement";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void selection_statement_astNode::output3AC() {
	if (nodeString == "IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement")
	{
	  std::string expression = "op1", statement = "op2", dst = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  // evaluate expression
	  getChild(2)->output3AC();
	  expression = getChild(2)->ret3ac;
	  dst = gettacTree()->asTree->genLabel();
	  
	  // j if = 0
	  ac_node = new NvPcomp::tacNode("", OP_BREQ, expression, "0", dst, loc);
	  acTree->addNode(ac_node);

	  // evaluate statement
	  getChild(4)->output3AC();

	  // our label to jump to
	  ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", dst, loc);
	  acTree->addNode(ac_node);	  
	}
	else if (nodeString == "IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement")
	{
	  std::string expression = "op1", statement = "op2", dst = "dst", dst2 = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  // evaluate expression
	  getChild(2)->output3AC();
	  expression = getChild(2)->ret3ac;
	  dst = gettacTree()->asTree->genLabel();
	  dst2 = gettacTree()->asTree->genLabel();
	  
	  // j if = 0
	  ac_node = new NvPcomp::tacNode("", OP_BREQ, expression, "0", dst, loc);
	  acTree->addNode(ac_node);
	  
	  // evaluate statement
	  getChild(4)->output3AC();
	  // jump out
	  ac_node = new NvPcomp::tacNode("", OP_BR, "", "", dst2, loc);
	  acTree->addNode(ac_node);
	  
	  // our else label to jump to
	  ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", dst, loc);
	  acTree->addNode(ac_node);	  
	  
	  getChild(6)->output3AC();

	  // our non-else label to jump to
	  ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", dst2, loc);
	  acTree->addNode(ac_node);	  

	}
}

