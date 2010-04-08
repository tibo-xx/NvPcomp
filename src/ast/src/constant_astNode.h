/**********************************************************************/
//! ASTNode constant_astNode implementation for NvPcomp
/*!
* \class constant_astNode
*
* Description: The constant_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef CONSTANT_ASTNODE_H_
#define CONSTANT_ASTNODE_H_

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

class constant_astNode:public astNode {
public:
	constant_astNode();
	constant_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~constant_astNode();
public:
	virtual void output3AC();
};

#endif /* CONSTANT_ASTNODE_H_ */
