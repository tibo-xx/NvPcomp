/**********************************************************************/
//! ASTNode direct_abstract_declarator_astNode implementation for NvPcomp
/*!
* \class direct_abstract_declarator_astNode
*
* Description: The direct_abstract_declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef DIRECT_ABSTRACT_DECLARATOR_ASTNODE_H_
#define DIRECT_ABSTRACT_DECLARATOR_ASTNODE_H_

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

class direct_abstract_declarator_astNode:public astNode {
public:
	direct_abstract_declarator_astNode();
	direct_abstract_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~direct_abstract_declarator_astNode();
public:
	virtual void output3AC();
};

#endif /* DIRECT_ABSTRACT_DECLARATOR_ASTNODE_H_ */
