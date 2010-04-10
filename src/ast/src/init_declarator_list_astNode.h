/**********************************************************************/
//! ASTNode init_declarator_list_astNode implementation for NvPcomp
/*!
* \class init_declarator_list_astNode
*
* Description: The init_declarator_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef INIT_DECLARATOR_LIST_ASTNODE_H_
#define INIT_DECLARATOR_LIST_ASTNODE_H_

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

class init_declarator_list_astNode:public astNode {
public:
	init_declarator_list_astNode();
	init_declarator_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~init_declarator_list_astNode();
public:
	virtual void output3AC();
};

#endif /* INIT_DECLARATOR_LIST_ASTNODE_H_ */
