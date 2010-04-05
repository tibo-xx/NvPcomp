/**********************************************************************/
//! ASTNode selection_statement_astNode implementation for NvPcomp
/*!
* \class selection_statement_astNode
*
* Description: The selection_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef SELECTION_STATEMENT_ASTNODE_H_
#define SELECTION_STATEMENT_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class selection_statement_astNode:public astNode {
public:
	selection_statement_astNode();
	selection_statement_astNode(std::string _nodeString, NvPcomp::location _loc);
	~selection_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* SELECTION_STATEMENT_ASTNODE_H_ */
