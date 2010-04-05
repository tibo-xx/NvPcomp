/**********************************************************************/
//! ASTNode statement_list_astNode implementation for NvPcomp
/*!
* \class statement_list_astNode
*
* Description: The statement_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STATEMENT_LIST_ASTNODE_H_
#define STATEMENT_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class statement_list_astNode:public astNode {
public:
	statement_list_astNode();
	statement_list_astNode(std::string _nodeString, NvPcomp::location _loc);
	~statement_list_astNode();
public:
	virtual void output3AC();
};

#endif /* STATEMENT_LIST_ASTNODE_H_ */
