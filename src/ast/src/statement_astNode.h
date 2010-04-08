/**********************************************************************/
//! ASTNode statement_astNode implementation for NvPcomp
/*!
* \class statement_astNode
*
* Description: The statement_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STATEMENT_ASTNODE_H_
#define STATEMENT_ASTNODE_H_

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

class statement_astNode:public astNode {
public:
	statement_astNode();
	statement_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~statement_astNode();
public:
	virtual void output3AC();
};

#endif /* STATEMENT_ASTNODE_H_ */
