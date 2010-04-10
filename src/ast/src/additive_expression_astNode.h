/**********************************************************************/
//! ASTNode additive_expression_astNode implementation for NvPcomp
/*!
* \class additive_expression_astNode
*
* Description: The additive_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ADDITIVE_EXPRESSION_ASTNODE_H_
#define ADDITIVE_EXPRESSION_ASTNODE_H_

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

class additive_expression_astNode:public astNode {
public:
	additive_expression_astNode();
	additive_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~additive_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* ADDITIVE_EXPRESSION_ASTNODE_H_ */
