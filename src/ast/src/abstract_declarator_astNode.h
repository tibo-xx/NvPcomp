/**********************************************************************/
//! ASTNode abstract_declarator_astNode implementation for NvPcomp
/*!
* \class abstract_declarator_astNode
*
* Description: The abstract_declarator_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ABSTRACT_DECLARATOR_ASTNODE_H_
#define ABSTRACT_DECLARATOR_ASTNODE_H_

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

class abstract_declarator_astNode:public astNode {
public:
	abstract_declarator_astNode();
	abstract_declarator_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~abstract_declarator_astNode();
public:
	virtual void output3AC();
};

#endif /* ABSTRACT_DECLARATOR_ASTNODE_H_ */
