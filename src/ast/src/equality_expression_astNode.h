/**********************************************************************/
//! ASTNode equality_expression_astNode implementation for NvPcomp
/*!
* \class equality_expression_astNode
*
* Description: The equality_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef EQUALITY_EXPRESSION_ASTNODE_H_
#define EQUALITY_EXPRESSION_ASTNODE_H_

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

class equality_expression_astNode:public astNode {
public:
	equality_expression_astNode();
	equality_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~equality_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* EQUALITY_EXPRESSION_ASTNODE_H_ */
