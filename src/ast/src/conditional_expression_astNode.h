/**********************************************************************/
//! ASTNode conditional_expression_astNode implementation for NvPcomp
/*!
* \class conditional_expression_astNode
*
* Description: The conditional_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef CONDITIONAL_EXPRESSION_ASTNODE_H_
#define CONDITIONAL_EXPRESSION_ASTNODE_H_

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

class conditional_expression_astNode:public astNode {
public:
	conditional_expression_astNode();
	conditional_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~conditional_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* CONDITIONAL_EXPRESSION_ASTNODE_H_ */
