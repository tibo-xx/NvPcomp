/**********************************************************************/
//! ASTNode inclusive_or_expression_astNode implementation for NvPcomp
/*!
* \class inclusive_or_expression_astNode
*
* Description: The inclusive_or_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef INCLUSIVE_OR_EXPRESSION_ASTNODE_H_
#define INCLUSIVE_OR_EXPRESSION_ASTNODE_H_

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

class inclusive_or_expression_astNode:public astNode {
public:
	inclusive_or_expression_astNode();
	inclusive_or_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~inclusive_or_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* INCLUSIVE_OR_EXPRESSION_ASTNODE_H_ */
