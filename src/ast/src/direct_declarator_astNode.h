/**********************************************************************/
//! ASTNode direct_declarator_astNode implementation for NvPcomp
/*!
* \class direct_declarator_astNode
*
* Description: The direct_declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef DIRECT_DECLARATOR_ASTNODE_H_
#define DIRECT_DECLARATOR_ASTNODE_H_

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

class direct_declarator_astNode:public astNode {
public:
	direct_declarator_astNode();
	direct_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~direct_declarator_astNode();
public:
	virtual void output3AC();
};

#endif /* DIRECT_DECLARATOR_ASTNODE_H_ */
