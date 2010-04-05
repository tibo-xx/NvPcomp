/**********************************************************************/
//! ASTNode type_qualifier_list_astNode implementation for NvPcomp
/*!
* \class type_qualifier_list_astNode
*
* Description: The type_qualifier_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef TYPE_QUALIFIER_LIST_ASTNODE_H_
#define TYPE_QUALIFIER_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class type_qualifier_list_astNode:public astNode {
public:
	type_qualifier_list_astNode();
	type_qualifier_list_astNode(std::string _nodeString, NvPcomp::location _loc);
	~type_qualifier_list_astNode();
public:
	virtual void output3AC();
};

#endif /* TYPE_QUALIFIER_LIST_ASTNODE_H_ */
