/***********************************************************************
* iteration_statement_astNode - Syntax Tree Node
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

#include <iteration_statement_astNode.h>
#include <ast.h>

using namespace std;

iteration_statement_astNode::iteration_statement_astNode()
	:astNode() {
	nodeType = "iteration_statement";
}

iteration_statement_astNode::iteration_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "iteration_statement";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
	e1_child = e2_child = e3_child = -1;
}

void iteration_statement_astNode::output3AC() {
	if (nodeString == "DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK")
	{
	  std::string expression = "op1", statement = "op2", do_label = "dst", done_label = "dst";
	  NvPcomp::tacNode * ac_node;
	  
	  do_label = gettacTree()->asTree->genLabel();
	  done_label = gettacTree()->asTree->genLabel();
	  	  
	  // loop label
	  ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", do_label, loc);
	  acTree->addNode(ac_node);	  
	  
	  // evaluate statement
	  getChild(1)->output3AC();

	  // evaluate expression
	  getChild(4)->output3AC();
	  expression = getChild(4)->ret3ac;
	  
	  // jump to loop if != 0
	  ac_node = new NvPcomp::tacNode("", OP_BRNE, expression, "0", do_label, loc);
	  acTree->addNode(ac_node);
	}
	else
	{
	  std::string e1 = "", e2 = "", e3 = "", statement = "", while_label = "dst", done_label = "dst";
	    
	    NvPcomp::tacNode * ac_node;
	    
	    while_label = gettacTree()->asTree->genLabel();
	    done_label = gettacTree()->asTree->genLabel();
		    
	    // evaluate init expression
	    if (e1_child >= 0)
	    {
	      getChild(e1_child)->output3AC();
	      e1 = getChild(e1_child)->ret3ac;
	    }
	    
	    // loop label
	    ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", while_label, loc);
	    acTree->addNode(ac_node);	  
	    
	    // evaluate loop expression
	    if (e2_child >= 0)
	    {
	      getChild(e2_child)->output3AC();
	      e2 = getChild(e2_child)->ret3ac;
	    }
	    else
	      e2 = "1";
	    
	    // jump to done if loop expression  (e2) = 0
	    ac_node = new NvPcomp::tacNode("", OP_BREQ, e2, "0", done_label, loc);
	    acTree->addNode(ac_node);

	    // evaluate statement
	    getChild(statement_child)->output3AC();

	    // evaluate iterative expression
	    if (e3_child >= 0)
	    {
	      getChild(e3_child)->output3AC();
	      e3 = getChild(e3_child)->ret3ac;	      
	    }
	    
	    // loop
	    ac_node = new NvPcomp::tacNode("", OP_BR, "", "", while_label, loc);
	    acTree->addNode(ac_node);

	    // our label to jump to when done
	    ac_node = new NvPcomp::tacNode("", OP_LABEL, "", "", done_label, loc);
	    acTree->addNode(ac_node);	  	  

	}
}

