/**********************************************************************/
//! ASTNode identifier_list_astNode implementation for NvPcomp
/*!
* \class identifier_list_astNode
*
* Description: The identifier_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef IDENTIFIER_LIST_ASTNODE_H_
#define IDENTIFIER_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class identifier_list_astNode:public astNode {
public:
	identifier_list_astNode();
	identifier_list_astNode(std::string _nodeString, NvPcomp::location _loc);
	~identifier_list_astNode();
public:
	virtual void output3AC();
};

#endif /* IDENTIFIER_LIST_ASTNODE_H_ */
