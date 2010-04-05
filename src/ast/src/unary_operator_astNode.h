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

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class unary_operator_astNode:public astNode {
public:
	unary_operator_astNode();
	unary_operator_astNode(std::string _nodeString, NvPcomp::location _loc);
	~unary_operator_astNode();
public:
	virtual void output3AC();
};

#endif /* UNARY_OPERATOR_ASTNODE_H_ */
