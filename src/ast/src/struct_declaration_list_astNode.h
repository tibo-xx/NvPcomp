/**********************************************************************/
//! ASTNode struct_declaration_list_astNode implementation for NvPcomp
/*!
* \class struct_declaration_list_astNode
*
* Description: The struct_declaration_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef STRUCT_DECLARATION_LIST_ASTNODE_H_
#define STRUCT_DECLARATION_LIST_ASTNODE_H_

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

class struct_declaration_list_astNode:public astNode {
public:
	struct_declaration_list_astNode();
	struct_declaration_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~struct_declaration_list_astNode();
public:
	virtual void output3AC();
};

#endif /* STRUCT_DECLARATION_LIST_ASTNODE_H_ */
