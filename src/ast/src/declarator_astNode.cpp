/***********************************************************************
* declarator_astNode - Syntax Tree Node
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

#include <declarator_astNode.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

declarator_astNode::declarator_astNode()
	:astNode() {
	nodeType = "declarator";
}

declarator_astNode::declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree)
	:astNode(_nodeString, _loc, tree) {
	nodeType = "declarator";
	LOG(ASTLog, logLEVEL1) << "===== Creating astNode ==== " << nodeType << " " << nodeString;
}

void declarator_astNode::output3AC() {
	LOG(ASTLog, logLEVEL1) << nodeType << " is not supported at this time" << nodeString;
}

std::string declarator_astNode::getName()
{
	string identifier;
	if (getString() == "pointer direct_declarator")
	{
	  identifier = getChild(1)->getString();
	}
	else
	  identifier = getChild(0)->getString();
	return identifier;
}

bool declarator_astNode::setSpecifiers(declaration_specifiers_astNode* declaration_specifiers, \
										NvPcomp::symTable *table, \
										variableTable *v_table, \
										string &error, \
										astInfoTable<functionDefinition> *f_table, \
										NvPcomp::location loc) {

	string identifier;
	bool is_pointer = false;
	bool is_array = false;
	int array_size = 0;
	if (getString() == "pointer direct_declarator")
	{
	  identifier = getChild(1)->getString();
	  is_pointer = true;
	}
else
	{
	  if (getChild(0)->getString() == "direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK")
	  {
	    // 2D array
	    if (getChild(0)->getChild(0)->getString() == "direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK")
	    {
	      identifier = getChild(0)->getChild(0)->getChild(0)->getString();
	      is_array = true;
	      array_size = atoi(getChild(0)->getChild(2)->getString().c_str()) * atoi(getChild(0)->getChild(0)->getChild(2)->getString().c_str());
	    }
	    // 1D array
	    else
	    {
	      identifier = getChild(0)->getChild(0)->getString();
	      is_array = true;
	      array_size = atoi(getChild(0)->getChild(2)->getString().c_str());
	    }
	  }
	  else if(getChild(0)->getString() == "direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK")
	  {
	      identifier = getChild(0)->getChild(0)->getString();
	      is_array = true;
	      array_size = -1;
	  }
	  else
	    identifier = getChild(0)->getString();
	}

	ret3ac = identifier;

	NvPcomp::symNode* st_node = table->search_top(identifier);
	
	// The identifier is not in the table...try to put it on the top.
	if (!st_node)
	{
		st_node = new NvPcomp::symNode(loc, identifier, "");
		InsertResult result = table->insert(identifier, st_node);

		if(result == INSERT_SUCCESS_W_SHADOW) {
			LOG(INFOLog, logLEVEL1) << "Warning: Variable " << identifier << " redefined on line: " << loc.begin.line << " at position: " << loc.begin.column;
		} else if(result == INSERT_FAIL_IN_CURRENT_LEVEL) {
			LOG(INFOLog, logLEVEL1) << "failed to insert " << identifier;
			error = "SERIOUS ERROR: failed to insert '" + identifier + "'";
			return false;
		}					
	} 	  
    		
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
	// Add pointer if its an array
	if (is_array)
	{
	  st_node->addType(STAR_TK);
          cout << "Adding pointer type " << STAR_TK << " to array " << identifier << " of size " << array_size << endl;
	}
	// Add pointer information
	if (is_pointer)
	{
	  for (int i = 0; i < getChild(0)->getNumberOfChildren(); i ++)
	  {
	    if (getChild(0)->getChild(i)->getString() == "type_qualifier")
	    {
	      for (int j = 0; j < getChild(0)->getChild(i)->getNumberOfChildren(); j ++)
	      {
		int token_type = ((leaf_astNode*) getChild(0)->getChild(i)->getChild(j))->getTokenType();
		st_node->addType(token_type);
		cout << "Adding qualifier type " << getChild(0)->getChild(i)->getChild(j)->getString() << endl;
	      }
	    }
	    else
	    {
	      int token_type = ((leaf_astNode*) getChild(0)->getChild(i))->getTokenType();
	      st_node->addType(token_type);
	      cout << "Adding pointer type " << getChild(0)->getChild(i)->getString() << endl;
	    }
	  }	 
	}
	if (f_table)
	{
	  functionDefinition new_func;
	  st_node->setMangledName(f_table->insert(identifier, &new_func));	  
	}
	else
	{
	  variableInfo new_var;
	  st_node->setMangledName(v_table->insert(identifier, &new_var));
	}
	return true;
}

bool declarator_astNode::addType(int token_type, NvPcomp::symNode *st_node, std::string &error)
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
