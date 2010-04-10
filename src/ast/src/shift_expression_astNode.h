/**********************************************************************/
//! ASTNode shift_expression_astNode implementation for NvPcomp
/*!
* \class shift_expression_astNode
*
* Description: The shift_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef SHIFT_EXPRESSION_ASTNODE_H_
#define SHIFT_EXPRESSION_ASTNODE_H_

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

class shift_expression_astNode:public astNode {
public:
	shift_expression_astNode();
	shift_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~shift_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* SHIFT_EXPRESSION_ASTNODE_H_ */
