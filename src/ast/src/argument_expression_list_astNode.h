/**********************************************************************/
//! ASTNode argument_expression_list_astNode implementation for NvPcomp
/*!
* \class argument_expression_list_astNode
*
* Description: The argument_expression_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ARGUMENT_EXPRESSION_LIST_ASTNODE_H_
#define ARGUMENT_EXPRESSION_LIST_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class argument_expression_list_astNode:public astNode {
public:
	argument_expression_list_astNode();
	argument_expression_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~argument_expression_list_astNode();
public:
	virtual void output3AC();
};

#endif /* ARGUMENT_EXPRESSION_LIST_ASTNODE_H_ */
