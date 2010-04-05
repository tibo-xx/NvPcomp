/**********************************************************************/
//! ASTNode jump_statement_astNode implementation for NvPcomp
/*!
* \class jump_statement_astNode
*
* Description: The jump_statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef JUMP_STATEMENT_ASTNODE_H_
#define JUMP_STATEMENT_ASTNODE_H_

#include <ast.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <position.hh>
#include <location.hh>
#include <NvPcomp_logger.h>

class jump_statement_astNode:public astNode {
public:
	jump_statement_astNode();
	jump_statement_astNode(std::string _nodeString, NvPcomp::location _loc);
	~jump_statement_astNode();
public:
	virtual void output3AC();
};

#endif /* JUMP_STATEMENT_ASTNODE_H_ */
