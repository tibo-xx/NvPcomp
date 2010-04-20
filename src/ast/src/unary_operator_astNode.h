/**********************************************************************/
//! ASTNode unary_operator_astNode implementation for NvPcomp
/*!
* \class unary_operator_astNode
*
* Description: The unary_operator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef UNARY_OPERATOR_ASTNODE_H_
#define UNARY_OPERATOR_ASTNODE_H_

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

class unary_operator_astNode:public expression_astNode {
public:
	unary_operator_astNode();
	unary_operator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~unary_operator_astNode();
public:
	virtual void output3AC();
};

#endif /* UNARY_OPERATOR_ASTNODE_H_ */
