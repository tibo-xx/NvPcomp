/**********************************************************************/
//! ASTNode root_astNode implementation for NvPcomp
/*!
* \class root_astNode
*
* Description: The root_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ROOT_ASTNODE_H_
#define ROOT_ASTNODE_H_

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

class root_astNode:public astNode {
public:
	root_astNode();
	root_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~root_astNode();
public:
	virtual void output3AC();
};

#endif /* ROOT_ASTNODE_H_ */
