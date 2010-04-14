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

bool init_declarator_astNode::setSpecifiers(declaration_specifiers_astNode* declaration_specifiers, NvPcomp::symTable *table, variableTable *v_table, string &error ) {

	string identifier;
	bool is_pointer = false;
	if (children[0]->getString() == ":pointer direct_declarator")
	{
	  identifier = children[0]->getChild(1)->getString();
	  is_pointer = true;
	}
	else
	  identifier = children[0]->getChild(0)->getString();

	NvPcomp::symNode* st_node = table->search_top(identifier);
        if (st_node->hasType())
	{
	  error = "SYNTAX ERROR: Redeclaration of '" + identifier + "'";
	  return false;
	}     
	// Add specifiers
	for (int i = 0; i < declaration_specifiers->getNumberOfChildren(); i ++)
	{
	  int token_type = ((leaf_astNode*) declaration_specifiers->getChild(i))->getTokenType();
	  // If this is a typedef, add the types from the typedef st_node
	  if (token_type == TYPEDEF_NAME_TK)
	  {
	    NvPcomp::symNode* typedef_st_node = table->search_top(declaration_specifiers->getChild(i)->getString());
	    for (int j = 0; j < typedef_st_node->getNumberOfTypes(); j++)
	    {
	      int token_type = typedef_st_node->getTypeByIndex(j);
	      if (token_type != TYPEDEF_NAME_TK)
	      {
		cout << "Adding type " << token_type  << " from typedef" << endl;
		if (!addType(token_type, st_node, error))
		  return false; // we had an error
	      }
	    }
	  }
	  else if (!addType(token_type, st_node, error))
	    return false;
	}
	// Add pointer information
	if (is_pointer)
	{
	  for (int i = 0; i < children[0]->getChild(0)->getNumberOfChildren(); i ++)
	  {
	    if (children[0]->getChild(0)->getChild(i)->getString() == ":type_qualifier")
	    {
	      for (int j = 0; j < children[0]->getChild(0)->getChild(i)->getNumberOfChildren(); j ++)
	      {
		int token_type = ((leaf_astNode*) children[0]->getChild(0)->getChild(i)->getChild(j))->getTokenType();
		st_node->addType(token_type);
		cout << "Adding pointer type " << children[0]->getChild(0)->getChild(i)->getChild(j)->getString() << endl;
	      }
	    }
	    else
	    {
	      int token_type = ((leaf_astNode*) children[0]->getChild(0)->getChild(i))->getTokenType();
	      st_node->addType(token_type);
	      cout << "Adding pointer type " << children[0]->getChild(0)->getChild(i)->getString() << endl;
	    }
	  }	 
	}
	variableInfo new_var;
	st_node->setMangledName(v_table->insert(identifier, &new_var));
	return true;
}

bool init_declarator_astNode::addType(int token_type, NvPcomp::symNode *st_node, std::string &error)
{
	  string identifier(st_node->_key);
	  switch(token_type)
	  {
	    case INT_TK:
	    case CHAR_TK:
	    case FLOAT_TK:
	    case DOUBLE_TK:
	      if ( st_node->hasType(DOUBLE_TK) ||
		   st_node->hasType(CHAR_TK) ||
		   st_node->hasType(FLOAT_TK) ||
		   st_node->hasType(INT_TK))
	      {
		error = "SYNTAX ERROR: '" + identifier + "' has two or more data types in delcaration";
		return false;
	      }
	      break;
	      
	    case SIGNED_TK:
	      if ( st_node->hasType(UNSIGNED_TK))
	      {
		error = "SYNTAX ERROR: '" + identifier + "' specified as both 'signed' and 'unsigned'";
		return false;
	      }      
	      break;
	    case UNSIGNED_TK:
	      if ( st_node->hasType(SIGNED_TK) )
	      {
		error = "SYNTAX ERROR: '" + identifier + "' specified as both 'signed' and 'unsigned'";
		return false;
	      }      
	      break;

	    case LONG_TK:
	      if ( st_node->hasType(SHORT_TK))
	      {
		error = "SYNTAX ERROR: '" + identifier + "' specified as both 'long' and 'short'";
		return false;
	      } 
	      break;
	    case SHORT_TK:
	      if ( st_node->hasType(SHORT_TK))
	      {
		error = "SYNTAX ERROR: '" + identifier + "' specified as both 'long' and 'short'";
		return false;
	      }      
	      break;
	      
	    /*
	    case CONST_TK:
	      if (nodeString != ":declarator EQUAL_TK initializer" && !st_node->hasType(TYPEDEF_NAME_TK))
	      {
		error = "SYNTAX ERROR: '" + identifier + "' specified as 'const' but not initilized";
		return false;
	      }    
	    */ 
	    
	    // If we find 'typedef' in the types, we mark this as being a typedef by makeing its type a typedef_name
	    case TYPEDEF_TK:
		token_type = TYPEDEF_NAME_TK;
		break;
	    default:
		break;
	  }
	  
	  
	  st_node->addType(token_type);
	  cout << "Adding type " << token_type << " to symbol '" << identifier << "'" << endl;
	  
	  return true;
}