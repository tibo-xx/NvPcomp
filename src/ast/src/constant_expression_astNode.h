/**********************************************************************/
//! ASTNode constant_expression_astNode implementation for NvPcomp
/*!
* \class constant_expression_astNode
*
* Description: The constant_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef CONSTANT_EXPRESSION_ASTNODE_H_
#define CONSTANT_EXPRESSION_ASTNODE_H_

#include <astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class constant_expression_astNode:public astNode {
public:
	constant_expression_astNode();
	constant_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~constant_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* CONSTANT_EXPRESSION_ASTNODE_H_ */
