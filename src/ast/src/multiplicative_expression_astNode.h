/**********************************************************************/
//! ASTNode multiplicative_expression_astNode implementation for NvPcomp
/*!
* \class multiplicative_expression_astNode
*
* Description: The multiplicative_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef MULTIPLICATIVE_EXPRESSION_ASTNODE_H_
#define MULTIPLICATIVE_EXPRESSION_ASTNODE_H_

#include <astNode.h>
#include <expression_astNode.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <tacTree.h>
#include <NvPcomp_logger.h>

class multiplicative_expression_astNode:public expression_astNode {
public:
	multiplicative_expression_astNode();
	multiplicative_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~multiplicative_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* MULTIPLICATIVE_EXPRESSION_ASTNODE_H_ */
