/**********************************************************************/
//! ASTNode primary_expression_astNode implementation for NvPcomp
/*!
* \class primary_expression_astNode
*
* Description: The primary_expression_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef PRIMARY_EXPRESSION_ASTNODE_H_
#define PRIMARY_EXPRESSION_ASTNODE_H_

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

class primary_expression_astNode:public astNode {
public:
	primary_expression_astNode();
	primary_expression_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~primary_expression_astNode();
public:
	virtual void output3AC();
};

#endif /* PRIMARY_EXPRESSION_ASTNODE_H_ */
