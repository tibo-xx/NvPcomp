/**********************************************************************/
//! ASTNode compound_statement_astNode implementation for NvPcomp
/*!
* \class compound_statement_astNode
*
* Description: The compound_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef COMPOUND_STATEMENT_ASTNODE_H_
#define COMPOUND_STATEMENT_ASTNODE_H_

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

class compound_statement_astNode:public astNode {
public:
	compound_statement_astNode();
	compound_statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~compound_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* COMPOUND_STATEMENT_ASTNODE_H_ */
