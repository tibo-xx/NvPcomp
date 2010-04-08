/**********************************************************************/
//! ASTNode identifier_astNode implementation for NvPcomp
/*!
* \class identifier_astNode
*
* Description: The identifier_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef IDENTIFIER_ASTNODE_H_
#define IDENTIFIER_ASTNODE_H_

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

class identifier_astNode:public astNode {
public:
	identifier_astNode();
	identifier_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~identifier_astNode();
public:
	virtual void output3AC();
};

#endif /* IDENTIFIER_ASTNODE_H_ */
