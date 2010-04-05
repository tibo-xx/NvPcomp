/**********************************************************************/
//! ASTNode assignment_expression_astNode implementation for NvPcomp
/*!
* \class assignment_expression_astNode
*
* Description: The assignment_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ASSIGNMENT_EXPRESSION_ASTNODE_H_
#define ASSIGNMENT_EXPRESSION_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class assignment_expression_astNode:public astNode {
public:
	assignment_expression_astNode();
	assignment_expression_astNode(std::string _nodeString, NvPcomp::location _loc);
	~assignment_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* ASSIGNMENT_EXPRESSION_ASTNODE_H_ */
