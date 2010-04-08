/**********************************************************************/
//! ASTNode specifier_qualifier_list_astNode implementation for NvPcomp
/*!
* \class specifier_qualifier_list_astNode
*
* Description: The specifier_qualifier_list_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef SPECIFIER_QUALIFIER_LIST_ASTNODE_H_
#define SPECIFIER_QUALIFIER_LIST_ASTNODE_H_

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

class specifier_qualifier_list_astNode:public astNode {
public:
	specifier_qualifier_list_astNode();
	specifier_qualifier_list_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~specifier_qualifier_list_astNode();
public:
	virtual void output3AC();
};

#endif /* SPECIFIER_QUALIFIER_LIST_ASTNODE_H_ */
