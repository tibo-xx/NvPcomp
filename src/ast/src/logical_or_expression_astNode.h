/**********************************************************************/
//! ASTNode logical_or_expression_astNode implementation for NvPcomp
/*!
* \class logical_or_expression_astNode
*
* Description: The logical_or_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef LOGICAL_OR_EXPRESSION_ASTNODE_H_
#define LOGICAL_OR_EXPRESSION_ASTNODE_H_

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

class logical_or_expression_astNode:public expression_astNode {
public:
	logical_or_expression_astNode();
	logical_or_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~logical_or_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* LOGICAL_OR_EXPRESSION_ASTNODE_H_ */
