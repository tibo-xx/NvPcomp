/**********************************************************************/
//! ASTNode postfix_expression_astNode implementation for NvPcomp
/*!
* \class postfix_expression_astNode
*
* Description: The postfix_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef POSTFIX_EXPRESSION_ASTNODE_H_
#define POSTFIX_EXPRESSION_ASTNODE_H_

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

class postfix_expression_astNode:public astNode {
public:
	postfix_expression_astNode();
	postfix_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~postfix_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* POSTFIX_EXPRESSION_ASTNODE_H_ */
