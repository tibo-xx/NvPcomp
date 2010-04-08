/**********************************************************************/
//! ASTNode enum_specifier_astNode implementation for NvPcomp
/*!
* \class enum_specifier_astNode
*
* Description: The enum_specifier_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef ENUM_SPECIFIER_ASTNODE_H_
#define ENUM_SPECIFIER_ASTNODE_H_

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

class enum_specifier_astNode:public astNode {
public:
	enum_specifier_astNode();
	enum_specifier_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~enum_specifier_astNode();
public:
	virtual void output3AC();
};

#endif /* ENUM_SPECIFIER_ASTNODE_H_ */
