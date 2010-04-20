/**********************************************************************/
//! ASTNode and_expression_astNode implementation for NvPcomp
/*!
* \class and_expression_astNode
*
* Description: The and_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef AND_EXPRESSION_ASTNODE_H_
#define AND_EXPRESSION_ASTNODE_H_

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

class and_expression_astNode:public expression_astNode {
public:
	and_expression_astNode();
	and_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~and_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* AND_EXPRESSION_ASTNODE_H_ */
