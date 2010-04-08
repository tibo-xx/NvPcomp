/**********************************************************************/
//! ASTNode declaration_specifiers_astNode implementation for NvPcomp
/*!
* \class declaration_specifiers_astNode
*
* Description: The declaration_specifiers_astNode implementation for Abstract Syntax Tree in NvPcomp
*
* \author CMT, DRJ & BFB
*
*/
/**********************************************************************/
#ifndef DECLARATION_SPECIFIERS_ASTNODE_H_
#define DECLARATION_SPECIFIERS_ASTNODE_H_

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

class declaration_specifiers_astNode:public astNode {
public:
	declaration_specifiers_astNode();
	declaration_specifiers_astNode(std::string _nodeString, NvPcomp::location _loc, NvPcomp::tacTree *tree);
	~declaration_specifiers_astNode();
public:
	virtual void output3AC();
};

#endif /* DECLARATION_SPECIFIERS_ASTNODE_H_ */
