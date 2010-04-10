/**********************************************************************/
//! ASTNode struct_declarator_astNode implementation for NvPcomp
/*!
* \class struct_declarator_astNode
*
* Description: The struct_declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STRUCT_DECLARATOR_ASTNODE_H_
#define STRUCT_DECLARATOR_ASTNODE_H_

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

class struct_declarator_astNode:public astNode {
public:
	struct_declarator_astNode();
	struct_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~struct_declarator_astNode();
public:
	virtual void output3AC();
};

#endif /* STRUCT_DECLARATOR_ASTNODE_H_ */
