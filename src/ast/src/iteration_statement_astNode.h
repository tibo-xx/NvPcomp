/**********************************************************************/
//! ASTNode iteration_statement_astNode implementation for NvPcomp
/*!
* \class iteration_statement_astNode
*
* Description: The iteration_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ITERATION_STATEMENT_ASTNODE_H_
#define ITERATION_STATEMENT_ASTNODE_H_

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

class iteration_statement_astNode:public astNode {
public:
	iteration_statement_astNode();
	iteration_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~iteration_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* ITERATION_STATEMENT_ASTNODE_H_ */
