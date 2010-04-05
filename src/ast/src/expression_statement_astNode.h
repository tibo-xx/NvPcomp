/**********************************************************************/
//! ASTNode expression_statement_astNode implementation for NvPcomp
/*!
* \class expression_statement_astNode
*
* Description: The expression_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef EXPRESSION_STATEMENT_ASTNODE_H_
#define EXPRESSION_STATEMENT_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class expression_statement_astNode:public astNode {
public:
	expression_statement_astNode();
	expression_statement_astNode(std::string _nodeString, NvPcomp::location _loc);
	~expression_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* EXPRESSION_STATEMENT_ASTNODE_H_ */
