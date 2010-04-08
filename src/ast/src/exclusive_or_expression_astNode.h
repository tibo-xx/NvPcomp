/**********************************************************************/
//! ASTNode exclusive_or_expression_astNode implementation for NvPcomp
/*!
* \class exclusive_or_expression_astNode
*
* Description: The exclusive_or_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef EXCLUSIVE_OR_EXPRESSION_ASTNODE_H_
#define EXCLUSIVE_OR_EXPRESSION_ASTNODE_H_

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

class exclusive_or_expression_astNode:public astNode {
public:
	exclusive_or_expression_astNode();
	exclusive_or_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~exclusive_or_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* EXCLUSIVE_OR_EXPRESSION_ASTNODE_H_ */
